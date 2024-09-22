// meraki: C/C++ implementation of Meraki, the Telestai Proof of Work algorithm.
// Copyright 2018-2019 Pawel Bylica.
// Licensed under the Apache License, Version 2.0.

#pragma once

#include "keccak.h"
#include "meraki/support/hash_types.hpp"

namespace meraki
{
inline meraki_hash256 keccak256(const uint8_t* data, size_t size) NOEXCEPT
{
    return meraki_keccak256(data, size);
}

inline meraki_hash256 keccak256(const meraki_hash256& input) NOEXCEPT
{
    return meraki_keccak256_32(input.bytes);
}

inline meraki_hash512 keccak512(const uint8_t* data, size_t size) NOEXCEPT
{
    return meraki_keccak512(data, size);
}

inline meraki_hash512 keccak512(const meraki_hash512& input) NOEXCEPT
{
    return meraki_keccak512_64(input.bytes);
}

}  // namespace meraki
