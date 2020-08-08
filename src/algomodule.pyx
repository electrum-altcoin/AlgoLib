from libc.stdint cimport uint32_t, int64_t

cdef extern from "scrypt/scrypt.h":
	extern void scrypt_1024_1_1_256(const char* input, char* output);

cdef extern from "bcrypt/bcrypt.h":
	extern void bcrypt_hash(const char* input, char* output);

cdef extern from "keccak/keccak.h":
	extern void keccak_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "quark/quark.h":
	extern void quark_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "skein/skein.h":
	extern void skein_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "x11/x11.h":
	extern void x11_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "groestl/groestl.h":
	extern void groestl_hash(const char* input, char* output, uint32_t input_len);
	extern void groestlmyriad_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "blake/blake.h":
	extern void blake_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "fugue/fugue.h":
	extern void fugue_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "qubit/qubit.h":
	extern void qubit_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "hefty1/hefty1.h":
	extern void hefty1_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "shavite3/shavite3.h":
	extern void shavite3_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "x13/x13.h":
	extern void x13_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "nist5/nist5.h":
	extern void nist5_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "x15/x15.h":
	extern void x15_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "fresh/fresh.h":
	extern void fresh_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "x14/x14.h":
	extern void x14_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "neoscrypt/neoscrypt.h":
	extern void neoscrypt_hash(const char* input, char* output, uint32_t input_len);

cdef extern from "dcrypt/dcrypt.h":
	extern void dcrypt_hash(const char* input, char* output, uint32_t len);


cdef extern from "bitblock/bitblock.h":
	extern void bitblock_hash(const char* input, char* output);

cdef extern from "twe/twe.h":
	extern void twe_hash(const char* input, char* output, uint32_t len);

cdef extern from "3s/3s.h":
	extern void threes_hash(const char* input, char* output);

cdef extern from "jh/jh.h":
	extern void jackpot_hash(const char* input, char* output);

cdef extern from "x17/x17.h":
	extern void x17_hash(const char* input, char* output);

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
	cdef char output[32];
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
