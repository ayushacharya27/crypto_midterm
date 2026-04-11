#include <bits/stdc++.h>
using namespace std;

int main() {
    string key;
    int choice;

    cout << "Enter key: ";
    // key123
    getline(cin, key);

    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    vector<int> plaintextBytes;

    if (choice == 1) {
        string plaintext;
        cout << "Enter plaintext: ";
        // hello
        getline(cin, plaintext);

        for (char c : plaintext)
            plaintextBytes.push_back((unsigned char)c);
    }
    else if (choice == 2) {
        string binaryInput;
        cout << "Enter binary plaintext: "; // Multiple of 8
        // 10001000 -> * bits
        getline(cin, binaryInput);

        plaintextBytes = binaryToBytes(binaryInput);
    }


    int S[256], K[256];

    // Key Scheduling Algorithm (KSA)
    for (int i = 0; i < 256; i++) {
        S[i] = i;
        K[i] = key[i % key.length()];
    }

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + K[i]) % 256;
        swap(S[i], S[j]);
    }

    // Pseudo Random Generation Algorithm (PRGA)
    int i = 0;
    j = 0;
    vector<int> keystream;

    for (int n = 0; n < plaintextBytes.size(); n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        swap(S[i], S[j]);

        int t = (S[i] + S[j]) % 256;
        int k = S[t];
        keystream.push_back(k);
    }

    // Encryption
    vector<int> cipher(plaintextBytes.size());

    cout << "\nKeystream: ";
    for (int k : keystream)
        cout << k << " ";

    cout << "\nEncrypted (hex): ";
    for (int n = 0; n < plaintextBytes.size(); n++) {
        cipher[n] = plaintextBytes[n] ^ keystream[n];
        printf("%02X ", cipher[n]);
    }

    // Decryption
    vector<int> decrypted(cipher.size());
    for (int n = 0; n < cipher.size(); n++) {
        decrypted[n] = cipher[n] ^ keystream[n];
    }

    cout << "\nDecrypted: ";
    for (int x : decrypted)
        cout << (char)x;

    cout << endl;
    return 0;
}