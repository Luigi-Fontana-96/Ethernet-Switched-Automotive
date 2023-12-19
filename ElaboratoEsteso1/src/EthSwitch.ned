package ethernetsimple;

module EthSwitch
{
    parameters:
        @display("i=device/hub;bgb=799.429");
       //Creiamo un array di gate
    gates:
        input channelIn[];
        output channelOut[];


    submodules:
        relayUnit: RelayUnit {
            @display("p=172.645,63.23625");
        }
        eth[sizeof(channelIn)]: EthNIC {
            @display("p=172.645,187.70125");
            inSwitch = true;
        }
        
        connections: 
        for i=0..sizeof(channelIn) - 1 {
        	//Dobbiamo collegare ogni eth upperlayer out e in con i rispettivi relay unit
            //Colleghiamo il modulo eth di indice i-esimo, prendiamo il gate in ingresso e lo vogliamo collegate
            //con il lower layer out della relay unit ma questo è un array di dimensioni indefinite.
            //Per aggiungere un gate a quell'array dobbiamo utilizzare in ++. 
        	eth[i].upperLayerIn <-- relayUnit.lowerLayerOut++; //Aggiunge un nuovo gate e restituisce il gate con indice appena aggiunto
        	//Stessa cosa per l'upperlayerout
        	eth[i].upperLayerOut --> relayUnit.lowerLayerIn++;
        	//dobbiamo connettere i nic con i rispettivi channel in e channel out
        	channelIn[i] --> eth[i].channelIn;
        	channelOut[i] <-- eth[i].channelOut;        	
        }   
}

