from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "neoscrypt/neoscrypt.h":
	extern void neoscrypt_hash(const unsigned char* input, unsigned char* output, uint32_t input_len);

def _neoscrypt_hash(hash):
	cdef unsigned char output[32];
	cdef uint32_t input_len = len(hash);
	neoscrypt_hash(hash, output, input_len);
	return output[:32];