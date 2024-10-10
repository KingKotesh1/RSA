#include <iostream>
#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/nbtheory.h>
#include <cryptopp/files.h>

using namespace std;
using namespace CryptoPP;

// Function to perform modular inverse
Integer ModInverse(const Integer& a, const Integer& n) {
    return a.InverseMod(n);
}

// Function to generate a prime number using a basic method
Integer GeneratePrime(AutoSeededRandomPool& rng, size_t bitSize) {
    Integer prime;
    do {
        prime.Randomize(rng, bitSize);
        // Ensure the number is prime
        if (IsPrime(prime)) {
            break;
        }
    } while (true);
    return prime;
}

// Setup Phase: Generate keys and store them
void SetupPhase() {
    AutoSeededRandomPool rng;

    // Generate two prime numbers p and q
    cout << "Generating p..." << endl;
    Integer p = GeneratePrime(rng, 1024);  // Using smaller bits for faster generation
    cout << "p: " << p << endl;

    Integer q;
    cout << "Generating q..." << endl;
    do {
        q = GeneratePrime(rng, 1024);  // Using smaller bits for faster generation
        cout << "q: " << q << endl;
    } while (q == p);  // Ensure p and q are distinct

    // Calculate n = p * q
    Integer n = p * q;
    cout << "n: " << n << endl;

    // Calculate φ(n) = (p-1) * (q-1)
    Integer phi_n = (p - 1) * (q - 1);
    cout << "phi_n: " << phi_n << endl;

    // Choose d, which is coprime to φ(n)
    Integer d;
    do {
        d.Randomize(rng, 512);  // Using smaller bits for faster generation
    } while (Integer::Gcd(d, phi_n) != 1);
    cout << "d: " << d << endl;

    // Calculate e, which is the modular inverse of d mod φ(n)
    Integer e = ModInverse(d, phi_n);
    cout << "e: " << e << endl;

    // Store public key (e, n) in publickey.bin
    FileSink pubFile("publickey.bin");
    e.DEREncode(pubFile);
    n.DEREncode(pubFile);
    pubFile.MessageEnd();  // Ensure all data is written

    // Store private key (d, n) in privatekey.bin
    FileSink privFile("privatekey.bin");
    d.DEREncode(privFile);
    n.DEREncode(privFile);
    privFile.MessageEnd();  // Ensure all data is written

    cout << "Keys have been generated and stored in binary files." << endl;
}

int main() {
    // Call the SetupPhase function
    SetupPhase();
    return 0;
}