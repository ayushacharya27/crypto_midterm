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

// Modular inverse (simple)
long long modInv(long long e,long long phi){
    for(long long d=1; d<phi; d++)
        if((e*d)%phi==1) return d;
    return -1;
}

int main(){
    long long p,q;

    cout<<"Enter prime p: ";
    // 61
    cin>>p;

    cout<<"Enter prime q: ";
    // 53
    cin>>q;

    long long n=p*q;
    long long phi=(p-1)*(q-1);

    // Choose e
    long long e;
    for(e=2;e<phi;e++)
        if(gcd(e,phi)==1) break;

    long long d=modInv(e,phi);

    cout<<"\nPublic key (e,n): ("<<e<<","<<n<<")";
    cout<<"\nPrivate key (d,n): ("<<d<<","<<n<<")\n";

    long long m;
    cout<<"\nEnter message (number < n): ";
    // 123
    cin>>m;

    // -------- SIGN --------
    long long signature = modExp(m,d,n);
    cout<<"\nSignature: "<<signature<<endl;

    // -------- VERIFY --------
    long long verify = modExp(signature,e,n);
    cout<<"Verified message: "<<verify<<endl;

    if(verify==m) cout<<"Signature VALID\n";
    else cout<<"Signature INVALID\n";
}