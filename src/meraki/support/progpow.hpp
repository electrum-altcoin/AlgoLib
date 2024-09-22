// meraki: C/C++ implementation of Meraki, the Telestai Proof of Work algorithm.
// Copyright 2018-2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

/// @file
///
/// ProgPoW API
///
/// This file provides the public API for ProgPoW as the Meraki API extension.

#include "meraki/meraki/meraki.hpp"

/// The ProgPoW algorithm revision implemented as specified in the spec
/// https://github.com/ifdefelse/ProgPOW#change-history.
#define REVISION = "0.9.4"

namespace progpow
{
using namespace meraki;  // Include meraki namespace.

const int period_length = 3;
const uint32_t num_regs = 32;
const size_t num_lanes = 16;
const int num_cache_accesses = 12;
const int num_math_operations = 5;
const size_t l1_cache_size = 16 * 1024;
const size_t l1_cache_num_items = l1_cache_size / sizeof(uint32_t);

meraki_result hash(const meraki_epoch_context& context, int block_number, const meraki_hash256& header_hash,
    uint64_t nonce) NOEXCEPT;

meraki_result hash(const meraki_epoch_context_full& context, int block_number, const meraki_hash256& header_hash,
    uint64_t nonce) NOEXCEPT;

bool verify(const meraki_epoch_context& context, int block_number, const meraki_hash256& header_hash,
    const meraki_hash256& mix_hash, uint64_t nonce, const meraki_hash256& boundary) NOEXCEPT;

//bool light_verify(const char* str_header_hash,
//        const char* str_mix_hash, const char* str_nonce, const char* str_boundary, char* str_final) NOEXCEPT;

search_result search_light(const meraki_epoch_context& context, int block_number,
    const meraki_hash256& header_hash, const meraki_hash256& boundary, uint64_t start_nonce,
    size_t iterations) NOEXCEPT;

search_result search(const meraki_epoch_context_full& context, int block_number,
    const meraki_hash256& header_hash, const meraki_hash256& boundary, uint64_t start_nonce,
    size_t iterations) NOEXCEPT;

}  // namespace progpow
