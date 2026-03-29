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

// Modular inverse
long long modInv(long long a,long long m){
    for(long long i=1;i<m;i++)
        if((a*i)%m==1) return i;
    return -1;
}

int main(){
    long long p,q,g,x,k,h;

    cout<<"Enter p (prime): ";
    // 23
    cin>>p;

    cout<<"Enter q (prime divisor of p-1): ";
    // 11
    cin>>q;

    cout<<"Enter g: ";
    // 2
    cin>>g;

    cout<<"Enter private key x (<q): ";
    // 3
    cin>>x;

    cout<<"Enter message hash h: ";
    // 5
    cin>>h;

    // -------- KEY GENERATION --------
    long long y = modExp(g,x,p);
    cout<<"\nPublic key y: "<<y<<endl;

    // -------- SIGNATURE --------
    cout<<"Enter random k (<q and gcd(k,q)=1): ";
    // 7
    cin>>k;

    long long r = modExp(g,k,p) % q;
    long long k_inv = modInv(k,q);
    long long s = (k_inv * (h + x*r)) % q;

    cout<<"\nSignature (r,s): ("<<r<<","<<s<<")"<<endl;

    // -------- VERIFICATION --------
    long long w = modInv(s,q);
    long long u1 = (h*w)%q;
    long long u2 = (r*w)%q;

    long long v = ((modExp(g,u1,p)*modExp(y,u2,p))%p)%q;

    cout<<"\nVerification value v: "<<v<<endl;

    if(v==r) cout<<"Signature VALID\n";
    else cout<<"Signature INVALID\n";
}