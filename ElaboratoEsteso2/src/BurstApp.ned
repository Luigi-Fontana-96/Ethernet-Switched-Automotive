package ethernetsimple;

simple BurstApp
{
    parameters: 
        @display("i=block/telnet");
        double period @unit(s) = default(0s);
        int payloadSize @unit(B) = default(0B);
        string destination = default("");
        string source = default("");
        int burstSize = default(1);
        double startTime @unit(s) = default(0s); //Se starttime = 0 solo ricevitore
        int priority = default(0);
        string provenienza = default("");
        double deadRelative @unit(s) = default(0s);
        bool miss = default(false);
        string sw1 = default("");
        string sw2 = default("");
        
        //Istruzioni per recuperare le statistiche
//        @signal[E2EDelay];
//        @statistic[E2EDelay](record = vector, histogram);
//        
//        @signal[Jitter];
//        @statistic[Jitter](record = vector, histogram);
        
    gates: 
        input lowerLayerIn;
        output lowerLayerOut;
        
}
