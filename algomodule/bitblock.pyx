from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "bitblock/bitblock.h":
	extern void bitblock_hash(const char* input, char* output);

def _bitblock_hash(hash):
	cdef char output[32];
	bitblock_hash(hash, output);
	return output[:32];