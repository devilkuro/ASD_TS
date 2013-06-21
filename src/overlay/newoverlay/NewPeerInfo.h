/*
 * NewPeerInfo.h
 *
 *  Created on: 2012-11-2
 *      Author: Fanjing
 */

#ifndef NEWPEERINFO_H_
#define NEWPEERINFO_H_
#include <vector>
#include "BaseOverlay.h"
typedef std::vector<TransportAddress> TransportAddressVector;
typedef std::vector<unsigned int> DataSeqVerctor;
typedef std::vector<simtime_t> TimeStampVector;

class NewPeerInfo
{
public:
    TransportAddress nodeAddress;

    TransportAddressVector parentList;

    TransportAddressVector childList;
    DataSeqVerctor childDataSeqList;

    TimeStampVector dataTimeStamp;
    unsigned int freeDegree;

    double getChildDataRate(unsigned int seq);
    TransportAddress getChildByDataSeq(unsigned int seq);
public:
    NewPeerInfo();
    virtual ~NewPeerInfo();
};

#endif /* NEWPEERINFO_H_ */
