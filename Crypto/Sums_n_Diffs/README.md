# Sums_n_Diffs
  
### Challenge Description  
polynomials... polynomials...

**Challenge File**
+ [Primary Link](./Handout/chall.zip)
+ [Mirror Link]()

**MD5 Hash**: 659500611fbaea0929833cc504b110af
  
### Short Writeup

+ The ascii value of each byte in the flag is taken and the product P of all of these values is calculated.
+ Then, a list with values `Pi` where each value is the total product divided by the ascii value of the ith byte of the flag, is created.
+ Next, a list with values `Di` where each value is `P-Pi` for every ith byte of the flag, is created.
+ Finally, a list with the values `Pi * Di` is created. 
+ The value of P as well as the product list is written to a flag.

This challenge can be solved using the quadratic equation.  
We have:
```
Di = P-Pi
prod = Pi * Di
prod = Pi * (P-Pi)
prod = Pi*P - Pi^2
Pi^2 - Pi*P + prod = 0
```
Since prod and P is known, each Pi can be calculated by finding the root of the equation.  
Calculating P/Pi gives each byte of the flag.  

### Flag

inctfj{qu4dr4t1c_f0rmu14_rul3s}

### Authors

**Ankith**
**Devanandan**    