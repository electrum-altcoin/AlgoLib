from libc.stdint cimport uint32_t, int64_t, uint8_t, uint64_t
from libc.stdlib cimport malloc, free
from libc.string cimport memcpy

cdef extern from "core/scrypt/scrypt.h":
	extern void scrypt_1024_1_1_256(const char* input, char* output);

cdef extern from "core/bcrypt/bcrypt.h":
	extern void bcrypt_hash(const char* input, char* output);

cdef extern from "core/keccak/keccak.h":
	extern void keccak_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/quark/quark.h":
	extern void quark_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/skein/skein.h":
	extern void skein_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/x11/x11.h":
	extern void x11_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/groestl/groestl.h":
	extern void groestl_hash(const char* input, char* output, uint32_t input_len);
	extern void groestlmyriad_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/blake/blake.h":
	extern void blake_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/fugue/fugue.h":
	extern void fugue_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/qubit/qubit.h":
	extern void qubit_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/hefty1/hefty1.h":
	extern void hefty1_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/shavite3/shavite3.h":
	extern void shavite3_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/x13/x13.h":
	extern void x13_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/nist5/nist5.h":
	extern void nist5_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/x15/x15.h":
	extern void x15_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/fresh/fresh.h":
	extern void fresh_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/x14/x14.h":
	extern void x14_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "core/neoscrypt/neoscrypt.h":
	extern void neoscrypt_hash(const unsigned char* input, unsigned char* output, uint32_t input_len);

cdef extern from "core/dcrypt/dcrypt.h":
	extern void dcrypt_hash(const char* input, char* output, uint32_t len);

cdef extern from "core/bitblock/bitblock.h":
	extern void bitblock_hash(const char* input, char* output);

cdef extern from "core/twe/twe.h":
	extern void twe_hash(const char* input, char* output, uint32_t len);

cdef extern from "core/3s/3s.h":
	extern void threes_hash(const char* input, char* output);

cdef extern from "core/jh/jh.h":
	extern void jackpot_hash(const char* input, char* output);

cdef extern from "core/x17/x17.h":
	extern void x17_hash(const char* input, char* output);

cdef extern from "core/x16rv2/x16rv2.h":
	extern void x16rv2_hash(const char* input, char* output);

def _ltc_scrypt(hash):
	cdef char output[32];	
	scrypt_1024_1_1_256(hash, output);
	return output[:32];	

def _bcrypt_hash(hash):
	cdef char output[32];
	bcrypt_hash(hash, output);
	return output[:32];

def _keccak_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	keccak_hash(hash, output, input_len);
	return output[:32];

def _quark_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	quark_hash(hash, output, input_len);
	return output[:32];

def _skein_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	skein_hash(hash, output, input_len);
	return output[:32];

def _x11_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	x11_hash(hash, output, input_len);
	return output[:32];

def _groestl_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	groestl_hash(hash, output, input_len);
	return output[:32];

def _mgroestl_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	groestlmyriad_hash(hash, output, input_len);
	return output[:32];

def _blake_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	blake_hash(hash, output, input_len);
	return output[:32];

def _fugue_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	fugue_hash(hash, output, input_len);
	return output[:32];

def _qubit_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	qubit_hash(hash, output, input_len);
	return output[:32];

def _hefty1_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	hefty1_hash(hash, output, input_len);
	return output[:32];

def _shavite3_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	shavite3_hash(hash, output, input_len);
	return output[:32];

def _x13_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	x13_hash(hash, output, input_len);
	return output[:32];

def _nist5_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	nist5_hash(hash, output, input_len);
	return output[:32];

def _x15_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	x15_hash(hash, output, input_len);
	return output[:32];

def _fresh_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	fresh_hash(hash, output, input_len);
	return output[:32];

def _x14_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	x14_hash(hash, output, input_len);
	return output[:32];

def _neoscrypt_hash(hash):
	cdef unsigned char output[32];
	cdef uint32_t input_len = len(hash);
	neoscrypt_hash(hash, output, input_len);
	return output[:32];

def _dcrypt_hash(hash):
	cdef char output[32];
	cdef int input_len = len(hash);
	dcrypt_hash(hash, output, input_len);
	return output[:32];

def _bitblock_hash(hash):
	cdef char output[32];
	bitblock_hash(hash, output);
	return output[:32];

def _twe_hash(hash):
	cdef char output[32];
	cdef uint32_t input_len = len(hash);
	twe_hash(hash, output, input_len);
	return output[:32];

def _threes_hash(hash):
	cdef char output[32];
	threes_hash(hash, output);
	return output[:32]

def _jackpot_hash(hash):
	cdef char output[32]
	jackpot_hash(hash, output);
	return output[:32]

def _x17_hash(hash):
	cdef char output[32]
	x17_hash(hash, output);
	return output[:32]

def _x16rv2_hash(hash):
	cdef char output[32]
	x16rv2_hash(hash, output);
	return output[:32]
