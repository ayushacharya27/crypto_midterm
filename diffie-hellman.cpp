#include <bits/stdc++.h>
using namespace std;

// modular exponentiation
long long modExp(long long b,long long e,long long m){
    long long r=1;
    while(e){
        if(e&1) r=r*b%m;
        b=b*b%m;
        e>>=1;
    }
    return r;
}

int main(){
    long long p,g;
    cout<<"Enter prime p: ";
    cin>>p;

    cout<<"Enter generator g: ";
    cin>>g;

    // private keys
    long long a,b;
    cout<<"Enter private key of A: ";
    cin>>a;

    cout<<"Enter private key of B: ";
    cin>>b;

    // public keys
    long long A = modExp(g,a,p);
    long long B = modExp(g,b,p);

    cout<<"\nPublic key of A: "<<A;
    cout<<"\nPublic key of B: "<<B;

    // shared secret
    long long keyA = modExp(B,a,p);
    long long keyB = modExp(A,b,p);

    cout<<"\n\nShared key (A computes): "<<keyA;
    cout<<"\nShared key (B computes): "<<keyB<<endl;
}