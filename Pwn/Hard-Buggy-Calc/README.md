# Buggy_Calc

### Challenge Description

This is our new and improved calculator, We introduced some new things such as variables. But in this version you cannot use them directly as it is still in development, so it's just like a notepad for numbers. We are offering you a sample early trial for our service.

**Challenge File**:
+ [Primary Link](https://drive.google.com/file/d/11_LY-vWpRE6qM9CsQIPP5ZlPXTgmQI8J/view?usp=sharing)
+ [Mirror Link](https://1drv.ms/u/s!AmBxw8ypjaxCbUyD91ljrWBkyxE?e=4WnlnZ)

**MD5 Hash**: 41aaf3321308a31275b3b4a1573ae94a

### Short Writeup

+  Bug - The user can call a function pointer at index -1 because the option 0 is not restricted in operations but is an invalid operation
+  Exploitation - Use the variables to set the function pointer and call printf to get libc leak after which you may use a one_gadget or a system("sh") call to gain a shell.
+ The sh string exists within the strings that are printed out in "sta'sh'"

### Flag

inctfj{Fun7ion_P7rs__U5e_th3m_w3ll_93iuehf}

### Author

**R0R1**