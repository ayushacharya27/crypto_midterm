#include <bits/stdc++.h>
using namespace std;

int mod = 13;

// modular inverse
int inv(int x){
    for(int i=1;i<mod;i++)
        if((x*i)%mod==1) return i;
    return -1;
}

// point structure
struct Point{
    int x,y;
    bool inf;
};

// point addition
Point add(Point P, Point Q, int a){
    if(P.inf) return Q;
    if(Q.inf) return P;

    if(P.x==Q.x && (P.y+Q.y)%mod==0)
        return {0,0,true};

    int m;
    if(P.x==Q.x && P.y==Q.y){
        m = (3*P.x*P.x + a) * inv(2*P.y % mod) % mod;
    } else {
        m = (Q.y - P.y) * inv((Q.x - P.x + mod)%mod) % mod;
    }

    m = (m + mod) % mod;

    int xr = (m*m - P.x - Q.x) % mod;
    int yr = (m*(P.x - xr) - P.y) % mod;

    return {(xr+mod)%mod, (yr+mod)%mod, false};
}

// scalar multiplication
Point mul(Point P, int k, int a){
    Point R = {0,0,true};
    while(k){
        if(k&1) R = add(R,P,a);
        P = add(P,P,a);
        k >>= 1;
    }
    return R;
}

int main(){
    int a,b;
    // y² = x³ + ax + b (mod 13)
    // 1 1
    cout<<"Enter curve parameters a and b: ";
    cin>>a>>b;

    Point G;
    cout<<"Enter base point (x y): ";
    // 2 7
    cin>>G.x>>G.y;
    G.inf=false;

    int d;
    cout<<"Enter private key: ";
    // 3
    cin>>d;

    // Public key
    Point Q = mul(G,d,a);

    cout<<"\nPublic key Q: ("<<Q.x<<","<<Q.y<<")";

    // Encryption
    Point M;
    cout<<"\nEnter message point (x y): ";
    // 5 1
    cin>>M.x>>M.y;
    M.inf=false;

    int k;
    cout<<"Enter random k: ";
    // 2
    cin>>k;

    Point C1 = mul(G,k,a);
    Point C2 = add(M, mul(Q,k,a), a);

    cout<<"\nCipher: ("<<C1.x<<","<<C1.y<<") , ("<<C2.x<<","<<C2.y<<")";

    // Decryption
    Point dC1 = mul(C1,d,a);
    dC1.y = (mod - dC1.y) % mod; // inverse point

    Point D = add(C2, dC1, a);

    cout<<"\nDecrypted: ("<<D.x<<","<<D.y<<")\n";
}