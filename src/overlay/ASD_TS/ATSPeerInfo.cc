//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "ATSPeerInfo.h"
#include <cmath>

unsigned int ATSPeerInfo::getFreeResource() const {
    return freeResource;
}

TransportAddress ATSPeerInfo::getAddress() const {
    return address;
}

double ATSPeerInfo::getLag() const {
    return lag;
}

bool ATSPeerInfo::getIsJoined() const {
    return isJoined;
}

void ATSPeerInfo::setFreeResource(unsigned int freeResource) {
    this->freeResource = freeResource;
}

void ATSPeerInfo::setAddress(TransportAddress address) {
    this->address = address;
}

void ATSPeerInfo::setLag(double lag) {
    this->lag = lag;
}

void ATSPeerInfo::setIsJoined(bool isJoined) {
    this->isJoined = isJoined;
}

double ATSPeerInfo::getJoinScoreByDataSeq(unsigned int dataSeq) {
    if (freeResource > 0) {
        EV << "JoinScore:"
                  << getDataScoreByDataSeq(dataSeq)
                          / (dataTimeStamp[dataSeq] + lag) << "\n";
        return getDataScoreByDataSeq(dataSeq) / (dataTimeStamp[dataSeq] + lag);
    } else {
        EV << "JoinScore:" << 0 << "\n";
        return 0;
    }
}

double ATSPeerInfo::getInsertScoreByDataSeq(unsigned int dataSeq) {
    if (freeResource > 0 || getDataScoreByDataSeq(dataSeq) > 0) {
        EV << "InsertScore:" << 0 << "\n";
        return 0;
    } else {
        EV << "InsertScore:" << 0.2 / (dataTimeStamp[dataSeq] + lag) << "\n";
        return 0.2 / (dataTimeStamp[dataSeq] + lag);
    }
}

double ATSPeerInfo::getSwitchScoreByDataSeq(unsigned int dataSeq1,
        unsigned int dataSeq2) {
    bool hasDataSeq1Child = false;
    bool hasDataSeq2Child = false;
    for (unsigned int i = 0; i < childlinklist.size(); i++) {
        if (childlinklist[i]->getDataSeq() == dataSeq1) {
            hasDataSeq1Child = true;
        }
        if (childlinklist[i]->getDataSeq() == dataSeq2) {
            hasDataSeq2Child = true;
        }
    }
    if (hasDataSeq1Child && hasDataSeq2Child) {
        double result1 = 2 / (dataTimeStamp[dataSeq1] + lag);
        double result2 = 2 / (dataTimeStamp[dataSeq2] + lag);

        EV << "SwitchScore:" << (result1 + result2) / 2 << "\n";
        return (result1 + result2) / 2;
    } else {
        EV << "SwitchScore:" << 0 << "\n";
        return 0;
    }
}
double ATSPeerInfo::getDataScoreByDataSeq(unsigned int dataSeq) {
    unsigned int dataNum = 0;
    if (childlinklist.size() == 0) {
        return 1;
    }
    for (unsigned int i = 0; i < childlinklist.size(); i++) {
        if (childlinklist[i]->getDataSeq() == dataSeq) {
            dataNum++;
        }
    }
    return dataNum / childlinklist.size();
}
double ATSPeerInfo::getDataRatioByDataSeq(unsigned int dataSeq) {
    unsigned int dataNum = 0;
    if (childlinklist.size() == 0) {
        return 1;
    }
    for (unsigned int i = 0; i < childlinklist.size(); i++) {
        if (childlinklist[i]->getDataSeq() == dataSeq) {
            dataNum++;
        }
    }
    return dataNum / childlinklist.size();
}

TransportAddress ATSPeerInfo::getChildAddressByDataSeq(unsigned int dataSeq) {
    for (unsigned int i = 0; i < childlinklist.size(); i++) {
        if (childlinklist[i]->getDataSeq() == dataSeq) {
            return childlinklist[i]->getTargetAddress();
        }
    }
    EV << "ATSPeerInfo::nonChild\n";
    return address;
}

unsigned int ATSPeerInfo::getChildIndexByDataSeq(unsigned int dataSeq) {
    for (unsigned int i = 0; i < childlinklist.size(); i++) {
        if (childlinklist[i]->getDataSeq() == dataSeq) {
            return i;
        }
    }
    EV << "ATSPeerInfo::nonChild\n";
    return 0;
}
ATSPeerInfo::ATSPeerInfo() {

}

double ATSPeerInfo::result2score(double result) {
    double PI_FIX = 3.14159265 + 0.01; // used to make score bigger than 0.
    return PI_FIX - atan(result);
}

ATSPeerInfo::~ATSPeerInfo() {
    for (unsigned int i = 0; i < parentlinklist.size(); i++) {
        delete parentlinklist[i];
    }
    parentlinklist.clear();
    for (unsigned int i = 0; i < childlinklist.size(); i++) {
        delete childlinklist[i];
    }
    childlinklist.clear();
    dataTimeStamp.clear();
}
