from binascii import unhexlify, hexlify
import weakref
import binascii
import unittest
import algomodule

teststart = '700000005d385ba114d079970b29a9418fd0549e7d68a95c7f168621a314201000000000578586d149fd07b22f3a8a347c516de7052f034d2b76ff68e0d6ecff9b77a45489e3fd511732011df0731000'
testbin = unhexlify(teststart)
bin_len = len(testbin)

for algo in dir(algomodule):
	print(algo)
