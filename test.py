from binascii import unhexlify, hexlify
import weakref
import binascii
import StringIO
import unittest
import algomodule

teststart = '700000005d385ba114d079970b29a9418fd0549e7d68a95c7f168621a314201000000000578586d149fd07b22f3a8a347c516de7052f034d2b76ff68e0d6ecff9b77a45489e3fd511732011df0731000'
testbin = unhexlify(teststart)
bin_len = len(testbin)

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

    def test_x13(self):
	import x13_hash
	x13_new = algomodule._x13_hash(testbin)
	x13_old = x13_hash.getPoWHash(testbin)
	self.assertTrue(x13_new == x13_old)

    def test_x14(self):
	import x14_hash
	x14_new = algomodule._x14_hash(testbin)
	x14_old = x14_hash.getPoWHash(testbin)
	self.assertTrue(x14_new == x14_old)

    def test_x15(self):
	import x15_hash
	x15_new = algomodule._x15_hash(testbin)
	x15_old = x15_hash.getPoWHash(testbin)
	self.assertTrue(x15_new == x15_old)

    def test_x17(self):
	import crypto_hash as x17_hash
	x17_new = algomodule._x17_hash(testbin)
	x17_old = x17_hash.getPoWHash(testbin)
	self.assertTrue(x17_new == x17_old)

    def test_bitblock(self):
	import bitblock_hash
	bitblock_new = algomodule._bitblock_hash(testbin)
	bitblock_old = bitblock_hash.getPoWHash(testbin)
	self.assertTrue(bitblock_new == bitblock_old)

    def test_blake(self):
	import blake_hash
	blake_new = algomodule._blake_hash(testbin)
	blake_old = blake_hash.getPoWHash(testbin)
	self.assertTrue(blake_new == blake_old)

    def test_dcrypt(self):
	import dcrypt_hash
	dcrypt_new = algomodule._dcrypt_hash(testbin)
	dcrypt_old = dcrypt_hash.getPoWHash(testbin)
	self.assertTrue(dcrypt_new == dcrypt_old)

    def test_fresh(self):
        import fresh_hash
        fresh_new = algomodule._fresh_hash(testbin)
        fresh_old = fresh_hash.getPoWHash(testbin)
        self.assertTrue(fresh_new == fresh_old)

    def test_fugue(self):
	import fugue_hash
	fugue_new = algomodule._fugue_hash(testbin)
	fugue_old = fugue_hash.getPoWHash(testbin)
	self.assertTrue(fugue_new == fugue_old)

    def test_qubit(self):
	import qubit_hash
	qubit_new = algomodule._qubit_hash(testbin)
	qubit_old = qubit_hash.getPoWHash(testbin)
	self.assertTrue(qubit_new == qubit_old)

    def test_twe(self):
	import twehash
	twe_new = algomodule._twe_hash(testbin)
	twe_old = twehash.getHash(testbin, bin_len)
	self.assertTrue(twe_new == twe_old)

    def test_mgroestl(self):
        import groestl_hash
        groestl_new = algomodule._mgroestl_hash(testbin)
        groestl_old = groestl_hash.getPoWHash(testbin)
        self.assertTrue(groestl_new == groestl_old)

    def test_groestl(self):
        import groestlcoin_hash
        groestlcoin_new = algomodule._groestl_hash(testbin)
        groestlcoin_old = groestlcoin_hash.getHash(testbin, bin_len)
        self.assertTrue(groestlcoin_new == groestlcoin_old)

    def test_yescrypt(self):
	import yescrypt_hash
	yescrypt_new = algomodule._yescrypt_hash(testbin)
	yescrypt_old = yescrypt_hash.getHash(testbin, bin_len)
	self.assertTrue(yescrypt_new == yescrypt_old)

    def test_nist(self):
	import nist5_hash
	nist5_new = algomodule._nist5_hash(testbin)
	nist5_old = nist5_hash.getPoWHash(testbin)
	self.assertTrue(nist5_new == nist5_old)

    def test_neoscrypt(self):
	import neoscrypt
	neoscrypt_new = algomodule._neoscrypt_hash(testbin)
	neoscrypt_old = neoscrypt.getPoWHash(testbin)
	self.assertTrue(neoscrypt_new == neoscrypt_old)

    def test_lyra2re(self):
	import lyra2re_hash
	lyra2re_new = algomodule._lyra2re_hash(testbin)
	lyra2re_old = lyra2re_hash.getPoWHash(testbin)
	print(hexlify(lyra2re_new), hexlify(lyra2re_old))
	self.assertTrue(lyra2re_new == lyra2re_old)

    def test_jh(self):
	import jackpotcoin_hash
	jh_new = algomodule._jackpot_hash(testbin)
	jh_old = jackpotcoin_hash.gethash(testbin)
	self.assertTrue(jh_new == jh_old)

    def test_hefty1(self):
	import heavycoin_hash
	hefty1_new = algomodule._hefty1_hash(testbin)
	hefty1_old = heavycoin_hash.getHash(testbin, bin_len)
	self.assertTrue(hefty1_new == hefty1_old)

    def test_skein(self):
	import skeinhash
	skein_new = algomodule._skein_hash(testbin)
	skein_old = skeinhash.getPoWHash(testbin)
	self.assertTrue(skein_new == skein_old)

    def test_threes(self):
	import onecoin_3s
	threes_new = algomodule._threes_hash(testbin)
	threes_old = onecoin_3s.getPoWHash(testbin)
	self.assertTrue(threes_new == threes_old)

if __name__ == "__main__":
   unittest.main()
   for algo in dir(algomodule):
	print(algo)
