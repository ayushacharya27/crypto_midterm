#include <bits/stdc++.h>
using namespace std;

int main() {
    string key, plaintext;
    cout << "Enter key: ";
    // key123
    getline(cin, key);

    cout << "Enter plaintext: ";
    // hello
    getline(cin, plaintext);

    int S[256], K[256];

    // Key Scheduling 
    for (int i = 0; i < 256; i++) {
        S[i] = i;
        K[i] = key[i % key.length()];
    }

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + K[i]) % 256;
        swap(S[i], S[j]);
    }

    // Key Stream Generation 
    int i = 0;
    j = 0;

    vector<int> keystream;

    for (int n = 0; n < plaintext.length(); n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        swap(S[i], S[j]);

        int t = (S[i] + S[j]) % 256;
        int k = S[t];   // keystream byte

        keystream.push_back(k);
    }

    // Encryption (XOR) 
    string cipher = plaintext;

    cout << "\nKeystream: ";
    for (int k : keystream) cout << k << " ";

    cout << "\nEncrypted (hex): ";
    for (int n = 0; n < plaintext.length(); n++) {
        cipher[n] = plaintext[n] ^ keystream[n];
        printf("%02X ", (unsigned char)cipher[n]);
    }

    // Decryption 
    string decrypted = cipher;
    for (int n = 0; n < cipher.length(); n++) {
        decrypted[n] = cipher[n] ^ keystream[n];
    }

    cout << "\nDecrypted: " << decrypted << endl;

    return 0;
}