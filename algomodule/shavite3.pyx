from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "shavite3/shavite3.h":
	extern void shavite3_hash(const char* input, char* output, uint32_t input_len);

def _shavite3_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	shavite3_hash(hash, output, input_len);
	return output[:32];