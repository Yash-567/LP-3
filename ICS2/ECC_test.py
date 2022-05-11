import math
import random

def point(a, b):
    if (4*(a**3)+27*(b*2)) !=0:
        x=1
        while True:
            rhs = x**3 +a*x + b
            y = math.sqrt(rhs)
            lhs = y**2
            if lhs==rhs:
                return [x, y]
            else:
                x = x + 1
    else:
        print("Enter another coefficients!")

a = int(input("Enter coefficient 'a' for the curve: "))
b = int(input("Enter coefficient 'b' for the curve: "))
m = int(input("Enter the input message: "))
generator = point(a, b)

private_a = 13
private_b = 15

public_a = [generator[0]*private_a, generator[1]*private_a]
public_b = [generator[0]*private_b, generator[1]*private_b]

print("Public key A: ", public_a)
print("Public key B: ", public_b)
print("Private key A: ", private_a)
print("Private key B: ", private_b)

k = random.randint(0,10)

c1 = k * (generator[0]+generator[1])
c2 = m + (k* (public_b[0]+public_b[1]))

print("Encrypted point :", [c1, c2])

r = private_b * c1
d = c2 - r
print("Decrypted message: ", d)