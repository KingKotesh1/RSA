RSA Encryption and Digital Signature System
This repository contains the implementation of the RSA Encryption System and the RSA Digital Signature System. The project uses core cryptographic functionality from the Crypto++ library and implements the following phases:

RSA Encryption System
1. Setup Phase
In this phase, we generate the two large prime numbers p and q, ensuring that p ≠ q. We then compute:

n = p * q
Φ(n) = (p - 1) * (q - 1)
Next, we generate:

Private Key (d): A random integer such that d is coprime to Φ(n).
Public Key (e): The inverse of d modulo Φ(n), i.e., e ≡ d⁻¹ mod Φ(n).
Once generated:

The public key (e, n) is stored in a binary file named publickey.bin.
The private key (d, n) is stored in a separate binary file privatekey.bin.
All intermediary values of p, q, and Φ(n) are discarded after the key generation for security purposes.

2. Encryption Phase
The public key (e, n) is used to encrypt plaintext data.

The user provides the plaintext file path.
Ciphertext (C) is generated as C ≡ mᵉ mod n (where m is the plaintext message).
3. Decryption Phase
The private key (d, n) is used to decrypt the ciphertext.

The decrypted plaintext message m is computed as m ≡ Cᵈ mod n.
RSA Digital Signature System
1. Setup Phase
Similar to the encryption system, this phase involves generating the public and private keys.

The public key (e, n) and private key (d, n) are generated and stored in publickey.bin and privatekey.bin.
2. Signature Phase
To create a digital signature:

A hash of the plaintext message is generated using the md5sum algorithm.
The hash is signed with the private key (d) to produce the signature (S):
S ≡ (H(m))ᵈ mod n
The hash is stored in a file named msgHash1.bin.
3. Verification Phase
To verify the authenticity of the signed message:

The recipient uses the public key (e, n) to check the signature. If the computed hash from the signature matches the original hash, the message is verified.
Requirements
Crypto++ Library: This project uses the classes Integer, PrimeAndGenerator, and AutoSeededRandomPool from Crypto++.
The use of external functions beyond those specified is not allowed.
How to Run
Clone this repository.
Follow the steps in the setup phase to generate keys.
Use the encryption or digital signature system by running the respective scripts with appropriate inputs (plaintext file, ciphertext, etc.).
