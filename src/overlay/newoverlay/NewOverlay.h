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

#ifndef NEWOVERLAY_H_
#define NEWOVERLAY_H_

#include <vector>

#include "common/UnderlayConfigurator.h"
#include "common/GlobalStatistics.h"

#include "BaseOverlay.h"

#include "NewOverlay_m.h"
#include "NewPeerInfo.h"

class NewOverlay: public BaseOverlay
{

private:
    enum NodeType{
        ServerNode = 0,
        PeerNode = 1,
    } nodeType;

    enum NodeState{
        NodeState_Init = 0,
        NodeState_Query = 1,
        NodeState_JoinEval = 2,
        NodeState_Join = 3,
        NodeState_InsertQuery = 4,
        NodeState_Insert = 5,
        NodeState_Wait = 6,
        NodeState_Joined = 7
    } nodeState;
    enum LinkState{
        Link_Init = 0,
        Link_Selected = 1,
        Link_Connected = 2,
    };

    typedef std::vector<TransportAddress> TransportAddressVector;
    typedef std::vector<unsigned int> DataSeqVerctor;
    typedef std::vector<simtime_t> TimeStampVector;
    typedef std::vector<NewPeerInfo*> NewPeerInfoVector;
    typedef std::vector<LinkState> LinkStateList;

    TransportAddress serverNode;
    TransportAddress nodeAddress;

    TransportAddressVector nodeList;
    TransportAddressVector joinedNodeList;
    TransportAddressVector parentList;
    LinkStateList parentStateList;

    TimeStampVector dataTimeStamp;

    TransportAddressVector childList;
    DataSeqVerctor childDataSeqList;
    LinkStateList childStateList;

    NewPeerInfoVector peerInfoList;
    unsigned int serverFreeDegree;
    unsigned int freeDegree;
    unsigned int peerRatio;
    unsigned int numOfLayers;
    unsigned int k;
    unsigned int in;
    unsigned int terminalNum;
    int myKey;


    cMessage *joinTimer;
    cMessage *visualizationTimer;

    // Statistics
    simtime_t queryTime;
    simtime_t joinEvalTime;
    simtime_t joinTime;
    simtime_t joinSuccessTime;
    std::vector<unsigned int> jumpNum;

    // Methods

    void handleTimerEvent(cMessage *msg);

    void initializeOverlay(int stage);
    void setOwnNodeID();
    void joinOverlay();
    void finishOverlay();
    bool isSiblingFor(const NodeHandle& node,const OverlayKey& key, int numSiblings, bool* err);
    NodeVector *findNode(const OverlayKey& key, int numRedundantNodes, int numSiblings, BaseOverlayMessage* msg);
    // obligatory: Set the maximum number of siblings that can be queried about (usually 1)
    int getMaxNumSiblings();

    // obligatory: Set the maximum number of redundant nodes that can be queried about (usually 1)
    int getMaxNumRedundantNodes();
    void handleUDPMessage(BaseOverlayMessage *msg);

    void handleNewQueryMessage(NewQueryMessage *msg);
    void handleNewQueryResponseMessage(NewQueryResponseMessage *msg);

    void handleNewJoinEvalMessage(NewJoinEvalMessage *msg);
    void handleNewJoinEvalResponseMessage(NewJoinEvalResponseMessage *msg);


    void handleNewJoinMessage(NewJoinMessage *msg);
    void handleNewJoinResponseMessage(NewJoinResponseMessage *msg);
    void startJoiningOverlay();
    void checkLinkState();
    void finishJoiningOverlay();
    void updateVisualization();

    void handleNewInsertQueryMessage(NewInsertQueryMessage *msg);
    void handleNewInsertQueryResponseMessage(NewInsertQueryResponseMessage *msg);

    void handleNewInsertEvalMessage(NewInsertEvalMessage *msg);
    void handleNewInsertEvalResponseMessage(NewInsertEvalResponseMessage *msg);

    void handleNewInsertMessage(NewInsertMessage *msg);
    void handleNewInsertResponseMessage(NewInsertResponseMessage *msg);

    void handleNewJoinSuccessMessage(NewJoinSuccessMessage *msg);

    void handleNewStatisticMessage(NewStatisticMessage *msg);

public:
    NewOverlay();
    virtual ~NewOverlay();
};

#endif /* NEWOVERLAY_H_ */
