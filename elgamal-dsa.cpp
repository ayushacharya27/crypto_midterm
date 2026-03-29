#include <bits/stdc++.h>
using namespace std;

// Fast modular exponentiation
long long modExp(long long b,long long e,long long m){
    long long r=1;
    while(e){
        if(e&1) r=(r*b)%m;
        b=(b*b)%m;
        e>>=1;
    }
    return r;
}

// GCD
long long gcd(long long a,long long b){
    return b==0?a:gcd(b,a%b);
}

// Modular inverse (brute)
long long modInv(long long a,long long m){
    for(long long i=1;i<m;i++)
        if((a*i)%m==1) return i;
    return -1;
}

int main(){
    long long p,g,x,m,k;

    cout<<"Enter prime p: ";
    // 23
    cin>>p;

    cout<<"Enter generator g: ";
    // 5
    cin>>g;

    cout<<"Enter private key x (<p): ";
    // 6
    cin>>x;

    cout<<"Enter message (number < p): ";
    // 10
    cin>>m;

    // Public key
    long long y = modExp(g,x,p);
    cout<<"\nPublic key y: "<<y<<endl;

    // Choose k (coprime with p-1)
    cout<<"Enter random k (gcd(k,p-1)=1): ";
    // 7
    cin>>k;

    // -------- SIGN --------
    long long r = modExp(g,k,p);
    long long k_inv = modInv(k,p-1);
    long long s = (k_inv * (m - x*r)) % (p-1);
    if(s<0) s += (p-1);

    cout<<"\nSignature (r,s): ("<<r<<","<<s<<")"<<endl;

    // -------- VERIFY --------
    long long v1 = modExp(g,m,p);
    long long v2 = (modExp(y,r,p) * modExp(r,s,p)) % p;

    cout<<"\nVerification:\n";
    cout<<"g^m mod p = "<<v1<<endl;
    cout<<"y^r * r^s mod p = "<<v2<<endl;

    if(v1==v2) cout<<"Signature VALID\n";
    else cout<<"Signature INVALID\n";
}