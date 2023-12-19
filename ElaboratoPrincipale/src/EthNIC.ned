package ethernetsimple;

simple EthNIC
{
    parameters:
        @display("i=block/mac");
        bool promMode = default(false);
        double datarate @unit(bps) = default(100Mbps);
        //parametro che indica se siamo nello switch oppure no
        bool inSwitch = default(false);
        int appN = default(1);
    
    gates: 
        input upperLayerIn;
        output upperLayerOut;
        input channelIn;
        output channelOut;
}
