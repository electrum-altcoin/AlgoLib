/* meraki: C/C++ implementation of Meraki, the Telestai Proof of Work algorithm.
 * Copyright 2018-2019 Pawel Bylica.
 * Licensed under the Apache License, Version 2.0.
 */

#pragma once

#include "algomodule/meraki/support/hash_types.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The Keccak-f[1600] function.
 *
 * The implementation of the Keccak-f function with 1600-bit width of the permutation (b).
 * The size of the state is also 1600 bit what gives 25 64-bit words.
 *
 * @param state  The state of 25 64-bit words on which the permutation is to be performed.
 */
void meraki_keccakf1600(uint64_t state[25]) ;

/**
 * The Keccak-f[800] function.
 *
 * The implementation of the Keccak-f function with 800-bit width of the permutation (b).
 * The size of the state is also 800 bit what gives 25 32-bit words.
 *
 * @param state  The state of 25 32-bit words on which the permutation is to be performed.
 */
void meraki_keccakf800(uint32_t state[25]) ;

union meraki_hash256 meraki_keccak256(const uint8_t* data, size_t size) ;
union meraki_hash256 meraki_keccak256_32(const uint8_t data[32]) ;
union meraki_hash512 meraki_keccak512(const uint8_t* data, size_t size) ;
union meraki_hash512 meraki_keccak512_64(const uint8_t data[64]) ;

#ifdef __cplusplus
}
#endif
