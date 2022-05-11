import random 

p = input("Enter prime number for p: ")
q = input("Enter prime numbe for q: ")

p = int(p)
q = int(q)

n = p * q 
r = (p - 1) * (q - 1)

def gcd(e, r):
    while(r != 0):
        e, r = r, e%r
    return e
    
e = random.randint(2, r - 1)
while(gcd(e, r) != 1):
    e = random.randint(2, r - 1)
    
def mod_inverse(e, r): ### IMP
    for x in range(1, r):
        if(((e%r)*(x%r)) % r == 1):
            return x
    return -1

d = mod_inverse(e, r)

m = input("Enter the message you want to encrypt: ")
m = int(m)

C = pow(m, e, n)

print(C)

M = pow(C, d, n)
print(M)