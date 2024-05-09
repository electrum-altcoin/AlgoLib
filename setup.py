#!/usr/bin/python3
import os
from glob import glob
from setuptools import setup, Extension

ROOT_DIR = os.path.dirname(__file__)
if ROOT_DIR == '':
  ROOT_DIR = '.'

SOURCES = [y for x in os.walk(ROOT_DIR) for y in glob(os.path.join(x[0], '*.c'))]
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
    )
]

setup(
    name = "algomodule",
    url = "https://github.com/electrum-altcoin/algomodule",
    author = "Ahmed Bodiwala",
    author_email = "ahmedbodi@crypto-expert.com",
    ext_modules=extensions,
)
