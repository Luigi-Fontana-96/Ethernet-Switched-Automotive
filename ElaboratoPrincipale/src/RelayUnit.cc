#include "RelayUnit.h"
#include "EthFrame_m.h"

Define_Module(RelayUnit);

void RelayUnit::initialize()
{
    //Salviamo il numero di porte su una variabile
    port_count = gateSize("lowerLayerIn");
}

void RelayUnit::handleMessage(cMessage *msg)
{
    int idx; //Indice del gate da cui è arrivata la frame
    int port_idx;

    //Restituisce l'indice se si tratta di un array di gate. Se non si tratta restituisce zero perchè ha un solo elemento.
    idx = msg->getArrivalGate()->getIndex(); //Restituisce l'indice del vettore se riconosce il gate
    EV << "Gate di arrivo della frame: [" << idx << "] "  << endl;
    EthFrame *frame = check_and_cast<EthFrame *>(msg);

    //Controlliamo l'indirizzo di destinazione per vedere se è in tabella
    port_idx = getPortFromAddr(frame->getDst());
    EV << "Sorgente della frame: [" << frame->getSrc() << "] "  << endl;

    if(checkTable(frame->getSrc()) == -1){
       TableEntry *entry = new TableEntry; //Alloco un elemento di struct di tipo tableentry
       strncpy(entry->mac_addr,frame->getSrc(), 30);
       entry->eth_port_idx = idx; //Porta da cui mi è arrivata la frame
       EV << "Nuova entry in table -> " << entry->mac_addr << ": " << entry->eth_port_idx << endl;
       fw_table.push_back(entry);
       }

    //se l'elemento è in tabella
    if(port_idx != -1) {
        send(frame->dup(), "lowerLayerOut", port_idx);
    } else {
        //La entry non è in tabella. Deve inoltrare tutte le volte tranne quella non in tabella
        for(int i=0; i<port_count; i++) {
            //la send la inviamo solo se diversa da idx
            if(i != idx) {
            //Quando lo invia a più di un gate non posso inviare la stessa frame ma devo inviare un duplicato della frame.
            //Crea un duplicato della frame. L'owner(proprietario) che è il modulo che la sta utilizzando
            send(frame->dup(), "lowerLayerOut", i);
            }
        }

    }
    delete frame;
}

int RelayUnit::getPortFromAddr(const char *mac) {
    //scorrere il vettore e cercare se l'indirizzo corrisponde al mac.
    for(int i = 0; i<int(fw_table.size()); i++) {
        //EV << "PORT: [" << fw_table[i]->eth_port_idx << "]: "  << fw_table[i]->mac_addr<< endl;
        if(strncmp(fw_table[i]->mac_addr, mac, strlen(fw_table[i]->mac_addr)) == 0) {
            EV << "Corrispondenza trovata Dst:"<< fw_table[i]->mac_addr <<" in Gate:"<< fw_table[i]->eth_port_idx <<" forwarding.."<< endl;
            return fw_table[i]->eth_port_idx;
        }

    }
    return -1;
}

int RelayUnit::checkTable(const char *sourceMac) {
    for(int i = 0; i<int(fw_table.size()); i++) {
        if(strncmp(fw_table[i]->mac_addr, sourceMac, strlen(fw_table[i]->mac_addr)) == 0) {
            //EV << "Entry presente in tabella" << endl;
            return 0;
        }
    }
    return -1;
}
