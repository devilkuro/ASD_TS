/*
 * NewPeerInfo.cpp
 *
 *  Created on: 2012-11-2
 *      Author: Fanjing
 */

#include "NewPeerInfo.h"

double NewPeerInfo::getChildDataRate(unsigned int seq)
{
    double result;
    if (childDataSeqList.size() != 0) {
        double *dataSeqRate = new double[parentList.size()];
        for (unsigned int i = 0; i < parentList.size(); i++) {
            dataSeqRate[i] = 0;
        }
        for (unsigned int i = 0; i < childDataSeqList.size(); i++) {
            dataSeqRate[childDataSeqList[i]] += 1;
        }
        for (unsigned int i = 0; i < parentList.size(); i++) {
            dataSeqRate[i] = dataSeqRate[i] / childDataSeqList.size();
        }
        result = dataSeqRate[seq];
        delete dataSeqRate;
        return result;
    }
    return 0;
}

TransportAddress NewPeerInfo::getChildByDataSeq(unsigned int seq)
{
    for(unsigned int i=0;i<childList.size();i++){
        if(seq==childDataSeqList[i])
            return childList[i];
    }
    return nodeAddress;
}

NewPeerInfo::NewPeerInfo()
{
// TODO Auto-generated constructor stub
}

NewPeerInfo::~NewPeerInfo()
{
    // TODO Auto-generated destructor stub
}
