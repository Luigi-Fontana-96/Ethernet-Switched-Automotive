#ifndef __ETHERNETSIMPLE_ETHNIC_H_
#define __ETHERNETSIMPLE_ETHNIC_H_

#include <omnetpp.h>

using namespace omnetpp;

class EthNIC : public cSimpleModule
{
  protected:
    typedef enum {
        TX_STATE_IDLE,
        TX_STATE_TRASMITTING,
        TX_STATE_WAIT_IFG
    }ethstate_t;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void trasmit();

    static int compareFunction(cObject *a, cObject *b);

    ethstate_t txstate;
    bool promMode;
    double datarate;
    cPacketQueue txqueue;

    bool inSwitch;
    int appN;
    int tx;
};

#endif
