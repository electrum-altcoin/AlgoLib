#!/usr/bin/python3
import os
from glob import glob
from setuptools import setup, Extension

ROOT_DIR = os.path.dirname(__file__)
if ROOT_DIR == '':
  ROOT_DIR = '.'

C_SOURCES = [y for x in os.walk(ROOT_DIR) for y in glob(os.path.join(x[0], '*.c'))]
CPP_SOURCES = [y for x in os.walk(ROOT_DIR) for y in glob(os.path.join(x[0], '*.cpp'))]
SOURCES = C_SOURCES + CPP_SOURCES
INCLUDE_DIRS = [os.path.join(ROOT_DIR, o) for o in os.listdir(ROOT_DIR) if os.path.isdir(os.path.join(ROOT_DIR, o))]
EXCLUDE_SOURCES = [
    os.path.join(ROOT_DIR, 'src', 'sha3', 'haval_helper.c'),
    os.path.join(ROOT_DIR, 'src', 'sha3', 'md_helper.c'),
]

extensions = [
    Extension(
        "algomodule",
        include_dirs=INCLUDE_DIRS,
        sources=list(filter(lambda x: x not in EXCLUDE_SOURCES, SOURCES)),
        extra_compile_args=["-std=c++11"],
    )
]

setup(
    name = "algomodule",
    url = "https://github.com/electrum-altcoin/algomodule",
    author = "Ahmed Bodiwala",
    author_email = "ahmedbodi@crypto-expert.com",
    ext_modules=extensions,
)
