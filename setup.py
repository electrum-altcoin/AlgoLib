#!/usr/bin/python3
import os
from glob import glob
from setuptools import setup, find_packages, Extension

EXCLUDE_SOURCES = [
    './src/sha3/haval_helper.c', './src/sha3/md_helper.c'
]

ROOT_DIR = '.'
SOURCES = [y for x in os.walk(ROOT_DIR) for y in glob(os.path.join(x[0], '*.c'))]
INCLUDE_DIRS = [os.path.join(ROOT_DIR, o) for o in os.listdir(ROOT_DIR) if os.path.isdir(os.path.join(ROOT_DIR, o))]

extensions = [
	Extension(
		"algomodule",
		include_dirs=INCLUDE_DIRS + ['/usr/local/include', '/usr/include'],
		sources=list(filter(lambda x: x not in EXCLUDE_SOURCES, SOURCES)),
                libraries=['crypto'],
	)
]

setup(
    name = "algomodule",
    version = "1.0.4",
    url = "https://github.com/electrum-altcoin/algomodule",
    author = "Ahmed Bodiwala",
    author_email = "ahmedbodi@crypto-expert.com",
    ext_modules=extensions,
)
