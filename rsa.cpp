#include <bits/stdc++.h>
using namespace std;

// Power function (modular exponentiation)
long long power(long long b, long long e, long long m){
    long long r = 1;
    while(e){
        if(e % 2) r = (r * b) % m;
        b = (b * b) % m;
        e /= 2;
    }
    return r;
}

// GCD
long long gcd(long long a, long long b){
    while(b){
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Modular inverse
long long modInverse(long long e, long long phi){
    for(long long d = 2; d < phi; d++)
        if((e * d) % phi == 1)
            return d;
    return -1;
}

int main(){
    long long p, q;
    cout << "Enter prime numbers p and q: ";
    // 23 5
    cin >> p >> q;

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e;
    for(e = 2; e < phi; e++)
        if(gcd(e, phi) == 1)
            break;

    long long d = modInverse(e, phi);

    cout << "Public Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n";

    long long message;
    cout << "Enter message (number): ";
    // 56
    cin >> message;

    long long cipher = power(message, e, n);
    cout << "Encrypted: " << cipher << endl;

    long long decrypted = power(cipher, d, n);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}