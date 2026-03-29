#include <bits/stdc++.h>
using namespace std;

long long modExp(long long b,long long e,long long m){
    long long r=1;
    while(e){
        if(e&1) r=r*b%m;
        b=b*b%m;
        e>>=1;
    }
    return r;
}

long long gcd(long long a,long long b){
    return b?gcd(b,a%b):a;
}

int main(){
    srand(time(0));

    long long p,g,m;
    cout<<"Enter prime p: ";
    // 23
    cin>>p;

    cout<<"Enter generator g: ";
    // 5
    cin>>g;

    cout<<"Enter message (m < p): ";
    // 10
    cin>>m;

    // Key Generation
    long long x=rand()%(p-2)+1;      // private key
    long long y=modExp(g,x,p);       // public key

    cout<<"\nPublic key (p,g,y): ("<<p<<","<<g<<","<<y<<")";
    cout<<"\nPrivate key x: "<<x;

    // Encryption 
    long long k;
    do k=rand()%(p-2)+1;
    while(gcd(k,p-1)!=1);

    long long c1=modExp(g,k,p);
    long long c2=m*modExp(y,k,p)%p;

    cout<<"\nCiphertext (c1,c2): ("<<c1<<","<<c2<<")";

    // Decryption 
    long long s=modExp(c1,x,p);
    long long m2=c2*modExp(s,p-2,p)%p;

    cout<<"\nDecrypted message: "<<m2<<"\n";
}