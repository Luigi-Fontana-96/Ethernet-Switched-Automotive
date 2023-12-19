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
    simtime_t period;
	int payloadSize;
	int burstSize;
	simtime_t deadRelative;
	int txFrame;
	string sw1;
	string sw2;
}
