# distutils: language = c++
from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "meraki/meraki/meraki.h":
	cdef union meraki_hash256:
		uint64_t word64s[4]
		uint32_t word32s[8]
		uint8_t bytes[32]
		char str[32]

	cdef meraki_hash256 light_verify(
		const meraki_hash256* header_hash,
		const meraki_hash256* mix_hash,
		uint64_t nonce
	)

# The Python wrapper function for light_verify
def _meraki_hash(bytes header_hash, bytes mix_hash, uint64_t nonce):
	if len(header_hash) != 32 or len(mix_hash) != 32:
		raise ValueError("header_hash and mix_hash must be 32 bytes")

	cdef meraki_hash256* c_header_hash
	cdef meraki_hash256* c_mix_hash
	cdef meraki_hash256 result
	cdef unsigned char[::1] mv_header_hash
	cdef unsigned char[::1] mv_mix_hash

	c_header_hash = <meraki_hash256*>malloc(sizeof(meraki_hash256))
	c_mix_hash = <meraki_hash256*>malloc(sizeof(meraki_hash256))
	
	if not c_header_hash or not c_mix_hash:
		raise MemoryError("Could not allocate memory for meraki_hash256")

	try:
		mv_header_hash = bytearray(header_hash)  # Create a bytearray
		mv_mix_hash = bytearray(mix_hash)        # Create a bytearray

		memcpy(c_header_hash.str, &mv_header_hash[0], 32)  # Use address of first element in memoryview
		memcpy(c_mix_hash.str, &mv_mix_hash[0], 32)        # Use address of first element in memoryview

		result = light_verify(c_header_hash, c_mix_hash, nonce)

		result_bytes = bytes(result.str[:32])

		return result_bytes

	finally:
		free(c_header_hash)
		free(c_mix_hash)