from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "x16rv2/x16rv2.h":
	extern void x16rv2_hash(const char* input, char* output);

def _x16rv2_hash(hash):
	cdef char output[32]
	x16rv2_hash(hash, output);
	return output[:32]
