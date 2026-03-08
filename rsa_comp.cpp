#include <iostream>
#include <chrono>
using namespace std;

long long power(long long b,long long e,long long m){
    long long r=1;
    while(e){
        if(e%2) r=(r*b)%m;
        b=(b*b)%m;
        e/=2;
    }
    return r;
}

long long gcd(long long a,long long b){
    while(b){
        long long t=b;
        b=a%b;
        a=t;
    }
    return a;
}

long long modInverse(long long e,long long phi){
    for(long long d=2; d<phi; d++)
        if((e*d)%phi==1) return d;
    return -1;
}

void RSA(long long p,long long q,string name){

    long long n=p*q;
    long long phi=(p-1)*(q-1);
    long long e,d;

    for(e=2;e<phi;e++)
        if(gcd(e,phi)==1) break;

    d=modInverse(e,phi);

    long long message=123,cipher,plain;

    cout<<"\n"<<name<<endl;

    auto s=chrono::high_resolution_clock::now();
    for(int i=0;i<100000;i++)
        cipher=power(message,e,n);
    auto e1=chrono::high_resolution_clock::now();

    auto s2=chrono::high_resolution_clock::now();
    for(int i=0;i<100000;i++)
        plain=power(cipher,d,n);
    auto e2=chrono::high_resolution_clock::now();

    cout<<"Encryption time: "
        <<chrono::duration<double,milli>(e1-s).count()<<" ms\n";

    cout<<"Decryption time: "
        <<chrono::duration<double,milli>(e2-s2).count()<<" ms\n";
}

int main(){

    RSA(61,53,"Small Key RSA");
    RSA(7919,1009,"Large Key RSA");

    cout<<"\nLarge keys take more time than small keys.\n";
}