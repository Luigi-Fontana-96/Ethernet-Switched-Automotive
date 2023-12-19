#include "BurstApp.h"
#include "AppPackets_m.h"
#include <iostream>
#include <fstream>



Define_Module(BurstApp);

void BurstApp::initialize()
{
   period = par("period");
   deadRelative = par("deadRelative");
   startTime = par("startTime");
   payloadSize = par("payloadSize");
   burstSize = par("burstSize");
   source = par("source").stringValue();
   destination = par("destination").stringValue();
   priority = par("priority");
   provenienza = par("provenienza").stringValue();
   miss = par("miss");
   sw1 = par("sw1").stringValue();
   sw2 = par("sw2").stringValue();
   numSim = getEnvir()->getConfigEx()->getActiveRunNumber();

   if (startTime == 0) {
     configNetwork();
   }
   else if(startTime > 0) {
       cMessage *txtimer = new cMessage("TxTimer");
       scheduleAt(startTime, txtimer);
   }

   mine2edelay = 0;
   maxe2edelay = 0;
   sigJitter = registerSignal("Jitter");
}

void BurstApp::handleMessage(cMessage *msg)
{
   if(msg->isSelfMessage()) {
       if(strcmp(msg->getName(), "TxTimer") == 0) {
           startTransmission();
           scheduleAt(simTime() + period, msg);
           return;
       }
   }

   //Quando arriva una frame dobbiamo leggere le control info
  AppControlInfo *ci = dynamic_cast<AppControlInfo *>(msg->removeControlInfo());
  EV << "Destination: "<<ci->getDst() << endl;
       EV << "Source: "<<ci->getSrc() << endl;
       EV << source << endl;
       EV << provenienza << endl;
   if(strcmp(ci->getDst(), source) != 0) {
       EV << "la frame non è destinata a questa sorgente" << endl;
       delete msg;
       delete ci;
       return;
   }

   if(strcmp(ci->getSrc(), provenienza) != 0) {
      EV << "Provenienza Sbagliata" << endl;
              delete msg;
              delete ci;
              return;
   }

   EV << "Un messaggio è arrivato da: " << msg->getName() << endl;

   AppPackets *pkt = check_and_cast<AppPackets *>(msg);
   simsignal_t sig;
   simtime_t e2ed;

   e2ed = simTime() - pkt->getGenTime();
   sig = registerSignal("E2EDelay");
   emit(sig, e2ed);

   if(e2ed > ci->getDeadRelative()) {
           miss = true;
      }

   if(e2ed > maxe2edelay) {
       maxe2edelay = e2ed;
   }

   if(mine2edelay == 0 || mine2edelay > e2ed) {
          mine2edelay = e2ed;
   }


   emit(sigJitter, maxe2edelay-mine2edelay);

       std::fstream fout;
          // opens an existing csv file or creates a new file.
          fout.open("report2.csv", std::ios::out | std::ios::app);
          /*
          fout << "FrameID" << ","
          << "Nome Flusso" << ","
                     << "Src" << ","
                     << "Dst" << ","
                     << "Periodo" << ","
                     << "DeadlineRelativa" << ","
                     << "Payload" << ","
                     << "Burst" << ","
                     << "sw1" << ","
                     << "sw2" << ","
                     << "priorità" << ","
                     << "DeadlineMiss" << ","
                     << "e2eDelay" << \n";
                     */

       // Insert the data to file
       fout << rand() << ","
            << provenienza << source << ", "
            << ci->getSrc() << ", "
            << ci->getDst() << ", "
            << ci->getPeriod() << ","
            << ci->getDeadRelative() << ","
            << ci->getPayloadSize()<< ","
            << ci->getBurstSize() << ","
            << ci->getSw1() << ","
            << ci->getSw2() << ","
            << ci->getPriority() << ","
            << miss << ","
            << e2ed << ","
            << numSim +3 << "\n";

                fout.close();

   miss = false;

   delete msg;
   delete ci;

}

void BurstApp::startTransmission() {
    AppPackets *pkt;
    AppControlInfo *ci;

    for (int i=0; i < burstSize; i++) {
        pkt = new AppPackets();
        pkt->setByteLength(payloadSize);
        pkt->setGenTime(simTime());
        if(i == (burstSize - 1)) {
            pkt -> setLastBurstPacket(true);
        }

        ci = new AppControlInfo();
        ci->setSrc(source);
        ci->setDst(destination);
        ci->setPriority(priority);
        ci->setPeriod(period);
        ci->setBurstSize(burstSize);
        ci->setPayloadSize(payloadSize);
        ci->setDeadRelative(deadRelative);
        ci->setSw1(sw1);
        ci->setSw2(sw2);

        pkt->setControlInfo(ci);

        send(pkt, "lowerLayerOut");
    }
}

void BurstApp::configNetwork() {
        AppPackets *pkt;
        AppControlInfo *ci;
        pkt = new AppPackets();
        pkt->setByteLength(payloadSize);

        pkt->setGenTime(simTime());

        if(burstSize - 1) {
            pkt -> setLastBurstPacket(true);
        }

        ci = new AppControlInfo();
        ci->setSrc(source);
        ci->setDst(destination);

        pkt->setControlInfo(ci);
        send(pkt, "lowerLayerOut");
}
