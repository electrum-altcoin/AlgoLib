from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "threes/3s.h":
	extern void threes_hash(const char* input, char* output);

def _threes_hash(hash):
	cdef char output[32];
	threes_hash(hash, output);
	return output[:32]