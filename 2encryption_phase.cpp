#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

// Encryption Phase
void EncryptionPhase(const string& plaintextFilePath, const string& ciphertextFilePath) {
    // Load public key (e, n) from file
    Integer e, n;
    FileSource pubFile("publickey.bin", true);
    e.BERDecode(pubFile);  // Use BERDecode to read Integer from file
    n.BERDecode(pubFile);

    // Read the plaintext from the file
    ifstream plainFile(plaintextFilePath, ios::binary);
    if (!plainFile.is_open()) {
        cerr << "Error: Unable to open plaintext file." << endl;
        return;
    }

    string plaintext((istreambuf_iterator<char>(plainFile)), istreambuf_iterator<char>());
    plainFile.close();

    // Convert plaintext to Integer (use CryptoPP::byte to avoid ambiguity)
    const CryptoPP::byte* plaintextBytes = reinterpret_cast<const CryptoPP::byte*>(plaintext.data());
    Integer m(plaintextBytes, plaintext.size());  // Properly cast plaintext data to byte array

    // Compute ciphertext C ≡ m^e mod n
    Integer C = a_exp_b_mod_c(m, e, n);

    // Store the ciphertext in a binary file using FileSink (BufferedTransformation)
    FileSink cipherFile(ciphertextFilePath.c_str(), true);  // Use FileSink instead of ofstream
    C.DEREncode(cipherFile);  // Save the ciphertext as a binary file

    cout << "Encryption complete. Ciphertext stored in: " << ciphertextFilePath << endl;
}

int main() {
    // Get file paths from user
    string plaintextFilePath, ciphertextFilePath;
    cout << "Enter the path for the plaintext file: ";
    cin >> plaintextFilePath;
    cout << "Enter the path for the ciphertext file: ";
    cin >> ciphertextFilePath;

    // Call the EncryptionPhase function with user-provided paths
    EncryptionPhase(plaintextFilePath, ciphertextFilePath);

    return 0;
}
