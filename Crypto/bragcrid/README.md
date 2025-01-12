# bragcrid
### Challenge Description

Two messages are xored with the same key to get these two encrypted messages. Now I can't give you the key, these messages could be of some help perhaps?

encrypted message1= b'0a1c0a1602181a1318'
encrypted message2= b'00000000000000000a'
flag=??

**Challenge File**:
+ [Primary Link](".\Handout\chall.zip")

**MD5 Hash**: 20283d3a0cf3e7ef15491de3094fda06

### Short Writeup

+  Crib drag is the principle used in the challenge
+  Procedure to solve:  
1) xor the two ciphertexts to get a combine_xored_ciphertext   
2) 2)Now, xor this combine_xored_ciphertext with guess words of the message to get parts of the flag
+ The flag placeholder "inctfj{" when xored with combine_xored_ciphertext will give the flag

### Flag

inctfj{tocribdrag}

### Author

Parvathy