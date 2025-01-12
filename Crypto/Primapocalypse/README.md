# Primapocalypse  

### Challenge Description
I was a bit lazy to generate 4 primes but at least the bit length is large right...?

**Challenge File**
+ [Primary Link](./Handout/chall.zip)
+ [Mirror Link]()

**MD5 Hash**: 31bab32c4988a357aa8668f75affeef0
    
### Short Writeup
+ This RSA challenge involves generating a 2048 bit prime as well as the next three primes after that one.  
+ The flag goes through 3 rounds of RSA encryption with N being the product of the first and the second prime and in the next round N is the product of the second and third prime and so on.
+ The ciphertext, e and the product of the first and last prime as well as the product of the 2nd and 3rd prime is written to a file.
  
Solving this challenge involves factoring the two products given with the fermat's factoring algorithm (since the primes are close together).
Since primes are generated in a successive manner, the factored values must be sorted and then the decryption can be done by considering the last two values first.  
  
### Flag

inctfj{n0t_4_t0u4h_p51me_1s_i7}

### Author

**Ankith**
**Devanandan**