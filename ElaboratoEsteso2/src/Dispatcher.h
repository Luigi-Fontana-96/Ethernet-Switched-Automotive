#ifndef __ELABORATOETHPROVAMINI2_DISPATCHER_H_
#define __ELABORATOETHPROVAMINI2_DISPATCHER_H_

#include <omnetpp.h>

using namespace omnetpp;

class Dispatcher : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    int count;
};

#endif
