#ifndef __ETHERNETSIMPLE_RELAYUNIT_H_
#define __ETHERNETSIMPLE_RELAYUNIT_H_

#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

class RelayUnit : public cSimpleModule
{
  protected:
    typedef struct {
        //abbiamo definito il nostro dato strutturale
        char mac_addr[30];
        //Indice dell'array di gate
        int eth_port_idx;
    }TableEntry;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    //scorre tutto il vettore e va a vedere se l'indirizzo mac si trova nella tabella e
    //se c'è restituisce l'indirizzo.
    virtual int getPortFromAddr(const char *mac);
    virtual int checkTable(const char *mac);


    //Creiamo un vettore dinamico. Usiamo la classe vector.
    //std è il namespace e vector è la classe. Dentro mettiamo il tipo di dato che vogliamo.
    std::vector<TableEntry *> fw_table; //vettore che contiene table entry

    //contiene il numero di porte.
    int port_count;
};

#endif
