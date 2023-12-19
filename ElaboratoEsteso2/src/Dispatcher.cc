#include "Dispatcher.h"
#include "EthFrame_m.h"
#include "AppPackets_m.h"

Define_Module(Dispatcher);

void Dispatcher::initialize()
{
    count = gateSize("layerAppIn");
}

void Dispatcher::handleMessage(cMessage *msg)
{
   if(msg->getArrivalGate() == gate("layerNicIn")) {
       cPacket *app_pkt;
       AppControlInfo *ci;
       for (int i = 0; i < count; i++) {
           app_pkt = check_and_cast<cPacket *>(msg->dup());
           AppControlInfo *ci = check_and_cast<AppControlInfo *>(msg->getControlInfo()->dup());
           app_pkt->setControlInfo(ci);
           send(app_pkt, "layerAppOut", i);
       }
       delete msg->removeControlInfo();
       delete msg;
   }

   else {
       send(msg, "layerNicOut");
   }

}

