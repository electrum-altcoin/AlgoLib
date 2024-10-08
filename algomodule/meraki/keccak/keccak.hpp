// meraki: C/C++ implementation of Meraki, the Telestai Proof of Work algorithm.
// Copyright 2018-2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#pragma once

#include "algomodule/meraki/keccak/keccak.h"
#include "algomodule/meraki/support/hash_types.hpp"

namespace meraki
{
inline hash256 keccak256(const uint8_t* data, size_t size) 
{
    return meraki_keccak256(data, size);
}

inline hash256 keccak256(const hash256& input) 
{
    return meraki_keccak256_32(input.bytes);
}

inline hash512 keccak512(const uint8_t* data, size_t size) 
{
    return meraki_keccak512(data, size);
}

inline hash512 keccak512(const hash512& input) 
{
    return meraki_keccak512_64(input.bytes);
}

static constexpr auto keccak256_32 = meraki_keccak256_32;
static constexpr auto keccak512_64 = meraki_keccak512_64;

}  // namespace meraki
