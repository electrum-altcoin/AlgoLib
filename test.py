from binascii import unhexlify, hexlify
import weakref
import binascii
import StringIO
import unittest
import algomodule

teststart = '700000005d385ba114d079970b29a9418fd0549e7d68a95c7f168621a314201000000000578586d149fd07b22f3a8a347c516de7052f034d2b76ff68e0d6ecff9b77a45489e3fd511732011df0731000'
testbin = unhexlify(teststart)

class AlgoTest(unittest.TestCase):
    def test_scrypt(self):
	import ltc_scrypt
	scrypt_new = algomodule._ltc_scrypt(testbin)
	scrypt_old = ltc_scrypt.getPoWHash(testbin)
	self.assertTrue(scrypt_new == scrypt_old)

    def test_quark(self):
	import quark_hash
	quark_new = algomodule._quark_hash(testbin)
	quark_old = quark_hash.getPoWHash(testbin)
	self.assertTrue(quark_new == quark_old)

    def test_x11(self):
	import drk_hash
	x11_new = algomodule._x11_hash(testbin)
	x11_old = drk_hash.getPoWHash(testbin)
	self.assertTrue(x11_new == x11_old)

if __name__ == "__main__":
   unittest.main()
   for algo in dir(algomodule):
	print(algo)
