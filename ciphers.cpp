////--------CIPHER START--------------CIPHER START------------CIPHER START------------------CIPHER START---------////
//--------------Caesar Cipher START---------------------------------------Caesar Cipher START-------------------------//
#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int k;

    cout<<"Enter text: ";
    getline(cin,s);

    cout<<"Enter key: ";
    cin>>k;

    string enc=s, dec;

    // Encrypt
    for(int i=0;i<s.size();i++){
        if(isalpha(s[i])){
            char base = islower(s[i]) ? 'a' : 'A';
            enc[i] = (s[i]-base + k)%26 + base;
        }
    }

    cout<<"Encrypted: "<<enc<<endl;

    // Decrypt
    dec=enc;
    for(int i=0;i<enc.size();i++){
        if(isalpha(enc[i])){
            char base = islower(enc[i]) ? 'a' : 'A';
            dec[i] = (enc[i]-base - k + 26)%26 + base;
        }
    }

    cout<<"Decrypted: "<<dec<<endl;
}
//--------------Caesar Cipher END---------------------------------------Caesar Cipher END-------------------------//

//--------------Monoalphabetic Cipher​ START-------------------Monoalphabetic Cipher​ START-------------------------//
#include <bits/stdc++.h>
using namespace std;

int main(){
    string text, key;

    cout<<"Enter plaintext: ";
    // ayushacharya
    getline(cin, text);

    cout<<"Enter 26-letter key: ";
    getline(cin, key);   // example: qwertyuiopasdfghjklzxcvbnm

    string enc=text, dec=text;

    // -------- ENCRYPT --------
    for(int i=0;i<text.size();i++){
        if(isalpha(text[i])){
            char base = islower(text[i]) ? 'a' : 'A';
            enc[i] = tolower(key[text[i]-base]);
            if(isupper(text[i])) enc[i] = toupper(enc[i]);
        }
    }

    cout<<"Encrypted: "<<enc<<endl;

    // -------- DECRYPT --------
    for(int i=0;i<enc.size();i++){
        if(isalpha(enc[i])){
            char c = tolower(enc[i]);
            int pos = key.find(c);
            dec[i] = pos + (isupper(enc[i]) ? 'A' : 'a');
        }
    }

    cout<<"Decrypted: "<<dec<<endl;
}
//--------------Monoalphabetic Cipher​ START-------------------Monoalphabetic Cipher​ START-------------------------//

//--------------Playfair Cipher START---------------------------------Playfair Cipher START-----------------------//
#include <bits/stdc++.h>
using namespace std;

char mat[5][5];

// Generate key matrix
void generateMatrix(string key){
    set<char> used;
    string k="";

    for(char c:key){
        c=tolower(c);
        if(c=='j') c='i';
        if(isalpha(c) && !used.count(c)){
            used.insert(c);
            k+=c;
        }
    }

    for(char c='a';c<='z';c++){
        if(c=='j') continue;
        if(!used.count(c)){
            used.insert(c);
            k+=c;
        }
    }

    for(int i=0;i<25;i++)
        mat[i/5][i%5]=k[i];
}

// Find position
pair<int,int> findPos(char c){
    if(c=='j') c='i';
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(mat[i][j]==c) return {i,j};
    return {-1,-1};
}

// Prepare text
string prepare(string s){
    string t="";
    for(char c:s){
        if(isalpha(c)){
            c=tolower(c);
            if(c=='j') c='i';
            t+=c;
        }
    }

    string res="";
    for(int i=0;i<t.size();i++){
        res+=t[i];
        if(i+1<t.size() && t[i]==t[i+1]) res+='x';
    }
    if(res.size()%2) res+='x';
    return res;
}

// Encrypt/Decrypt
string process(string s,bool enc){
    string res="";
    for(int i=0;i<s.size();i+=2){
        auto a=findPos(s[i]);
        auto b=findPos(s[i+1]);

        if(a.first==b.first){ // same row
            res+=mat[a.first][(a.second+(enc?1:4))%5];
            res+=mat[b.first][(b.second+(enc?1:4))%5];
        }
        else if(a.second==b.second){ // same col
            res+=mat[(a.first+(enc?1:4))%5][a.second];
            res+=mat[(b.first+(enc?1:4))%5][b.second];
        }
        else{ // rectangle
            res+=mat[a.first][b.second];
            res+=mat[b.first][a.second];
        }
    }
    return res;
}

int main(){
    string key, text;

    cout<<"Enter key: ";
    // ayushcharya
    getline(cin,key);

    cout<<"Enter plaintext: ";
    // tamanna
    getline(cin,text);

    generateMatrix(key);

    string p = prepare(text);
    string enc = process(p,true);
    string dec = process(enc,false);

    cout<<"Encrypted: "<<enc<<endl;
    cout<<"Decrypted: "<<dec<<endl;
}
//--------------Playfair Cipher END---------------------------------------Playfair Cipher END----------------------//

//--------------Hill Cipher START---------------------------------------Hill Cipher START-------------------------//
#include <bits/stdc++.h>
using namespace std;

int mod26(int x){
    x %= 26;
    if(x < 0) x += 26;
    return x;
}

int modInverse(int a){
    a = mod26(a);
    for(int i=1;i<26;i++)
        if((a*i)%26==1) return i;
    return -1;
}

int main(){
    string text;
    int key[2][2];

    cout<<"Enter plaintext: ";
    // help
    getline(cin,text);

    cout<<"Enter 2x2 key matrix:\n";
    // 3 3 2 5
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            cin>>key[i][j];

    // Prepare plaintext
    string p="";
    for(char c:text){
        if(isalpha(c))
            p += tolower(c);
    }
    if(p.size()%2) p+='x';

    // Encrypt
    string enc="";
    for(int i=0;i<p.size();i+=2){
        int a=p[i]-'a';
        int b=p[i+1]-'a';

        int c1 = mod26(key[0][0]*a + key[0][1]*b);
        int c2 = mod26(key[1][0]*a + key[1][1]*b);

        enc += char(c1+'a');
        enc += char(c2+'a');
    }

    cout<<"Encrypted: "<<enc<<endl;

    // Inverse key matrix
    int det = mod26(key[0][0]*key[1][1] - key[0][1]*key[1][0]);
    int invDet = modInverse(det);

    if(invDet==-1){
        cout<<"Key matrix not invertible!"<<endl;
        return 0;
    }

    int inv[2][2];
    inv[0][0] = mod26( key[1][1]*invDet);
    inv[0][1] = mod26(-key[0][1]*invDet);
    inv[1][0] = mod26(-key[1][0]*invDet);
    inv[1][1] = mod26( key[0][0]*invDet);

    // Decrypt
    string dec="";
    for(int i=0;i<enc.size();i+=2){
        int a=enc[i]-'a';
        int b=enc[i+1]-'a';

        int p1 = mod26(inv[0][0]*a + inv[0][1]*b);
        int p2 = mod26(inv[1][0]*a + inv[1][1]*b);

        dec += char(p1+'a');
        dec += char(p2+'a');
    }

    cout<<"Decrypted: "<<dec<<endl;
}
//--------------Hill Cipher END---------------------------------------Hill Cipher END-------------------------//
////--------CIPHER END------------------CIPHER END------------------CIPHER END------------------CIPHER END----------////