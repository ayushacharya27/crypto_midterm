vector<uint8_t> binaryToBytes(string bin){
    vector<uint8_t> bytes;
    while(bin.length()%8!=0) bin="0"+bin;

    for(int i=0;i<bin.length();i+=8){
        string part=bin.substr(i,8);
        bytes.push_back(bitset<8>(part).to_ulong());
    }
    return bytes;
}