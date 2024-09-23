#!/usr/bin/python3
import os
import sys
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


# generate an Extension object from its dotted name
def makeExtension(extName):
    EXT_DIR = extName.replace(".", os.path.sep)
    SOURCES =  [y for x in os.walk(extName.replace(".", os.path.sep)) for y in glob(os.path.join(x[0], '*.c'))]
    SOURCES += [y for x in os.walk(extName.replace(".", os.path.sep)) for y in glob(os.path.join(x[0], '*.cpp'))]
    EXCLUDE_SOURCES = [
        os.path.join(EXT_DIR, 'sha3', 'haval_helper.c'),
        os.path.join(EXT_DIR, 'sha3', 'md_helper.c'),
    ]

    LANGUAGE = None,
    EXTRA_COMPILE_ARGS = []
    
    is_cpp = [item for item in SOURCES if any([word in item for word in ['cpp']])]
    if is_cpp:
        print(SOURCES)
        LANGUAGE = 'c++'
        EXTRA_COMPILE_ARGS = ['-std=c++11']
        SOURCES += [EXT_DIR+'.cpp']
    else:
        SOURCES += [EXT_DIR+'.c']

    print(SOURCES)
    return Extension(
        extName,
        include_dirs = ["."],
        sources=list(filter(lambda x: x not in EXCLUDE_SOURCES, SOURCES)),
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
      'algomodule.meraki',
    ],
    ext_modules=extensions,
    #cmdclass = {'build_ext': build_ext},
)
