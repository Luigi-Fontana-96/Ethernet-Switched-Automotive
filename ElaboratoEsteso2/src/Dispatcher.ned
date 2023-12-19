package ethernetsimple;

simple Dispatcher
{
    parameters:
        @display("i=abstract/cache");
    gates:
        //L'array è a dimensione variabile. Ogni connesione nuova è un elemento in più che andiamo a creare
        input layerAppIn[];
        output layerAppOut[];
        input layerNicIn;
        output layerNicOut;
}
