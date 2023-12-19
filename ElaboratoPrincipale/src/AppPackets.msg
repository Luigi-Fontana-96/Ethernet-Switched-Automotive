packet AppPackets {
  name = "AppPacket";
  simtime_t genTime;
  bool lastBurstPacket = false;
}

message AppControlInfo{
	string dst;
	string src;
	int priority;
}
