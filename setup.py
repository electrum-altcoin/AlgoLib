try:
	from setuptools import setup, Extension
except:
	from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(
    ext_modules = cythonize(Extension("algomodule", 
    include_dirs=['.','./scrypt','./bcrypt','./bitblock','./blake','./crypto','./cryptonight','./dcrypt',
		  './fresh','./fugue','./groestl','./hefty1','./keccak','./lyra2re','./neoscrypt','./nist5','./quark',
		  './qubit','./sha1','./sha3','./shavite3','./skein','./x11','./x13','./x14','./x15','./yescrypt',
		  './twe','./3s','./x17','./jh'],
    sources = ['algomodule.pyx','scrypt/scrypt.c','bcrypt/bcrypt.c','bitblock/bitblock.c','blake/blake.c',
	       'cryptonight/cryptonight.c', 'dcrypt/dcrypt.c', 'fresh/fresh.c','fugue/fugue.c','groestl/groestl.c',
	       'hefty1/hefty1.c', 'keccak/keccak.c','lyra2re/Lyra2RE.c','neoscrypt/neoscrypt.c','nist5/nist5.c','quark/quark.c',
	       'qubit/qubit.c', 'sha1/sha1.c', 'shavite3/shavite3.c','skein/skein.c','x11/x11.c','x13/x13.c','x14/x14.c',
	       'x15/x15.c','sha3/aes_helper.c','sha3/sph_blake.c','sha3/sph_fugue.c',    
	       'sha3/sph_keccak.c','sha3/sph_simd.c','sha3/hamsi.c','sha3/sph_bmw.c','sha3/sph_groestl.c','sha3/sph_luffa.c',
	       'sha3/sph_skein.c','sha3/hamsi_helper.c','sha3/sph_cubehash.c','sha3/sph_hefty1.c','sha3/sph_shabal.c',
	       'sha3/sph_whirlpool.c','sha3/sph_echo.c','sha3/sph_jh.c','sha3/sph_shavite.c', 'crypto/hash.c','crypto/aesb.c',
	       'crypto/oaes_lib.c','crypto/c_groestl.c','crypto/c_keccak.c','crypto/c_blake256.c','crypto/c_jh.c',
	       'crypto/c_skein.c','lyra2re/crypto/Lyra2.c', 'lyra2re/crypto/Sponge.c', 'yescrypt/yescrypt.c',
	       'yescrypt/yescrypt-opt.c','yescrypt/sha256_Y.c','twe/twe.c','sha3/sph_panama.c', 'x17/x17.c', '3s/3s.c',
	       'sha3/sph_haval.c','sha3/hamsi_helper.c','sha3/sha2big.c', 'jh/jh.c'],
   extra_compile_args = ['-lcrypto'],
   extra_link_args = ['-lcrypto']
)))
