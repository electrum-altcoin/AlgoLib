#!/usr/bin/python3
import os
from glob import glob
from setuptools import setup, find_packages, Extension

try:
    from Cython.Build import cythonize
except ImportError:
    cythonize = None

EXCLUDE_SOURCES = [
	'./src/sha3/haval_helper.c', './src/sha3/md_helper.c'
]

ROOT_DIR = '.'
SOURCES = [y for x in os.walk(ROOT_DIR) for y in glob(os.path.join(x[0], '*.c'))]
INCLUDE_DIRS = [os.path.join(ROOT_DIR, o) for o in os.listdir(ROOT_DIR) if os.path.isdir(os.path.join(ROOT_DIR, o))]

extensions = [
	Extension(
		"algomodule", 
		include_dirs=INCLUDE_DIRS,
		sources=list(filter(lambda x: x not in EXCLUDE_SOURCES, SOURCES)),
		extra_compile_args=['-lcrypto'],
		extra_link_args=['-lcrypto'],
	)
]

# https://cython.readthedocs.io/en/latest/src/userguide/source_files_and_compilation.html#distributing-cython-modules
def no_cythonize(extensions, **_ignore):
    for extension in extensions:
        sources = []
        for sfile in extension.sources:
            path, ext = os.path.splitext(sfile)
            if ext in (".pyx", ".py"):
                if extension.language == "c++":
                    ext = ".cpp"
                else:
                    ext = ".c"
                sfile = path + ext
            sources.append(sfile)
        extension.sources[:] = sources
    return extensions


CYTHONIZE = bool(int(os.getenv("CYTHONIZE", 0))) and cythonize is not None

if CYTHONIZE:
    compiler_directives = {"language_level": 3, "embedsignature": True}
    extensions = cythonize(extensions, compiler_directives=compiler_directives)
else:
    extensions = no_cythonize(extensions)

setup(
    name = "algomodule",
    version = "1.0.1",
    url = "https://github.com/electrum-altcoin/algomodule",
    author = "Ahmed Bodiwala",
    author_email = "ahmedbodi@crypto-expert.com",
    ext_modules=extensions,
)
