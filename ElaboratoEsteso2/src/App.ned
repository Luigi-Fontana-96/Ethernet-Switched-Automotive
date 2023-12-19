package ethernetsimple;

import ethernetsimple.BurstApp;
import ethernetsimple.EthNIC;
import ethernetsimple.EthNode;
import ethernetsimple.EthSwitch;


network App
{
    @display("bgb=1475.0887,657.0113");
    submodules:
        CM1: EthNode {
            @display("p=104.2875,288.52875;is=l");
        }
        S1: EthNode {
            @display("p=376.59375,35.92125;is=l");
        }
        SW1: EthSwitch {
            @display("p=376.59375,288.52875;is=l");
        }

        S2: EthNode {
            @display("p=376.59375,531.8663");
        }
        US2: EthNode {
            @display("p=104.2875,188.87625");
        }
        LD2: EthNode {
            @display("p=104.2875,104.2875");
        }
        LD1: EthNode {
            @display("p=104.2875,385.86377");
        }
        US1: EthNode {
            @display("p=100.81125,484.3575");
        }
        CU: EthNode {
            @display("p=287.37,115.875");
        }
        HU: EthNode {
            @display("p=504.05627,346.46625");
        }
        SW2: EthSwitch {
            @display("p=789.10876,288.52875;is=l");
        }
        S4: EthNode {
            @display("p=789.10876,33.603752");
        }
        S3: EthNode {
            @display("p=789.10876,531.8663");
        }
        RS1: EthNode {
            @display("p=662.805,207.41626");
        }
        RS2: EthNode {
            @display("p=670.91626,376.59375");
        }
        RC: EthNode {
            @display("p=1016.22375,283.89377");
        }
        US4: EthNode {
            @display("p=1016.22375,355.73627");
        }
        US3: EthNode {
            @display("p=1016.22375,207.41626");
        }
        ME: EthNode {
            @display("p=927,123.98625");
        }
        TLM: EthNode {
            @display("p=927,429.89627");
        }
    //Definiamo il numero di porte che ha lo switch nel file della rete. 
    //Possiamo parametrizzarlo facendo un ciclo for.
    connections:
        CM1.channelOut --> SW1.channelIn++;
        SW1.channelOut++ --> CM1.channelIn;
        SW1.channelOut++ --> S1.channelIn;
        S1.channelOut --> SW1.channelIn++;
        S2.channelOut --> SW1.channelIn++;
        SW1.channelOut++ --> S2.channelIn;
        LD2.channelOut --> SW1.channelIn++;
        SW1.channelOut++ --> LD2.channelIn;
        US2.channelOut --> SW1.channelIn++;
        SW1.channelOut++ --> US2.channelIn;
        LD1.channelOut --> SW1.channelIn++;
        SW1.channelOut++ --> LD1.channelIn;
        US1.channelOut --> SW1.channelIn++;
        SW1.channelOut++ --> US1.channelIn;
        SW1.channelOut++ --> CU.channelIn;
        CU.channelOut --> SW1.channelIn++;
        SW1.channelOut++ --> HU.channelIn;
        HU.channelOut --> SW1.channelIn++;
        SW1.channelOut++ --> SW2.channelIn++;
        SW2.channelOut++ --> SW1.channelIn++;
        SW2.channelOut++ --> S4.channelIn;
        S4.channelOut --> SW2.channelIn++;
        SW2.channelOut++ --> S3.channelIn;
        S3.channelOut --> SW2.channelIn++;
        RS1.channelOut --> SW2.channelIn++;
        SW2.channelOut++ --> RS1.channelIn;
        RS2.channelOut --> SW2.channelIn++;
        SW2.channelOut++ --> RS2.channelIn;
        ME.channelOut --> SW2.channelIn++;
        SW2.channelOut++ --> ME.channelIn;
        TLM.channelOut --> SW2.channelIn++;
        SW2.channelOut++ --> TLM.channelIn;
        RC.channelOut --> SW2.channelIn++;
        SW2.channelOut++ --> RC.channelIn;
        US3.channelOut --> SW2.channelIn++;
        SW2.channelOut++ --> US3.channelIn;
        US4.channelOut --> SW2.channelIn++;
        SW2.channelOut++ --> US4.channelIn;
}
