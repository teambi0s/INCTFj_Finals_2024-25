# Choc Shop

### Challenge Description

Welcome to my chocolate store. Can you find out what my favourite type of chocolate is?

**Challenge File**:
+ [Primary Link](https://drive.google.com/file/d/1__OMkrSBZdXYsrHq2jorGHJ9VD3anwu4/view?usp=sharing)
+ [Mirror Link](https://1drv.ms/u/c/d7b26a698efc06c2/EdjwL4d5amlOosE5fKQ1fuwBr3j1H7xQPU1NxXD3xj0UeQ?e=QTdrfb)

**MD5 Hash**: 1065b3d0b73e163342ece4399c5fe128 

### Short Writeup

+ The challenge gives us a menu asking us what chocolate we would prefer.
+ If you choose the dark chocolate path, we find a format string vulnerability where it asks for our name.
+ The program also provides us with a ret2win function.
+ Using the format string we can overwrite the GOT entry of exit with the ret2win function and answer NO at the "Would you like some chocolate?" prompt so that exit is called.
+ The ret2win function asks us "What is my preferred chocolate type?" as a final check before giving us the flag.
+ The string we enter is compared using strstr() which means we can put every chocolate type in a single string since strstr() only checks whether the required string is present within the string we enter.
+ This bypasses the check and we get the flag.

### Flag

inctfj{d4rk_ch0c0l4t3_15_my_f4v0ur1t3_$T3mN#9}

### Author

**B4tMite**
