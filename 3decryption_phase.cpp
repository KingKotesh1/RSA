#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

// Decryption Phase
void DecryptionPhase(const string& ciphertextFilePath, const string& plaintextFilePath) {
    // Load private key (d, n) from file
    Integer d, n;
    FileSource privFile("privatekey.bin", true);
    d.BERDecode(privFile);  // Use BERDecode to read Integer from file
    n.BERDecode(privFile);

    // Load the ciphertext from the file
    Integer C;
    FileSource cipherFile(ciphertextFilePath.c_str(), true);
    C.BERDecode(cipherFile);  // Use BERDecode to read the ciphertext

    // Compute plaintext m ≡ C^d mod n
    Integer m = a_exp_b_mod_c(C, d, n);

    // Convert Integer back to plaintext (string)
    string plaintext;
    plaintext.resize(m.MinEncodedSize());  // Resize the string to fit the decoded message
    m.Encode(reinterpret_cast<CryptoPP::byte*>(&plaintext[0]), plaintext.size());  // Encode Integer to byte array

    // Save the plaintext to a file
    ofstream plainFile(plaintextFilePath, ios::binary);  // Open in binary mode
    if (!plainFile.is_open()) {
        cerr << "Error: Unable to open plaintext file for writing." << endl;
        return;
    }

    plainFile.write(plaintext.data(), plaintext.size());  // Write plaintext to file
    plainFile.close();

    cout << "Decryption complete. Plaintext stored in: " << plaintextFilePath << endl;
}

int main() {
    string ciphertextFilePath, plaintextFilePath;
    cout << "Enter the path for the ciphertext file: ";
    cin >> ciphertextFilePath;
    cout << "Enter the path for the plaintext file: ";
    cin >> plaintextFilePath;

    DecryptionPhase(ciphertextFilePath, plaintextFilePath);

    return 0;
}
