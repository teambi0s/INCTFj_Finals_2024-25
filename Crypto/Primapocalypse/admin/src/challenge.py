from Crypto.Util.number import getPrime, bytes_to_long as b2l
from sympy import nextprime

flag = b2l(b"inctfj{n0t_4_t0u4h_p51me_1s_i7}")

L = [getPrime(2048)]
for i in range(3):
    L.append(nextprime(L[-1]))

e = 0x10001

cipher = flag
for i in range(3):
    a, b = L[i], L[i + 1]
    N = a * b
    cipher = pow(cipher, e, N)

with open('output.txt', 'w') as output_file:
    output_file.write(f"cipher: {hex(cipher)}\n")
    output_file.write(f"e: {hex(e)}\n")
    output_file.write(f"leak: {hex(L[0]*L[3])}, {hex(L[1]*L[2])}\n")