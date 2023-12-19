package ethernetsimple;

simple RelayUnit
{
    parameters:
    	@display("i=abstract/switch");
    gates: 
        //L'array è a dimensione variabile. Ogni connesione nuova è un elemento in più che andiamo a creare
        input lowerLayerIn[]; 
        output lowerLayerOut[];
        
        //Modulo con due array di gate
}
