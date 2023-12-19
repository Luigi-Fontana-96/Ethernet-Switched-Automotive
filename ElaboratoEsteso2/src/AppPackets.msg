packet AppPackets {
  name = "AppPacket";
  simtime_t genTime;
  bool lastBurstPacket = false;
}

message AppControlInfo{
	string dst;
	string src;
	int priority;
	simtime_t period;
	int payloadSize;
	int burstSize;
	simtime_t deadRelative;
	int idFrame;
	string sw1;
	string sw2;
}
