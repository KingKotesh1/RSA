#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/files.h>
#include <cryptopp/md5.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

// Function to compute the MD5 hash of a file
string ComputeMD5Hash(const string& filePath) {
    Weak::MD5 hash;
    string digest;
    FileSource file(filePath.c_str(), true, new HashFilter(hash, new StringSink(digest)));
    return digest;
}

// Signature Phase: Sign the hash of the message
void SignaturePhase(const string& plaintextFilePath) {
    // Load private key (d, n) from file
    Integer d, n;
    FileSource privFile("privatekey.bin", true);
    d.BERDecode(privFile);
    n.BERDecode(privFile);

    // Compute the hash of the plaintext
    string hashValue = ComputeMD5Hash(plaintextFilePath);

    // Convert hash to Integer
    Integer H_m(reinterpret_cast<const CryptoPP::byte*>(hashValue.data()), hashValue.size());

    // Sign the hash: S ≡ (H(m))^d mod n
    Integer S = a_exp_b_mod_c(H_m, d, n);

    // Store the signed hash in msgSig.bin
    FileSink sigFile("msgSig.bin");
    S.DEREncode(sigFile);

    // Store the original hash in msgHash1.bin
    FileSink hashFile("msgHash1.bin");
    H_m.DEREncode(hashFile);

    cout << "Signature phase complete." << endl;
}



int main() {
    // Example usage
    SignaturePhase("/home/tarun/Desktop/CyberSecurity/Cryptography/Lab7/7B/plain_text.txt");
    return 0;
}
