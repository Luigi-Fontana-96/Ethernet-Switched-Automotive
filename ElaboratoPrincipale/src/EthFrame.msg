packet EthFrame {
    name = "EthFrame";
    string dst;
    string src;
    int ethertype;
    byteLength = 26;
    string tpid;
    int pcp;
    bool dei;
    int vid;
}
