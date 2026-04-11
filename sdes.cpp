#include <bits/stdc++.h>
using namespace std;

int P(int v,int in,int out,int p[]){
    int r=0;
    for(int i=0;i<out;i++)
        r|=((v>>(in-p[i]))&1)<<(out-1-i);
    return r;
}

int P10[]={3,5,2,7,4,10,1,9,8,6}, P8[]={6,3,7,4,8,5,10,9};
int IP[]={2,6,3,1,4,8,5,7}, IPI[]={4,1,3,5,7,2,8,6};
int EP[]={4,1,2,3,2,3,4,1}, P4[]={2,4,3,1};

int S0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
int S1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};

int shift(int x,int s){
    return ((x<<s)|(x>>(5-s)))&31;
}

int fk(int r,int k){
    int t=P(r,4,8,EP)^k;
    int L=t>>4,R=t&15;

    int row=((L&8)>>2)|(L&1), col=(L>>1)&3;
    int a=S0[row][col];

    row=((R&8)>>2)|(R&1);
    col=(R>>1)&3;
    int b=S1[row][col];

    return P((a<<2)|b,4,4,P4);
}

int sdes(int m,int k1,int k2){
    m=P(m,8,8,IP);

    int L=m>>4,R=m&15;

    L^=fk(R,k1);
    swap(L,R);
    L^=fk(R,k2);

    return P((L<<4)|R,8,8,IPI);
}

int main(){
    int choice;
    string keyStr;

    vector<int> plaintextBytes;
    /*string pt;
    cout<<"Enter plaintext string: ";
    // ayushacharya
    getline(cin,pt);

    for(char c:pt)
        plaintextBytes.push_back((unsigned char)c);
    */

    /*
    string bin;
    cout<<"Enter binary plaintext: "; // Multiple of 8 Bits
    // 10101011
    getline(cin,bin);

    plaintextBytes=binaryToBytes(bin);
    */
    

    cout<<"Enter 10-bit key (binary): ";
    // 1010101101
    getline(cin,keyStr);

    // Parse key
    int k=0,c=0;
    for(char x:keyStr){
        if(x=='0'||x=='1'){
            k=(k<<1)|(x-'0');
            if(++c==10) break;
        }
    }
    k<<=(10-c);

    // Generate subkeys
    int k1=P((shift(k>>5,1)<<5)|shift(k&31,1),10,8,P8);
    int k2=P((shift(k>>5,3)<<5)|shift(k&31,3),10,8,P8);

    // Encrypt
    vector<int> cipher=plaintextBytes;
    for(int &x:cipher)
        x=sdes(x,k1,k2);

    cout<<"Encrypted (hex): ";
    for(int x:cipher)
        printf("%02X ",x);

    // Decrypt
    vector<int> decrypted=cipher;
    for(int &x:decrypted)
        x=sdes(x,k2,k1);

    cout<<"\nDecrypted: ";
    for(int x:decrypted)
        cout<<(char)x;

    cout<<endl;
    return 0;
}