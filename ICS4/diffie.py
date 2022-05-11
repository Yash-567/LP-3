sharedPrime = 23
sharedBase = 5
aliceSecret = 6
bobSecret = 16

aPublicKey = (sharedBase**aliceSecret) % sharedPrime
bPublicKey = (sharedBase**bobSecret) % sharedPrime

print("A public key: ", aPublicKey)
print("B public key: ", bPublicKey)

aSharedSecret = (bPublicKey**aliceSecret) % sharedPrime
bSharedSecret = (aPublicKey**bobSecret) % sharedPrime

print("A shared secret key: ", aSharedSecret)
print("B shared secret key: ", bSharedSecret)