// meraki: C/C++ implementation of Meraki, the Telestai Proof of Work algorithm.
// Copyright 2018-2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#include "meraki/meraki/meraki-internal.hpp"

#include "meraki/support/attributes.h"
#include "meraki/meraki/bit_manipulation.h"
#include "meraki/meraki/endianness.hpp"
#include "meraki/meraki/primes.h"
#include "meraki/keccak/keccak.hpp"
#include "meraki/support/progpow.hpp"

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <cstddef>

namespace meraki
{
// Internal constants:
const static int light_cache_init_size = 1 << 24;
const static int light_cache_growth = 1 << 17;
const static int light_cache_rounds = 3;
const static int full_dataset_init_size = 1 << 30;
const static int full_dataset_growth = 1 << 23;
const static int full_dataset_item_parents = 512;



// Verify constants:
static_assert(sizeof(meraki_hash512) == MERAKI_LIGHT_CACHE_ITEM_SIZE, "");
static_assert(sizeof(meraki_hash1024) == MERAKI_FULL_DATASET_ITEM_SIZE, "");
static_assert(light_cache_item_size == MERAKI_LIGHT_CACHE_ITEM_SIZE, "");
static_assert(full_dataset_item_size == MERAKI_FULL_DATASET_ITEM_SIZE, "");


namespace
{
using ::fnv1;

inline meraki_hash512 fnv1(const meraki_hash512& u, const meraki_hash512& v) NOEXCEPT
{
    meraki_hash512 r;
    for (std::size_t i = 0; i < sizeof(r) / sizeof(r.word32s[0]); ++i)
        r.word32s[i] = fnv1(u.word32s[i], v.word32s[i]);
    return r;
}

inline meraki_hash512 bitwise_xor(const meraki_hash512& x, const meraki_hash512& y) NOEXCEPT
{
    meraki_hash512 z;
    for (size_t i = 0; i < sizeof(z) / sizeof(z.word64s[0]); ++i)
        z.word64s[i] = x.word64s[i] ^ y.word64s[i];
    return z;
}
}  // namespace

int find_epoch_number(const meraki_hash256& seed) NOEXCEPT
{
    static const int num_tries = 30000;  // Divisible by 16.

    // Thread-local cache of the last search.
    static thread_local int cached_epoch_number = 0;
    static thread_local meraki_hash256 cached_seed = {};

    // Load from memory once (memory will be clobbered by keccak256()).
    const uint32_t seed_part = seed.word32s[0];
    const int e = cached_epoch_number;
    meraki_hash256 s = cached_seed;

    if (s.word32s[0] == seed_part)
        return e;

    // Try the next seed, will match for sequential epoch access.
    s = keccak256(s);
    if (s.word32s[0] == seed_part)
    {
        cached_seed = s;
        cached_epoch_number = e + 1;
        return e + 1;
    }

    // Search for matching seed starting from epoch 0.
    s = {};
    for (int i = 0; i < num_tries; ++i)
    {
        if (s.word32s[0] == seed_part)
        {
            cached_seed = s;
            cached_epoch_number = i;
            return i;
        }

        s = keccak256(s);
    }

    return -1;
}

namespace generic
{
void build_light_cache(
    hash_fn_512 hash_fn, meraki_hash512 cache[], int num_items, const meraki_hash256& seed) NOEXCEPT
{
    meraki_hash512 item = hash_fn(seed.bytes, sizeof(seed));
    cache[0] = item;
    for (int i = 1; i < num_items; ++i)
    {
        item = hash_fn(item.bytes, sizeof(item));
        cache[i] = item;
    }

    for (int q = 0; q < light_cache_rounds; ++q)
    {
        for (int i = 0; i < num_items; ++i)
        {
            const uint32_t index_limit = static_cast<uint32_t>(num_items);

            // Fist index: 4 first bytes of the item as little-endian integer.
            const uint32_t t = le::uint32(cache[i].word32s[0]);
            const uint32_t v = t % index_limit;

            // Second index.
            const uint32_t w = static_cast<uint32_t>(num_items + (i - 1)) % index_limit;

            const meraki_hash512 x = bitwise_xor(cache[v], cache[w]);
            cache[i] = hash_fn(x.bytes, sizeof(x));
        }
    }
}

meraki_epoch_context_full* create_epoch_context(
    build_light_cache_fn build_fn, int epoch_number, bool full) NOEXCEPT
{
    static_assert(sizeof(meraki_epoch_context_full) < sizeof(meraki_hash512), "epoch_context too big");
    static const size_t context_alloc_size = sizeof(meraki_hash512);

    const int light_cache_num_items = meraki_calculate_light_cache_num_items(epoch_number);
    const int full_dataset_num_items = meraki_calculate_full_dataset_num_items(epoch_number);
    const size_t light_cache_size = get_light_cache_size(light_cache_num_items);
    const size_t full_dataset_size =
        full ? static_cast<size_t>(full_dataset_num_items) * sizeof(meraki_hash1024) :
               progpow::l1_cache_size;

    const size_t alloc_size = context_alloc_size + light_cache_size + full_dataset_size;

    char* const alloc_data = static_cast<char*>(std::calloc(1, alloc_size));
    if (!alloc_data)
        return nullptr;  // Signal out-of-memory by returning null pointer.

    meraki_hash512* const light_cache = reinterpret_cast<meraki_hash512*>(alloc_data + context_alloc_size);
    const meraki_hash256 epoch_seed = meraki_calculate_epoch_seed(epoch_number);
    build_fn(light_cache, light_cache_num_items, epoch_seed);

    uint32_t* const l1_cache =
        reinterpret_cast<uint32_t*>(alloc_data + context_alloc_size + light_cache_size);

    meraki_hash1024* full_dataset = full ? reinterpret_cast<meraki_hash1024*>(l1_cache) : nullptr;

    meraki_epoch_context_full* const context = new (alloc_data) meraki_epoch_context_full{
        epoch_number,
        light_cache_num_items,
        light_cache,
        l1_cache,
        full_dataset_num_items,
        full_dataset,
    };

    auto* full_dataset_2048 = reinterpret_cast<meraki_hash2048*>(l1_cache);
    for (uint32_t i = 0; i < progpow::l1_cache_size / sizeof(full_dataset_2048[0]); ++i)
        full_dataset_2048[i] = calculate_dataset_item_2048(*context, i);
    return context;
}
}  // namespace generic

void build_light_cache(meraki_hash512 cache[], int num_items, const meraki_hash256& seed) NOEXCEPT
{
    return generic::build_light_cache(keccak512, cache, num_items, seed);
}

struct item_state
{
    const meraki_hash512* const cache;
    const int64_t num_cache_items;
    const uint32_t seed;

