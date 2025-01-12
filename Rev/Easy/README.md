# ezX0r

### Challenge Description 
Mr.X0r has made it so that you can only get the flag if you run the  program on "1735835350" second after January 1, 1970. So make sure you run the binary at that time.

### Short Writeup
- So this challenge gets time since Jan 1,1970. using the time module in c 
- Uses that said time as a seed for rand()
- Iterates through each character of the flag while xoring it with the output of rand() & 0xff(which can be recreated since we are using a seed) and stores that xor'ed value in file called enc_flag.txt 

### Flag
inctfj{Mr.X0r_5a1d_x0r_1s_sUper}

# Author 
0xea22