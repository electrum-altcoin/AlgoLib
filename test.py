from binascii import unhexlify, hexlify
import weakref
import binascii
import unittest
import algomodule

'''
header_hash = b'\xa0\xb4\x06RU\xf0\xdd\xee\xeb\x0e\xbc\xf4\xd7/H\x16\x9b\xac\xe3\x06\x1fu\x1e\xfb\x15\x11]3\x88\x17a?'
mix_hash = b'\xc2K\x92;s\xe8o\x84M\xccN\x90\x0b\x85Z\xb7\x06\x90\x96\xc5\x9ab\x8d\xc7\xbd\xc1\x9bD\x1d\xac\x08\xe1'
nonce = 14613617863994149989

print(algomodule.meraki._meraki_hash(header_hash, mix_hash, nonce))

teststart = '700000005d385ba114d079970b29a9418fd0549e7d68a95c7f168621a314201000000000578586d149fd07b22f3a8a347c516de7052f034d2b76ff68e0d6ecff9b77a45489e3fd511732011df0731000'
testbin = unhexlify(teststart)
bin_len = len(testbin)

print(algomodule.core._quark_hash(testbin))
'''
