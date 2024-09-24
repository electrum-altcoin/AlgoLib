from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "bcrypt/bcrypt.h":
	extern void bcrypt_hash(const char* input, char* output);

def _bcrypt_hash(hash):
	cdef char output[32];
	bcrypt_hash(hash, output);
	return output[:32];