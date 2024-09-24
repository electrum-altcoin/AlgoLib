from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "dcrypt/dcrypt.h":
	extern void dcrypt_hash(const char* input, char* output, uint32_t len);

def _dcrypt_hash(hash):
	cdef char output[32];
	cdef int input_len = len(hash);
	dcrypt_hash(hash, output, input_len);
	return output[:32];