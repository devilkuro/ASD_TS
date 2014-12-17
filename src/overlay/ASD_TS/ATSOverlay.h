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

#ifndef ATSOVERLAY_H_
#define ATSOVERLAY_H_
//util_class
#include <vector>

#include <GlobalStatistics.h>
//baseoverlay_class
#include "BaseOverlay.h"

//related_classes
#include "ATSOverlay_m.h"
#include "ATSPeerManager.h"
#include "ATSPeerInfo.h"
#include "ATSLink.h"


class ATSOverlay: public BaseOverlay

{
private:
    simtime_t SECOND;
    enum NodeType
    {
        Server = 0, Peer = 1
    };

    enum NodeState
    {
        NodeState_Init = 0,
        NodeState_Query = 1,
        NodeState_Wait = 2,
        NodeState_JoinEval = 3,
        NodeState_Joining = 4,
        NodeState_Joined = 5
    };

    typedef std::vector<ATSLink*> ATSLinkVector;
    typedef std::vector<ATSPeerInfo*> ATSPeerInfoVector;

    //节点父节点状态
    ATSLinkVector parentLinkList;
    //子节点状态
    ATSLinkVector childLinkList;
    //各数据流时间戳
    std::vector<double> dataTimeStamp;
    std::vector<unsigned int> dataHops;
    //网络成员状态
    ATSPeerInfoVector PeerInfoList;

    TransportAddress ServerAddress;
    TransportAddress nodeAddress;

    unsigned int inputDegree;
    unsigned int outputDegree;
    unsigned int freeDegree;
    unsigned int serverFreeDegree;
    //记录每个支流的孩子节点数量
    std::vector<unsigned int> ChildNum_dataSeq;//数组大小等于inputDegree

    unsigned int memberNum;
    //Only used by Server node
    unsigned joinedMemberNum;
    unsigned readyMenberNum;
    bool isBusy;    // server is busy

    NodeState nodeState;
    //DEBUG
    unsigned int targetOverlayTerminalNum;
    unsigned int seq;
    unsigned int infoCollectNum;
    double startTime;
    double endTime;
    unsigned int forceInsertTimes;
    unsigned int resourceErrorTimes;

    //HandleATSMessage
    void handleATSMessgae(ATSMessage* atsMsg);

    void handleATSQueryMessage(ATSQueryMessage* atsQueryMsg);

    void handleATSQueryResponseMessage(ATSQueryResponseMessage* atsQueryResponseMsg);

    void handleATSJoinEvalMessage(ATSJoinEvalMessage* atsJoinEvalMsg);

    void handleATSJoinEvalResponseMessage(ATSJoinEvalResponseMessage* atsJoinEvalResponseMsg);

    void handleATSJoinMessage(ATSJoinMessage* atsJoinMsg);

    void handleATSJoinResponseMessage(ATSJoinResponseMessage* atsJoinResponseMsg);

    void handleATSInsertMessage(ATSInsertMessage* atsInsertMsg);

    void handleATSInsertResponseMessage(ATSInsertResponseMessage* atsInsertResponseMsg);

    void handleATSJoinSuccessMessage(ATSJoinSuccessMessage* atsJoinSuccessMsg);

    void handleATSStatisticMessage(ATSStatisticMessage* atsStatisticMsg);

    void handleATSChildNumIncreaseMessage(ATSChildNumIncreaseMessage* atsChildNumIncreaseMsg);//增加对应支流的子节点数量

    //Subfunctions
    void sendATSQueryResponseMessage(TransportAddress address);
    void initializeATSMessage(ATSMessage* atsMsg);
    unsigned int calculateATSMessageBitLength(ATSMessage* atsMsg);
    void setATSMessageBitLength(ATSMessage* atsMsg);
    void sendATSMessageToUDP(ATSMessage* atsMsg,TransportAddress address);
    void startJoinProcess();
    void checkNodeState();
    void updateVisualization();
    unsigned int getDataNumBySeq(unsigned int seq);
	//通过TransportAddress来取得lag
	double getLagByAddress(TransportAddress address);


public:
    virtual void initializeOverlay(int stage);

    virtual void handleTimerEvent(cMessage* msg);

    virtual void handleUDPMessage(BaseOverlayMessage* msg);

    virtual void handleAppMessage(cMessage* msg);

    virtual void finishOverlay();

public:
    ATSOverlay();
    virtual ~ATSOverlay();
};

#endif /* ATSOVERLAY_H_ */
