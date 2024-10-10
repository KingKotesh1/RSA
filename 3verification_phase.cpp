#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/files.h>
#include <cryptopp/nbtheory.h>

using namespace std;
using namespace CryptoPP;

// Verification Phase: Verify the signature
void VerificationPhase(const string& plaintextFilePath) {
    // Load public key (e, n) from file
    Integer e, n;
    FileSource pubFile("publickey.bin", true);
    e.BERDecode(pubFile);
    n.BERDecode(pubFile);

    // Load the signature (S) from file
    Integer S;
    FileSource sigFile("msgSig.bin", true);
    S.BERDecode(sigFile);

    // Load the original hash (D) from file (msgHash1.bin)
    Integer D;
    FileSource hashFile("msgHash1.bin", true);
    D.BERDecode(hashFile);

    // Verify the signature: D' ≡ S^e mod n
    Integer D_prime = a_exp_b_mod_c(S, e, n);
    cout << "D_prime: " << D_prime << endl;
    cout << "D (Original Hash): " << D << endl;

    // Compare D' with the original hash D
    if (D_prime == D) {
        cout << "Signature is valid." << endl;
    } else {
        cout << "Signature is invalid." << endl;
    }

    // Store the value of D' in msgHash2.bin
    FileSink hashFile2("msgHash2.bin");
    D_prime.DEREncode(hashFile2);
    hashFile2.MessageEnd();  // Ensure all data is written
    cout << "D' has been stored in msgHash2.bin." << endl;
}

int main() {
    VerificationPhase("plaintext.txt");
    return 0;
}
