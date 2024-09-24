#!/usr/bin/python3
import os
from glob import glob
from setuptools import setup, Extension

ROOT_DIR = os.path.dirname(__file__)
if ROOT_DIR == '':
  ROOT_DIR = '.'


def scandir(dir, files=[]):
    for file in os.listdir(dir):
        path = os.path.join(dir, file)
        if os.path.isfile(path) and path.endswith(".pyx"):
            files.append(path.replace(os.path.sep, ".")[:-4])
        elif os.path.isdir(path):
            scandir(path, files)
    return files


def getFiles(folder, extension):
    res =  [y for x in os.walk(folder) for y in glob(os.path.join(x[0], extension))]

    if 'sha3' in folder:
        EXCLUDE_SOURCES = [
            os.path.join(folder, 'haval_helper.c'),
            os.path.join(folder, 'md_helper.c'),
        ]
        return list(filter(lambda x: x not in EXCLUDE_SOURCES, res))
    return res

# generate an Extension object from its dotted name
def makeExtension(extName):
    EXT_DIR = extName.replace(".", os.path.sep)
    SOURCES = getFiles(EXT_DIR, '*.c') + getFiles(EXT_DIR, '*.cpp')
    LANGUAGE = None
    EXTRA_COMPILE_ARGS = []

    is_cpp = [item for item in SOURCES if any([word in item for word in ['cpp']])]
    if is_cpp:
        LANGUAGE = 'c++'
        EXTRA_COMPILE_ARGS = ['-std=c++11']
        SOURCES += [EXT_DIR+'.cpp']
    else:
        SOURCES += [EXT_DIR+'.c']
        PARENT_DIR = os.path.join(EXT_DIR, '..')
        SOURCES += getFiles(os.path.join(PARENT_DIR, 'core'), '*.c')
        SOURCES += getFiles(os.path.join(PARENT_DIR, 'sha3'), '*.c')

    return Extension(
        extName,
        include_dirs = ["."],
        sources=SOURCES,
        extra_compile_args=EXTRA_COMPILE_ARGS,
        language=LANGUAGE,
    )

extNames = scandir("algomodule")
extensions = [makeExtension(name) for name in extNames]

setup(
    name = "algomodule",
    url = "https://github.com/electrum-altcoin/algomodule",
    author = "Ahmed Bodiwala",
    author_email = "ahmedbodi@crypto-expert.com",
    packages = [
      'algomodule',
      'algomodule.core',
      'algomodule.threes',
      'algomodule.bcrypt',
      'algomodule.bitblock',
      'algomodule.blake',
      'algomodule.dcrypt',
      'algomodule.fresh',
      'algomodule.fugue',
      'algomodule.groestl',
      'algomodule.hefty1',
      'algomodule.jackpot',
      'algomodule.keccak',
      'algomodule.meraki',
      'algomodule.meraki.meraki',
      'algomodule.meraki.keccak',
      'algomodule.meraki.support',
      'algomodule.neoscrypt',
      'algomodule.nist5',
      'algomodule.quark',
      'algomodule.qubit',
      'algomodule.scrypt',
      'algomodule.sha256',
      'algomodule.sha3',
      'algomodule.shavite3',
      'algomodule.skein',
      'algomodule.twe',
      'algomodule.x11',
      'algomodule.x13',
      'algomodule.x14',
      'algomodule.x15',
      'algomodule.x16rv2',
      'algomodule.x17'
    ],
    ext_modules=extensions,
    #cmdclass = {'build_ext': build_ext},
)
