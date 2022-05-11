import random

p = int(input("Enter a prime number for p: "))
q = int(input("Enter a prime number for q: "))

n = p*q
r = (p-1)*(q-1)

def gcd(a, b):
    if a < b:
        small = a
    else:
        small = b
    for i in range(1, small+1):
        if(a%i)==0 and (b%i)==0:
            gcd = i
    return gcd

e = random.randint(1, r-1)
while(gcd(e, r)!=1):
    e = random.randint(1, r-1)

def mod_inverse(e, r):
    for x in range(1, r): 
        if(((e%r)*(x%r))%r==1):
            return x

d = mod_inverse(e, r)

m = int(input("Enter input message: "))

C = pow(m, e, n)
print("Encrypted message: ", C)

D = pow(C, d, n)
print("Decrypted message: ", D)