    meraki_hash512 mix;

    ALWAYS_INLINE item_state(const meraki_epoch_context& context, int64_t index) NOEXCEPT
      : cache{context.light_cache},
        num_cache_items{context.light_cache_num_items},
        seed{static_cast<uint32_t>(index)}
    {
        mix = cache[index % num_cache_items];
        mix.word32s[0] ^= le::uint32(seed);
        mix = le::uint32s(keccak512(mix));
    }

    ALWAYS_INLINE void update(uint32_t round) NOEXCEPT
    {
        static const size_t num_words = sizeof(mix) / sizeof(uint32_t);
        const uint32_t t = fnv1(seed ^ round, mix.word32s[round % num_words]);
        const int64_t parent_index = t % num_cache_items;
        mix = fnv1(mix, le::uint32s(cache[parent_index]));
    }

    ALWAYS_INLINE meraki_hash512 final() NOEXCEPT { return keccak512(le::uint32s(mix)); }
};

meraki_hash512 calculate_dataset_item_512(const meraki_epoch_context& context, int64_t index) NOEXCEPT
{
    item_state item0{context, index};
    for (uint32_t j = 0; j < full_dataset_item_parents; ++j)
        item0.update(j);
    return item0.final();
}

/// Calculates a full dataset item
///
/// This consist of two 512-bit items produced by calculate_dataset_item_partial().
/// Here the computation is done interleaved for better performance.
meraki_hash1024 calculate_dataset_item_1024(const meraki_epoch_context& context, uint32_t index) NOEXCEPT
{
    item_state item0{context, int64_t(index) * 2};
    item_state item1{context, int64_t(index) * 2 + 1};

    for (uint32_t j = 0; j < full_dataset_item_parents; ++j)
    {
        item0.update(j);
        item1.update(j);
    }

    return meraki_hash1024{{item0.final(), item1.final()}};
}

meraki_hash2048 calculate_dataset_item_2048(const meraki_epoch_context& context, uint32_t index) NOEXCEPT
{
    item_state item0{context, int64_t(index) * 4};
    item_state item1{context, int64_t(index) * 4 + 1};
    item_state item2{context, int64_t(index) * 4 + 2};
    item_state item3{context, int64_t(index) * 4 + 3};

    for (uint32_t j = 0; j < full_dataset_item_parents; ++j)
    {
        item0.update(j);
        item1.update(j);
        item2.update(j);
        item3.update(j);
    }

    return meraki_hash2048{{item0.final(), item1.final(), item2.final(), item3.final()}};
}

namespace
{
using lookup_fn = meraki_hash1024 (*)(const meraki_epoch_context&, uint32_t);

inline meraki_hash512 hash_seed(const meraki_hash256& header_hash, uint64_t nonce) NOEXCEPT
{
    nonce = le::uint64(nonce);
    uint8_t init_data[sizeof(header_hash) + sizeof(nonce)];
    std::memcpy(&init_data[0], &header_hash, sizeof(header_hash));
    std::memcpy(&init_data[sizeof(header_hash)], &nonce, sizeof(nonce));

    return keccak512(init_data, sizeof(init_data));
}

inline meraki_hash256 hash_final(const meraki_hash512& seed, const meraki_hash256& mix_hash)
{
    uint8_t final_data[sizeof(seed) + sizeof(mix_hash)];
    std::memcpy(&final_data[0], seed.bytes, sizeof(seed));
    std::memcpy(&final_data[sizeof(seed)], mix_hash.bytes, sizeof(mix_hash));
    return keccak256(final_data, sizeof(final_data));
}

inline meraki_hash256 hash_kernel(
    const meraki_epoch_context& context, const meraki_hash512& seed, lookup_fn lookup) NOEXCEPT
{
    static const size_t num_words = sizeof(meraki_hash1024) / sizeof(uint32_t);
    const uint32_t index_limit = static_cast<uint32_t>(context.full_dataset_num_items);
    const uint32_t seed_init = le::uint32(seed.word32s[0]);

    meraki_hash1024 mix{{le::uint32s(seed), le::uint32s(seed)}};

    for (uint32_t i = 0; i < num_dataset_accesses; ++i)
    {
        const uint32_t p = fnv1(i ^ seed_init, mix.word32s[i % num_words]) % index_limit;
        const meraki_hash1024 newdata = le::uint32s(lookup(context, p));

        for (size_t j = 0; j < num_words; ++j)
            mix.word32s[j] = fnv1(mix.word32s[j], newdata.word32s[j]);
    }

    meraki_hash256 mix_hash;
    for (size_t i = 0; i < num_words; i += 4)
    {
        const uint32_t h1 = fnv1(mix.word32s[i], mix.word32s[i + 1]);
        const uint32_t h2 = fnv1(h1, mix.word32s[i + 2]);
        const uint32_t h3 = fnv1(h2, mix.word32s[i + 3]);
        mix_hash.word32s[i / 4] = h3;
    }

    return le::uint32s(mix_hash);
}
}  // namespace

meraki_result hash(const meraki_epoch_context_full& context, const meraki_hash256& header_hash, uint64_t nonce) NOEXCEPT
{
    static const auto lazy_lookup = [](const meraki_epoch_context& ctx, uint32_t index) NOEXCEPT
    {
        auto full_dataset = static_cast<const meraki_epoch_context_full&>(ctx).full_dataset;
        meraki_hash1024& item = full_dataset[index];
        if (item.word64s[0] == 0)
        {
            // TODO: Copy elision here makes it thread-safe?
            item = calculate_dataset_item_1024(ctx, index);
        }

        return item;
    };

    const meraki_hash512 seed = hash_seed(header_hash, nonce);
    const meraki_hash256 mix_hash = hash_kernel(context, seed, lazy_lookup);
    return {hash_final(seed, mix_hash), mix_hash};
}

search_result search_light(const meraki_epoch_context& context, const meraki_hash256& header_hash,
    const meraki_hash256& boundary, uint64_t start_nonce, size_t iterations) NOEXCEPT
{
    const uint64_t end_nonce = start_nonce + iterations;
    for (uint64_t nonce = start_nonce; nonce < end_nonce; ++nonce)
    {
        meraki_result r = hash(context, header_hash, nonce);
        if (is_less_or_equal(r.final_hash, boundary))
            return {r, nonce};
    }
    return {};
}

search_result search(const meraki_epoch_context_full& context, const meraki_hash256& header_hash,
    const meraki_hash256& boundary, uint64_t start_nonce, size_t iterations) NOEXCEPT
{
    const uint64_t end_nonce = start_nonce + iterations;
    for (uint64_t nonce = start_nonce; nonce < end_nonce; ++nonce)
    {
        meraki_result r = hash(context, header_hash, nonce);
        if (is_less_or_equal(r.final_hash, boundary))
            return {r, nonce};
    }
    return {};
}
}  // namespace meraki

