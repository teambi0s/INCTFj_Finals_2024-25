flag = "inctfj{?????}"
flag = list(flag.encode())

def product(arr):
    product = 1
    for num in arr:
        product *= num
    return product

def generatePs(arr):
    Ps = []
    for i in range(len(arr)):
        Ps.append(product(arr[:i] + arr[i+1:]))
    return Ps

def generateDs(Ps, P):
    Ds = []
    for i in range(len(Ps)):
        Ds.append(P - Ps[i])
    return Ds

P = product(flag)
Ps = generatePs(flag)
Ds = generateDs(Ps, P)

out = [hex(Ps[i] * Ds[i]) for i in range(len(flag))]

with open('output.txt', 'w') as output_file:
    output_file.write(f"P: {hex(P)}\n")
    output_file.write(f"Out: {out}\n")