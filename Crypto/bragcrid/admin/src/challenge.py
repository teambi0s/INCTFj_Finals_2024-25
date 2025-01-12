import binascii
from operator import xor
m1=b"inctfj{to"
m2=b"cribdrag}"
key=b"cribdragwelcomesyou!"
c1=''.join(chr(a^b) for a,b in zip(m1,key))
c2=''.join(chr(c^d) for c,d in zip(m2,key))
print("encrypted message1",binascii.hexlify(c1.encode()))
print("encrypted message2",binascii.hexlify(c2.encode()))
print("flag=??")