package ethernetsimple;

module EthNode
{
    parameters:
        @display("i=device/drive;bgb=403,431");
        int napp = default(1);
    //Andiamo ad inserire i gate	
    gates:
        input channelIn;
        output channelOut;
    submodules:
        app[napp]: BurstApp {
            @display("p=197,112");
        }
        nic: EthNIC {
            @display("p=197,357");
        }
        dispatcher: Dispatcher {
            @display("p=191,240");
        }
    connections:
        //In questo caso colleghiamo uscita con uscita 
        for i=0..(napp-1) {
        	app[i].lowerLayerOut --> dispatcher.layerAppIn++;
        	dispatcher.layerAppOut++ --> app[i].lowerLayerIn;
        }
        
        nic.channelOut --> channelOut; //Le frecce puntano nella direzione in cui transitano i messaggi
        nic.channelIn <-- channelIn;
        
        dispatcher.layerNicOut --> nic.upperLayerIn;
        nic.upperLayerOut --> dispatcher.layerNicIn;
}