using namespace meraki;

extern "C" {

meraki_hash256 meraki_calculate_epoch_seed(int epoch_number) NOEXCEPT
{
    meraki_hash256 epoch_seed = {};
    for (int i = 0; i < epoch_number; ++i)
        epoch_seed = meraki_keccak256_32(epoch_seed.bytes);
    return epoch_seed;
}

int meraki_calculate_light_cache_num_items(int epoch_number) NOEXCEPT
{
    static const int item_size = sizeof(meraki_hash512);
    static const int num_items_init = light_cache_init_size / item_size;
    static const int num_items_growth = light_cache_growth / item_size;
    static_assert(
        light_cache_init_size % item_size == 0, "light_cache_init_size not multiple of item size");
    static_assert(
        light_cache_growth % item_size == 0, "light_cache_growth not multiple of item size");

    int num_items_upper_bound = num_items_init + (epoch_number * 4) * num_items_growth;
    int num_items = meraki_find_largest_prime(num_items_upper_bound);
    return num_items;
}

int meraki_calculate_full_dataset_num_items(int epoch_number) NOEXCEPT
{
    static const int item_size = sizeof(meraki_hash1024);
    static const int num_items_init = full_dataset_init_size / item_size;
    static const int num_items_growth = full_dataset_growth / item_size;
    static_assert(full_dataset_init_size % item_size == 0,
        "full_dataset_init_size not multiple of item size");
    static_assert(
        full_dataset_growth % item_size == 0, "full_dataset_growth not multiple of item size");

    int num_items_upper_bound = num_items_init + (epoch_number * 4) * num_items_growth;
    int num_items = meraki_find_largest_prime(num_items_upper_bound);
    return num_items;
}

meraki_epoch_context* meraki_create_epoch_context(int epoch_number) NOEXCEPT
{
    return generic::create_epoch_context(build_light_cache, epoch_number, false);
}

meraki_epoch_context_full* meraki_create_epoch_context_full(int epoch_number) NOEXCEPT
{
    return generic::create_epoch_context(build_light_cache, epoch_number, true);
}

void meraki_destroy_epoch_context_full(meraki_epoch_context_full* context) NOEXCEPT
{
    meraki_destroy_epoch_context(context);
}

void meraki_destroy_epoch_context(meraki_epoch_context* context) NOEXCEPT
{
    context->~meraki_epoch_context();
    std::free(context);
}

meraki_result meraki_hash(
    const meraki_epoch_context* context, const meraki_hash256* header_hash, uint64_t nonce) NOEXCEPT
{
    const meraki_hash512 seed = hash_seed(*header_hash, nonce);
    const meraki_hash256 mix_hash = hash_kernel(*context, seed, calculate_dataset_item_1024);
    return {hash_final(seed, mix_hash), mix_hash};
}

bool meraki_verify_final_hash(const meraki_hash256* header_hash, const meraki_hash256* mix_hash, uint64_t nonce,
    const meraki_hash256* boundary) NOEXCEPT
{
    const meraki_hash512 seed = hash_seed(*header_hash, nonce);
    return is_less_or_equal(hash_final(seed, *mix_hash), *boundary);
}

bool meraki_verify(const meraki_epoch_context* context, const meraki_hash256* header_hash,
    const meraki_hash256* mix_hash, uint64_t nonce, const meraki_hash256* boundary) NOEXCEPT
{
    const meraki_hash512 seed = hash_seed(*header_hash, nonce);
    if (!is_less_or_equal(hash_final(seed, *mix_hash), *boundary))
        return false;

    const meraki_hash256 expected_mix_hash = hash_kernel(*context, seed, calculate_dataset_item_1024);
    return is_equal(expected_mix_hash, *mix_hash);
}

static const uint32_t meowcoin_meraki[15] = {
        0x00000072, //R
        0x00000041, //A
        0x00000056, //V
        0x00000045, //E
        0x0000004E, //N
        0x00000043, //C
        0x0000004F, //O
        0x00000049, //I
        0x0000004E, //N
        0x0000004B, //K
        0x00000041, //A
        0x00000057, //W
        0x00000050, //P
        0x0000004F, //O
        0x00000057, //W
};


meraki_hash256 light_verify(const meraki_hash256* header_hash,
                       const meraki_hash256* mix_hash, uint64_t nonce) NOEXCEPT
{
    uint32_t state2[8];

    {
        // Absorb phase for initial round of keccak
        // 1st fill with header data (8 words)
        uint32_t state[25] = {0x0};     // Keccak's state
        for (int i = 0; i < 8; i++)
            state[i] = header_hash->word32s[i];

        // 2nd fill with nonce (2 words)
        state[8] = (uint32_t)nonce;
        state[9] = (uint32_t)(nonce >> 32);

        // 3rd apply progpow input constraints
        for (int i = 10; i < 25; i++)
            state[i] = meowcoin_meraki[i-10];

        meraki_keccakf800(state);

        for (int i = 0; i < 8; i++)
            state2[i] = state[i];
    }

    uint32_t state[25] = {0x0};     // Keccak's state

    // Absorb phase for last round of keccak (256 bits)
    // 1st initial 8 words of state are kept as carry-over from initial keccak
    for (int i = 0; i < 8; i++)
        state[i] = state2[i];


    // 2nd subsequent 8 words are carried from digest/mix
    for (int i = 8; i < 16; i++)
        state[i] = mix_hash->word32s[i-8];

    // 3rd apply progpow input constraints
    for (int i = 16; i < 25; i++)
        state[i] = meowcoin_meraki[i - 16];

    // Run keccak loop
    meraki_keccakf800(state);

    meraki_hash256 output;
    for (int i = 0; i < 8; ++i)
        output.word32s[i] = le::uint32(state[i]);

    return output;
}

}  // extern "C"
