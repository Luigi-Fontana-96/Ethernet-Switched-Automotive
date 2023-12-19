#include "EthNIC.h"
#include "EthFrame_m.h"
#include "AppPackets_m.h"

Define_Module(EthNIC);

void EthNIC::initialize()
{
    datarate = par("datarate");
    promMode = par("promMode");
    inSwitch = par("inSwitch");
    txstate = TX_STATE_IDLE;
    txqueue = cPacketQueue(nullptr, compareFunction);
    tx = par("tx");
}

void EthNIC::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()) {
        if(strcmp(msg->getName(),"TxEndTimer") == 0) {
            assert(txstate = TX_STATE_TRASMITTING);
            delete msg;
            txstate = TX_STATE_WAIT_IFG; //InterframeGap
            double t = 96.0/datarate;
            cMessage *ifgtim = new cMessage("IFGEndTimer");
            scheduleAt(simTime() + t, ifgtim);
            return;
        } else if(strcmp(msg->getName(), "IFGEndTimer") == 0) {
            assert(txstate = TX_STATE_WAIT_IFG);
            delete msg;
            txstate = TX_STATE_IDLE;
            trasmit();
            return;
        } else if (strcmp(msg->getName(), "RxEndTimer") == 0) {
            cPacket *pkt = dynamic_cast<cPacket *>(msg->removeControlInfo());
            delete msg;
            send(pkt, "upperLayerOut");
            return;
        }
    }

    if(msg->getArrivalGate() == gate("upperLayerIn")) {
        //quando arriva una frame da sopra
        if (inSwitch) {
            //aggiungiamo la frame in coda
            cPacket *pkt = check_and_cast<cPacket *>(msg);
            txqueue.insert(pkt);
            trasmit();
            return;
        }
        AppControlInfo *ci = check_and_cast<AppControlInfo *>(msg->removeControlInfo());
        EthFrame *frame = new EthFrame();
        frame->setSrc(ci->getSrc());
        EV << "Source: " << ci->getSrc() << endl;
        frame->setDst(ci->getDst());
        EV << "Destination: " << ci->getDst() << endl;
        frame->setPcp(ci->getPriority());
        EV << "Priorità: " << ci->getPriority() << endl;
        frame->setBurstSize(ci->getBurstSize());
        frame->setPayloadSize(ci->getPayloadSize());
        frame->setPeriod(ci->getPeriod());
        frame->setDeadRelative(ci->getDeadRelative());
        frame->setSw1(ci->getSw1());
        frame->setSw2(ci->getSw2());
        AppPackets *pkt = check_and_cast<AppPackets *>(msg);
        pkt->setName(ci->getSrc());
        delete ci;
        cPacket *app_pkt = check_and_cast<cPacket *>(msg);
        int padding = 0;
        if (app_pkt->getByteLength() < 46) {
            padding = 46 - app_pkt->getByteLength();
        } else if (app_pkt->getByteLength() > 1500) {
            delete app_pkt;
            delete frame;
            EV << "AppPacket oversize: dropping..."<< endl;
            return;
        }
        frame->setTxFrame(tx++);
        frame->addByteLength(padding);
        frame->encapsulate(app_pkt);
        txqueue.insert(frame);
        trasmit();
        return;
    }

    EthFrame *frame = check_and_cast<EthFrame *>(msg);
    double t = frame->getBitLength()/datarate;
    cMessage *rxtim = new cMessage("RxEndTimer");
    if (inSwitch) {
                rxtim -> setControlInfo(frame);
                scheduleAt(simTime() + t, rxtim);
                return;
            }
    cPacket *app_pkt = frame->decapsulate();
    //Creiamo delle control info
    AppControlInfo *ci = new AppControlInfo();
    //settiamo sorgente e destinazione
    ci -> setSrc(frame->getSrc());
    ci -> setDst(frame->getDst());
    ci -> setPriority(frame->getPcp());
    ci -> setBurstSize(frame->getBurstSize());
    ci -> setPayloadSize(frame->getPayloadSize());
    ci -> setPeriod(frame->getPeriod());
    ci -> setDeadRelative(frame->getDeadRelative());
    ci -> setTxFrame(frame->getTxFrame());
    ci -> setSw1(frame->getSw1());
    ci -> setSw2(frame->getSw2());
    app_pkt->setControlInfo(ci);
    delete frame;
    rxtim -> setControlInfo(app_pkt);
    scheduleAt(simTime()+t, rxtim);
}

void EthNIC::trasmit() {
    if(txstate == TX_STATE_IDLE) {
        if(!txqueue.empty()) {
            cPacket *frame = txqueue.pop();
            send(frame, "channelOut");
            txstate = TX_STATE_TRASMITTING;
            double t = frame -> getBitLength()/datarate;
            cMessage *txtimer = new cMessage("TxEndTimer");
            scheduleAt(t + simTime(), txtimer);
        }
    }
}

int EthNIC::compareFunction(cObject *a, cObject *b) {
    int A = check_and_cast<EthFrame *>(a)->getPcp();
    int B = check_and_cast<EthFrame *>(b)->getPcp();
    if(A < B) {
        return 1;
    }
    else if (A == B) {
        return 0;
    }
    else {
        return -1;
    }

}
