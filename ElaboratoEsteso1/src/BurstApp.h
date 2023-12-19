#ifndef __ETHERNETSIMPLE_BURSTAPP_H_
#define __ETHERNETSIMPLE_BURSTAPP_H_
#include <iostream>
#include <fstream>

#include <omnetpp.h>

using namespace omnetpp;

class BurstApp : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void startTransmission();
    virtual void configNetwork();

    simtime_t period;
    simtime_t startTime;
    int payloadSize;
    const char *source;
    const char *destination;
    int burstSize;
    int priority;
    const char *provenienza;
    simtime_t deadRelative;

    //Calcolo del Jitter
    simsignal_t sigJitter;
    simtime_t maxe2edelay;
    simtime_t mine2edelay;


    simtime_t e2etot;
    int rxFrame;
    int numDeadMiss;

    const char *sw1;
    const char *sw2;

    int numSim;
};

#endif
