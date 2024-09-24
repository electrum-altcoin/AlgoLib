from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "x17/x17.h":
	extern void x17_hash(const char* input, char* output);

def _x17_hash(hash):
	cdef char output[32]
	x17_hash(hash, output);
	return output[:32]