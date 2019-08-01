//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "App1.h"

Define_Module(App1);

void App1::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        //Initializing members and pointers of your application goes here
        EV << "Initializing " << "app1" << std::endl;
        sentMessage = false;
        lastDroveAt = simTime();
    }
    else if (stage == 1) {
        //Initializing members that require initialized other modules goes here
        prevTime = simTime();
    }
}

void App1::finish() {
    BaseWaveApplLayer::finish();
    //statistics recording goes here
    EV << "finished!!" << std::endl;
}

void App1::onBSM(BasicSafetyMessage* bsm) {
    //Your application has received a beacon message from another car or RSU
    //code for handling the message goes here
}

void App1::onWSM(WaveShortMessage* wsm) {
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples
    /*findHost()->getDisplayString().updateWith("r=16,green");
    EV << "RECEIVED WSM" << std::endl;
    std::string id = "car1";
    if ((id.compare(traciVehicle->getTypeId())) == 0) {
        traciVehicle->setSpeedMode(0000);
        traciVehicle->setSpeed(8.0);
    } else if (wsm->getChannelNumber() == 1) {
        int speed = std::stod(wsm->getWsmData());
        traciVehicle->setSpeedMode(0000);
        traciVehicle->setSpeed(speed);
    }*/
    findHost()->getDisplayString().updateWith("r=16,green");
    std::string id = "car1";
    if ((id.compare(traciVehicle->getTypeId())) == 0) {
        traciVehicle->setSpeedMode(0000);
        traciVehicle->setSpeed(3.0);
    }
}

void App1::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void App1::handleSelfMsg(cMessage* msg) {
    BaseWaveApplLayer::handleSelfMsg(msg);
    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission
   /* EV << "SELF MSG" << std::endl;
    std::string id = "car1";
    if (id.compare(traciVehicle->getTypeId()) == 0){
        if (simTime() == 40){
            DBG_APP << "car1 to 10" << std::endl;
            traciVehicle->setSpeed(10.0);
        } else if (simTime() == 80){
            EV << "car1 to 50" << std::endl;
            traciVehicle->setSpeed(50.0);
        }
    }*/
    if (WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg)) {
        delete(wsm);
    }
    else {
        BaseWaveApplLayer::handleSelfMsg(msg);
    }
}

void App1::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class
    /*if ((simTime() - prevTime >= 1)){ //send wsm every second
        WaveShortMessage* wsm = new WaveShortMessage();
        populateWSM(wsm);
        std::string s = std::to_string(mobility->getSpeed()); //message: speed
        wsm->setWsmData(s.c_str());

        std::string id = "car1";
        if (id.compare(traciVehicle->getTypeId()) == 0){
            wsm->setUserPriority(1);
            wsm->setChannelNumber(1);
        } else {
            wsm->setUserPriority(2);
            wsm->setChannelNumber(2);
        }

        sendDelayedDown(wsm, uniform(100,1000));
        lastDroveAt = simTime();
    }*/
    if (simTime() - lastDroveAt >= 1) {
           WaveShortMessage* wsm =new WaveShortMessage();
           populateWSM(wsm);
           sendDelayedDown(wsm, uniform(100,1000));
           lastDroveAt = simTime();
       }
}
