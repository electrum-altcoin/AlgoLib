from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "scrypt/scrypt.h":
	extern void scrypt_1024_1_1_256(const char* input, char* output);


def _ltc_scrypt(hash):
	cdef char output[32];	
	scrypt_1024_1_1_256(hash, output);
	return output[:32];	