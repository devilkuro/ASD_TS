//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PAdouble ATSOverlay::getLagByAddress(TransportAddress address)

//RTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "ATSOverlay.h"

// Important! This line must be present for each module you extend (see BaseApp)
Define_Module(ATSOverlay);

#define BIGBIT (1 << 24)

static const char *newArrows[] = { "m=m,50,50,50,50;ls=orange,2",
        "m=m,50,50,50,50;ls=magenta,3", "m=m,50,50,50,50;ls=red,4",
        "m=m,50,50,50,50;ls=orange,5", "m=m,50,50,50,50;ls=green,6",
        "m=m,50,50,50,50;ls=aquamarine,7", "m=m,50,50,50,50;ls=cyan,8",
        "m=m,50,50,50,50;ls=blue,9", "m=m,50,50,50,50;ls=navy,10",
        "m=m,50,50,50,50;ls=yellow,11" };
// Overwrite BaseOverlay
void ATSOverlay::initializeOverlay(int stage) {
    if (stage != MIN_STAGE_OVERLAY)
        return; //第8阶段为overlay层

    SECOND = 1.0;
    ServerAddress = TransportAddress(IPAddress(BIGBIT + 1), thisNode.getPort());
    nodeAddress = TransportAddress(thisNode.getIp(), thisNode.getPort());

    inputDegree = par("inputDegree");
    outputDegree = par("outputDegree");
    targetOverlayTerminalNum = par("targetOverlayTerminalNum");
    seq = par("seq");
    infoCollectNum = par("infoCollectNum");
    freeDegree = outputDegree;
    serverFreeDegree = outputDegree;

    memberNum = 0;
    joinedMemberNum = 0;
    readyMenberNum = 0;
    isBusy = false;
    //记录每个支流的孩子节点数量
    for (unsigned int i = 0; i < inputDegree; i++) {
        ChildNum_dataSeq.push_back(0); //开始每只节点的孩子支流的子节点全部为0
    }

    WATCH(isBusy);
    WATCH(joinedMemberNum);
    WATCH(readyMenberNum);

    getParentModule()->getParentModule()->getDisplayString().setTagArg("i", 0,
            "device/pc_vs");
    getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 0,
            "block/circle_s");
    if (nodeAddress != ServerAddress) {
        ATSQueryMessage* atsQueryMsg = new ATSQueryMessage("atsQueryMsg"); //初始化后立即新建询问消息请求加入
        sendATSMessageToUDP(atsQueryMsg, ServerAddress);
    } else {
        getParentModule()->getParentModule()->getDisplayString().setTagArg("i2",
                1, "black");
    }
}

void ATSOverlay::handleUDPMessage(BaseOverlayMessage* msg) {
    EV << "ATSOverlay::handleUDPMessage@Time:" << simTime() << std::endl;
    if (dynamic_cast<ATSMessage*>(msg) != NULL) {
        ATSMessage *atsMsg = check_and_cast<ATSMessage*>(msg);
        handleATSMessgae(atsMsg);
    } else {
        delete (msg);
    }
}
void ATSOverlay::handleAppMessage(cMessage* msg) {
    if (msg) {
        delete (msg);
    }
}
void ATSOverlay::handleTimerEvent(cMessage* msg) {
    if (msg) {
        delete (msg);
    }
}

unsigned int ATSOverlay::getDataNumBySeq(unsigned int seq) {
    unsigned int dataNum = 0;
    if (childLinkList.size() == 0) {
        return 0;
    }
    for (unsigned int i = 0; i < childLinkList.size(); i++) {
        if (childLinkList[i]->getDataSeq() == seq) {
            dataNum++;
        }
    }
    return dataNum;
}
void ATSOverlay::finishOverlay() {

    if (nodeState == NodeState_Joined && nodeAddress != ServerAddress) {
        double maxDataTimeStamp = 0;
        for (unsigned int i = 0; i < dataTimeStamp.size(); i++) {
            if (i == 0) {
                globalStatistics->recordOutVector(
                        "Fanjing:ATS:maxdataTimeStamp0", dataTimeStamp[i]);
                globalStatistics->recordOutVector("Fanjing:ATS:maxdataHops0",
                        dataHops[i]);
                globalStatistics->recordOutVector("Fanjing:ATS:maxdataDataNum0",
                        getDataNumBySeq(i));
            } else if (i == 1) {
                globalStatistics->recordOutVector(
                        "Fanjing:ATS:maxdataTimeStamp1", dataTimeStamp[i]);
                globalStatistics->recordOutVector("Fanjing:ATS:maxdataHops1",
                        dataHops[i]);
                globalStatistics->recordOutVector("Fanjing:ATS:maxdataDataNum1",
                        getDataNumBySeq(i));
            } else if (i == 2) {
                globalStatistics->recordOutVector(
                        "Fanjing:ATS:maxdataTimeStamp2", dataTimeStamp[i]);
                globalStatistics->recordOutVector("Fanjing:ATS:maxdataHops2",
                        dataHops[i]);
                globalStatistics->recordOutVector("Fanjing:ATS:maxdataDataNum2",
                        getDataNumBySeq(i));
            }
            maxDataTimeStamp =
                    maxDataTimeStamp > dataTimeStamp[i] ?
                            maxDataTimeStamp : dataTimeStamp[i];
        }
        globalStatistics->recordOutVector("Fanjing:ATS:maxdataTimeStamp",
                maxDataTimeStamp);
        globalStatistics->recordOutVector("Fanjing:ATS:JoinTime",
                endTime - startTime);
    }
}

// Private functions
void ATSOverlay::handleATSMessgae(ATSMessage *atsMsg) {
    ATSQueryMessage *atsQueryMsg;
    ATSQueryResponseMessage *atsQueryResponseMsg;
    ATSJoinEvalMessage *atsJoinEvalMsg;
    ATSJoinEvalResponseMessage *atsJoinEvalResponseMsg;
    ATSJoinMessage *atsJoinMsg;
    ATSJoinResponseMessage *atsJoinResponseMsg;
    ATSInsertMessage *atsInsertMsg;
    ATSInsertResponseMessage *atsInsertResponseMsg;
    ATSJoinSuccessMessage *atsJoinSuccessMsg;
    ATSStatisticMessage *atsStatisticMsg;
    ATSChildNumIncreaseMessage *atsChildNumIncreaseMsg;
    updateVisualization();
    switch (atsMsg->getCommand()) {
    case ATS_NULL:
        //EV<< "ATSOverlay::handleATSMessage@Time" <<simTime()<<"\n"<<"{\tError:unInitialized Message Type.}\n";
        if (nodeAddress == ServerAddress) {
            readyMenberNum++;
            if (readyMenberNum == joinedMemberNum * inputDegree) {
                readyMenberNum = 0;
                isBusy = false;
                if (joinedMemberNum < PeerInfoList.size()) {
                    for (unsigned int i = 0; i < PeerInfoList.size(); i++) {
                        if (!PeerInfoList[i]->getIsJoined()) {
                            sendATSQueryResponseMessage(
                                    PeerInfoList[i]->getAddress());
                            break;
                        }
                    }
                }
            }
        } else {
            for (unsigned int i = 0; i < childLinkList.size(); i++) {
                if (0 == childLinkList[i]->getDataSeq()) {
                    sendATSMessageToUDP(atsMsg->dup(),
                            childLinkList[i]->getTargetAddress());
                }
            }

        }
        break;
    case ATS_QUERY:
        atsQueryMsg = check_and_cast<ATSQueryMessage*>(atsMsg);
        handleATSQueryMessage(atsQueryMsg);
        break;
    case ATS_QUERY_RESPONSE:
        atsQueryResponseMsg = check_and_cast<ATSQueryResponseMessage*>(atsMsg);
        handleATSQueryResponseMessage(atsQueryResponseMsg);
        break;
    case ATS_JOINEVAL:
        atsJoinEvalMsg = check_and_cast<ATSJoinEvalMessage*>(atsMsg);
        handleATSJoinEvalMessage(atsJoinEvalMsg);
        break;
    case ATS_JOINEVAL_RESPONSE:
        atsJoinEvalResponseMsg = check_and_cast<ATSJoinEvalResponseMessage*>(
                atsMsg);
        handleATSJoinEvalResponseMessage(atsJoinEvalResponseMsg);
        break;
    case ATS_JOIN:
        atsJoinMsg = check_and_cast<ATSJoinMessage*>(atsMsg);
        handleATSJoinMessage(atsJoinMsg);
        break;
    case ATS_JOIN_RESPONSE:
        atsJoinResponseMsg = check_and_cast<ATSJoinResponseMessage*>(atsMsg);
        handleATSJoinResponseMessage(atsJoinResponseMsg);
        break;
    case ATS_INSERT:
        atsInsertMsg = check_and_cast<ATSInsertMessage*>(atsMsg);
        handleATSInsertMessage(atsInsertMsg);
        break;
    case ATS_INSERT_RESPONSE:
        atsInsertResponseMsg = check_and_cast<ATSInsertResponseMessage*>(
                atsMsg);
        handleATSInsertResponseMessage(atsInsertResponseMsg);
        break;
    case ATS_JOIN_SUCCESS:
        atsJoinSuccessMsg = check_and_cast<ATSJoinSuccessMessage*>(atsMsg);
        handleATSJoinSuccessMessage(atsJoinSuccessMsg);
        break;
    case ATS_STATISTIC:
        atsStatisticMsg = check_and_cast<ATSStatisticMessage*>(atsMsg);
        handleATSStatisticMessage(atsStatisticMsg);
        break;
    case ATS_CHILD_NUM_INCREASE: //更新孩子节点的消息
        atsChildNumIncreaseMsg = check_and_cast<ATSChildNumIncreaseMessage*>(
                atsMsg);
        handleATSChildNumIncreaseMessage(atsChildNumIncreaseMsg);
        break;
    default:
        EV << "ATSOverlay::handleATSMessage@Time" << simTime() << "\n"
                  << "{\tError:unKnown Message Type.}\n";
        break;
    }
    if (atsMsg) {
        delete (atsMsg);
    }
}

void ATSOverlay::handleATSQueryMessage(ATSQueryMessage *atsQueryMsg) {
    EV << "ATSOverlay::handleATSQueryMessage@Time" << simTime() << "\n";
    ATSPeerInfo* atsPeerInfo = new ATSPeerInfo(); //新建一个节点列表，设置节点状态信息
    atsPeerInfo->setAddress(atsQueryMsg->getSourceAddress()); //节点地址即传过来的atsQueryMsg的地址
    atsPeerInfo->setIsJoined(false); //未加入组播组
    PeerInfoList.push_back(atsPeerInfo);
    if (!isBusy) { //若节点处于非busy状态，则调用发送询问反馈函数
        sendATSQueryResponseMessage(atsQueryMsg->getSourceAddress());
    }
}

void ATSOverlay::initializeATSMessage(ATSMessage* atsMsg) {
    atsMsg->setSourceAddress(thisNode);
    atsMsg->setSendTime(simTime() / SECOND);
}

//计算消息长度
unsigned int ATSOverlay::calculateATSMessageBitLength(ATSMessage* atsMsg) {

    ATSQueryMessage *atsQueryMsg;
    ATSQueryResponseMessage *atsQueryResponseMsg;
    ATSJoinEvalMessage *atsJoinEvalMsg;
    ATSJoinEvalResponseMessage *atsJoinEvalResponseMsg;
    ATSJoinMessage *atsJoinMsg;
    ATSJoinResponseMessage *atsJoinResponseMsg;
    ATSInsertMessage *atsInsertMsg;
    ATSInsertResponseMessage *atsInsertResponseMsg;
    ATSJoinSuccessMessage *atsJoinSuccessMsg;
    ATSStatisticMessage *atsStatisticMsg;
    ATSChildNumIncreaseMessage *atsChildNumIncreaseMsg;

    unsigned int result = 0;
    switch (atsMsg->getCommand()) {
    case ATS_NULL:
        result = ATSMESSAGE_L(atsMsg);
        break;
    case ATS_QUERY:
        atsQueryMsg = check_and_cast<ATSQueryMessage*>(atsMsg);
        result = ATSQUERYMESSAGE_L(atsQueryMsg);
        break;
    case ATS_QUERY_RESPONSE:
        atsQueryResponseMsg = check_and_cast<ATSQueryResponseMessage*>(atsMsg);
        result = ATSQUERYRESPONSEMESSAGE_L(atsQueryResponseMsg);
        break;
    case ATS_JOINEVAL:
        atsJoinEvalMsg = check_and_cast<ATSJoinEvalMessage*>(atsMsg);
        result = ATSJOINEVALMESSAGE_L(atsJoinEvalMsg);
        break;
    case ATS_JOINEVAL_RESPONSE:
        atsJoinEvalResponseMsg = check_and_cast<ATSJoinEvalResponseMessage*>(
                atsMsg);
        result = ATSJOINEVALRESPONSEMESSAGE_L(atsJoinEvalResponseMsg);
        break;
    case ATS_JOIN:
        atsJoinMsg = check_and_cast<ATSJoinMessage*>(atsMsg);
        result = ATSJOINMESSAGE_L(atsJoinMsg);
        break;
    case ATS_JOIN_RESPONSE:
        atsJoinResponseMsg = check_and_cast<ATSJoinResponseMessage*>(atsMsg);
        result = ATSJOINRESPONSEMESSAGE_L(atsJoinResponseMsg);
        break;
    case ATS_INSERT:
        atsInsertMsg = check_and_cast<ATSInsertMessage*>(atsMsg);
        result = ATSINSERTMESSAGE_L(atsInsertMsg);
        break;
    case ATS_INSERT_RESPONSE:
        atsInsertResponseMsg = check_and_cast<ATSInsertResponseMessage*>(
                atsMsg);
        result = ATSINSERTRESPONSEMESSAGE_L(atsInsertResponseMsg);
        break;
    case ATS_JOIN_SUCCESS:
        atsJoinSuccessMsg = check_and_cast<ATSJoinSuccessMessage*>(atsMsg);
        result = ATSJOINSUCCESSMESSAGE_L(atsJoinSuccessMsg);
        break;
    case ATS_STATISTIC:
        atsStatisticMsg = check_and_cast<ATSStatisticMessage*>(atsMsg);
        result = ATSSTATISTICMESSAGE_L(atsStatisticMsg);
        break;
    case ATS_CHILD_NUM_INCREASE:
        atsChildNumIncreaseMsg = check_and_cast<ATSChildNumIncreaseMessage*>(
                atsMsg);
        break;
    default:
        EV << "ATSOverlay::setATSMessageBitLength@Time" << simTime() << "\n"
                  << "{\tError:unKnown Message Type.}\n";
        result = 0;
        break;
    }
    return result;
}

//设置消息长度
void ATSOverlay::setATSMessageBitLength(ATSMessage* atsMsg) {
    atsMsg->setBitLength(calculateATSMessageBitLength(atsMsg));
}
//Send ATSMessage to certain Address with sourceAddress and sendTime
void ATSOverlay::sendATSMessageToUDP(ATSMessage* atsMsg,
        TransportAddress address) {

    initializeATSMessage(atsMsg);
    setATSMessageBitLength(atsMsg);
    sendMessageToUDP(address, atsMsg);
}

//Send ATSQueryResponseMessage to certain Address
//服务器向节点发送请求回应报文
void ATSOverlay::sendATSQueryResponseMessage(TransportAddress address) {
    isBusy = true;
    ATSQueryResponseMessage* atsQueryResponseMsg = new ATSQueryResponseMessage(
            "atsQueryResponseMsg"); //新建询问反馈消息
    int mSize = 0; //统计树内部节点数量用
    for (unsigned int i = 0; i < PeerInfoList.size(); i++) { //统计树内部节点数量
        if (PeerInfoList[i]->getIsJoined())
            mSize++;
    }
    atsQueryResponseMsg->setMemberAddressArraySize(mSize); //设置地址数组大小
    for (unsigned int i = 0, j = 0; i < PeerInfoList.size(); i++) { //将组播组内的节点发送给待连接的新节点
        if (PeerInfoList[i]->getIsJoined()) {
            atsQueryResponseMsg->setMemberAddress(j,
                    PeerInfoList[i]->getAddress()); //设置对应地址
            j++;
        }
    }
    atsQueryResponseMsg->setFreeDegree(freeDegree); //设置出度
    sendATSMessageToUDP(atsQueryResponseMsg, address);
}

//处理询问反馈报文
void ATSOverlay::handleATSQueryResponseMessage(
        ATSQueryResponseMessage *atsQueryResponseMsg) {
    startTime = simTime() / SECOND
            - 2 * (simTime() / SECOND - atsQueryResponseMsg->getSendTime()); //获取开始时间
    serverFreeDegree = atsQueryResponseMsg->getFreeDegree(); //获取服务节点的自由度
    if (inputDegree <= serverFreeDegree) { //服务器有多余出度，直接加入
        startJoinProcess(); //开始加入过程
    } else {
        memberNum = atsQueryResponseMsg->getMemberAddressArraySize(); //得到节点数量
        for (unsigned int i = 0;
                i < atsQueryResponseMsg->getMemberAddressArraySize(); i++) { //依次发送评估消息
            ATSJoinEvalMessage* atsJoinEvalMsg = new ATSJoinEvalMessage(
                    "atsJoinEvalMsg"); //新建评估消息
            sendATSMessageToUDP(atsJoinEvalMsg,
                    atsQueryResponseMsg->getMemberAddress(i));
        }
    }
}

void ATSOverlay::handleATSJoinEvalMessage(ATSJoinEvalMessage *atsJoinEvalMsg) {
    EV << "ATSOverlay::handleATSJoinEvalMessage@Time" << simTime() << "\n";
    EV << "\tdataTimeStamp.size()" << dataTimeStamp.size() << "\n";
    ATSJoinEvalResponseMessage* atsJoinEvalResponseMsg =
            new ATSJoinEvalResponseMessage("atsJoinEvalResponseMsg"); //新建评估反馈消息
    atsJoinEvalResponseMsg->setFreeDegree(freeDegree);                   //设置自由度
    atsJoinEvalResponseMsg->setDataTimeStampArraySize(dataTimeStamp.size()); //设置时间戳数组大小
    for (unsigned int i = 0; i < dataTimeStamp.size(); i++) {
        atsJoinEvalResponseMsg->setDataTimeStamp(i, dataTimeStamp[i]); //为每一条时间戳赋值
    }
    atsJoinEvalResponseMsg->setParentAddressArraySize(parentLinkList.size());
    for (unsigned int i = 0; i < parentLinkList.size(); i++) {
        atsJoinEvalResponseMsg->setParentAddress(i,
                parentLinkList[i]->getTargetAddress()); //为每个父节点赋值
    }
    atsJoinEvalResponseMsg->setParentlagArraySize(parentLinkList.size()); //设置每个父节点的lag
    for (unsigned int i = 0; i < parentLinkList.size(); i++) {
        atsJoinEvalResponseMsg->setParentlag(i, parentLinkList[i]->getLag());
    }
    atsJoinEvalResponseMsg->setChildAddressArraySize(childLinkList.size());
    atsJoinEvalResponseMsg->setChildDataSeqArraySize(childLinkList.size());
    for (unsigned int i = 0; i < childLinkList.size(); i++) {
        atsJoinEvalResponseMsg->setChildAddress(i,
                childLinkList[i]->getTargetAddress());    //设置孩子节点目标节点
        atsJoinEvalResponseMsg->setChildDataSeq(i,
                childLinkList[i]->getDataSeq());
    }
    atsJoinEvalResponseMsg->setChildlagArraySize(childLinkList.size()); //设置每个孩子节点的lag
    for (unsigned int i = 0; i < childLinkList.size(); i++) {
        atsJoinEvalResponseMsg->setChildlag(i, childLinkList[i]->getLag());
    }
    atsJoinEvalResponseMsg->setChildNum_dataSeqArraySize(
            ChildNum_dataSeq.size());
    for (unsigned int i = 0; i < ChildNum_dataSeq.size(); i++) {   //设置孩子节点的支流数量
        atsJoinEvalResponseMsg->setChildNum_dataSeq(i, ChildNum_dataSeq[i]);
    }
    sendATSMessageToUDP(atsJoinEvalResponseMsg,
            atsJoinEvalMsg->getSourceAddress());
}

//开始加入过程，分为3种形式加入，将网络情况打分，按分数高低选择合适的加入方式
void ATSOverlay::startJoinProcess() {
    EV << "ATSOverlay::startJoinProcess@Time" << simTime() << "\n";
    for (unsigned int i = 0; i < inputDegree; i++) {
        ATSLink *atsLink = new ATSLink(); //新建节点信息
        atsLink->setDataSeq(i); //为每条支流
        atsLink->setState(ATS_LINK_INIT);
        parentLinkList.push_back(atsLink);
        double timeStamp = 0;
        dataTimeStamp.push_back(timeStamp);
        dataHops.push_back(0);
    }
    EV << "\tdataTimeStamp.size()" << dataTimeStamp.size() << "\n";
    for (unsigned int i = 0; i < inputDegree; i++) { //利用一个循环，每个出度都是分别添加，以下内容是每条支流单独加入的过程
        //If the link has already selected, break out.
        if (parentLinkList[i]->getState() != ATS_LINK_INIT) { //检查节点状态
            continue;
        }
        //Use server free resource
        if (serverFreeDegree > 0) { //若服务器包含多余出度则直接加入
            EV << "ATSOverlay::Server\n";
            ATSJoinMessage* atsJoinMsg = new ATSJoinMessage("atsJoinMsg_S"); //服务器上的第一个孩子按照1方式加入，发送JoinMsg
            atsJoinMsg->setDataSeq(i);
            parentLinkList[i]->setTargetAddress(ServerAddress); //第一个节点加入时每条支流的父节点都是服务器节点
            parentLinkList[i]->setState(ATS_LINK_SELECTED); //节点的状态需要置为被选择状态
            serverFreeDegree--; //自由的出度减一
            sendATSMessageToUDP(atsJoinMsg, ServerAddress);
        }
        //Use peer nodes resource
        //若服务器没有多余节点则采取打分机制
        else {
            double maxJoinScore = 0;
            double maxInsertScore = 0;
            double maxSwitchScore = 0;
            unsigned int maxJoinNum = 0;
            unsigned int maxInsertNum = 0;
            unsigned int maxSwitchNum = 0;
            unsigned int maxSwitchSeq1 = 0;
            unsigned int maxSwitchSeq2 = 0;
            unsigned int tag = 0;		//标记B中离D最近的孩子
            for (unsigned int j = 0; j < PeerInfoList.size(); j++) {
                double joinScore = PeerInfoList[j]->getJoinScoreByDataSeq(i); //若采取Join加入方式1&2a，获得的影响分数
                if (joinScore > maxJoinScore) {
                    maxJoinScore = joinScore;
                    maxJoinNum = j;
                }
                double lagTF = getLagByAddress(
                        PeerInfoList[j]->parentlinklist[i]->getTargetAddress());
                double insertScore = PeerInfoList[j]->getInsertScoreByDataSeq(i,
                        lagTF); //若采取Insert加入方式3，获得影响分数
                if (insertScore > maxInsertScore) {
                    maxInsertScore = insertScore;
                    maxInsertNum = j;
                }
                double switchScore = 0;
                unsigned int switchSeq1 = 0;
                unsigned int switchSeq2 = 0;
                for (unsigned int k = i + 1; k < inputDegree; k++) {
                    if (parentLinkList[k]->getState() == ATS_LINK_INIT) {

                        //A0->B直接根据B的父节点表查得
                        double lag1 =
                                PeerInfoList[j]->parentlinklist[k]->getLag();
                        //A0->D延时，在B的父节点中获取地址
                        double lag2 =
                                getLagByAddress(
                                        PeerInfoList[j]->parentlinklist[k]->getLinkOwnerAddress());
                        //D->B延时,直接从D的列表中获取到B的延时
                        double lag3 = getLagByAddress(
                                PeerInfoList[j]->getAddress());
                        //B->C0取B的孩子中到D最短的节点到B的延时
                        double minLag1 = 0;
                        //D->C0取B的孩子中到D最短的节点到D的延时
                        double minLag2 = 0;
                        if (PeerInfoList[j]->childlinklist.size() != 0) { //若B节点的孩子不为空
                            //EV<<"PeerInfoList[j]->childlinklist.size()"<<endl;
                            if (!PeerInfoList[j]->getChildAddressByDataSeq(k).isUnspecified()
                                    && PeerInfoList[j]->getChildAddressByDataSeq(
                                            k)
                                            != PeerInfoList[j]->getAddress()) {
                                //返回地址为节点地址证明没有对应序列的子节点
                                //这里的k要做判断，对应的节点B，可能不转发seqK
                                //取B中孩子节点离D最近节点的lag
                                //EV<<"isUnspecified()"<<endl;
                                for (unsigned int n = 0;
                                        n
                                                < PeerInfoList[j]->childlinklist.size();
                                        n++) {
                                    //EV<<"n<PeerInfoList[j]->childlinklist.size()"<<endl;
                                    if (PeerInfoList[j]->childlinklist[n]->getDataSeq()
                                            == k) {
                                        //EV<<"PeerInfoList[j]->childlinklist[n]->getDataSeq()==k"<<endl;
                                        //筛选出数据流为K的B的孩子节点
                                        //在B的孩子中取到D延时最短的节点，取得到D的延时
                                        //TransportAddress address=PeerInfoList[j]->childlinklist[n]->getSelfAddress();
                                        if (minLag1 == 0) {
                                            minLag1 =
                                                    getLagByAddress(
                                                            PeerInfoList[j]->childlinklist[n]->getLinkOwnerAddress());
                                            tag = n;
                                            //在B的childlinklist里取C0到B的延时
                                            minLag2 =
                                                    PeerInfoList[j]->childlinklist[tag]->getLag();
                                        }
                                        //若B的孩子节点到D的延时更小（同时取到B的延时）
                                        if (minLag1
                                                > getLagByAddress(
                                                        PeerInfoList[j]->childlinklist[n]->getLinkOwnerAddress())) {
                                            //在D的PeerInfoList里取C0到D的延时
                                            minLag1 =
                                                    getLagByAddress(
                                                            PeerInfoList[j]->childlinklist[n]->getLinkOwnerAddress());
                                            tag = n;		//记录下B的孩子距离D最近的一个
                                            //在B的childlinklist里取C0到B的延时
                                            minLag2 =
                                                    PeerInfoList[j]->childlinklist[tag]->getLag();
                                        }
                                    } else {
                                        //若无dataSeq==k如何
                                        //minLag1=0;
                                        //minLag2=0;
                                    }
                                }
                            } else {							//若B不参与seqK的转发

                            }
                        } else {						//若B节点尚无孩子节点则将lag全部置0

                        }

                        double tempSwitchScore =
                                PeerInfoList[j]->getSwitchScoreByDataSeq(i, k,
                                        lag1, lag2, lag3, minLag1, minLag2);//若采取Switch加入方式2b，获得影响分数
                        EV << "SwitchScore:" << tempSwitchScore << endl;
                        if (tempSwitchScore > switchScore) {
                            switchScore = tempSwitchScore;
                            switchSeq1 = i;
                            switchSeq2 = k;
                        }
                    }
                }
                if (switchScore > maxSwitchScore) {
                    maxSwitchScore = switchScore;
                    maxSwitchNum = j;
                    maxSwitchSeq1 = switchSeq1;
                    maxSwitchSeq2 = switchSeq2;
                }
            }
            //若JoinScore为三者中的最大值，则采取第1种和1a种加入方式，
            //对应的取maxJoinSocre的地址，将该节点标志置为select并将可用资源减1
            if (maxJoinScore > 0 && maxJoinScore >= maxInsertScore
                    && maxJoinScore >= maxSwitchScore) {
                EV << "ATSOverlay::Join\n";
                ATSJoinMessage* atsJoinMsg = new ATSJoinMessage("atsJoinMsg_1"); //以第一种方式加入组播组，发Join消息
                atsJoinMsg->setDataSeq(i);
                parentLinkList[i]->setTargetAddress(
                        PeerInfoList[maxJoinNum]->getAddress());
                parentLinkList[i]->setState(ATS_LINK_SELECTED);
                PeerInfoList[maxJoinNum]->setFreeResource(
                        PeerInfoList[maxJoinNum]->getFreeResource() - 1);
                sendATSMessageToUDP(atsJoinMsg,
                        PeerInfoList[maxJoinNum]->getAddress());
            }
            //若Insert为三者中最大值，则采取第3种加入方式
            else if (maxInsertScore > 0 && maxInsertScore >= maxJoinScore
                    && maxInsertScore >= maxSwitchScore) {
                EV << "ATSOverlay::Insert\n";
                //Msg to peer[?]'s parent and be its child node
                //向maxInsertSocre的节点发送称为该孩子节点的请求，设置数据队列，置状态为selected
                ATSInsertMessage *insertMsgPPC = new ATSInsertMessage(
                        "insertMsgPPC_3"); //第三种加入方式
                insertMsgPPC->setBeChildNode(true);
                insertMsgPPC->setDataSeq(i);
                insertMsgPPC->setSelectedNodeAddress(
                        PeerInfoList[maxInsertNum]->getAddress());
                insertMsgPPC->setSelectedDataSeq(i);

                parentLinkList[i]->setTargetAddress(
                        PeerInfoList[maxInsertNum]->parentlinklist[i]->getTargetAddress());
                parentLinkList[i]->setState(ATS_LINK_SELECTED);
                sendATSMessageToUDP(insertMsgPPC,
                        PeerInfoList[maxInsertNum]->parentlinklist[i]->getTargetAddress());

                //Msg to peer[?] and be its parent node
                //向插入节点的原孩子发送请求，称为父节点，将它们全部加入自己的孩子列表中，并设置数据序列，置状态为selected
                ATSInsertMessage *insertMsgPC = new ATSInsertMessage(
                        "insertMsgPC_3"); //第三种加入方式
                insertMsgPC->setBeChildNode(false);
                insertMsgPC->setDataSeq(i);
                insertMsgPC->setSelectedNodeAddress(
                        PeerInfoList[maxInsertNum]->parentlinklist[i]->getTargetAddress());
                insertMsgPC->setSelectedDataSeq(i);

                ATSLink *childLink = new ATSLink();
                childLink->setTargetAddress(
                        PeerInfoList[maxInsertNum]->getAddress());
                childLink->setDataSeq(i);
                childLink->setLag(
                        getLagByAddress(
                                PeerInfoList[maxInsertNum]->getAddress()));
                childLink->setState(ATS_LINK_SELECTED);
                childLinkList.push_back(childLink);
                freeDegree = outputDegree - childLinkList.size();
                sendATSMessageToUDP(insertMsgPC,
                        PeerInfoList[maxInsertNum]->getAddress());
            }
            //SwitchSocre最高的话采取第2B种加入方案
            else if (maxSwitchScore > 0 && maxSwitchScore >= maxJoinScore
                    && maxSwitchScore >= maxInsertScore) {
                EV << "ATSOverlay::Switch\n";
                //Replace peer[?] to deliver seq1 from peer[?]'s parent node to peer[?] and one of its child, and get seq2 from peer[?].
                //Since peer[?] should continue to deliver the higher ratio seq, so we should confirm seq1 is the low ratio seq and seq2 is the higher one.
                if (PeerInfoList[maxSwitchNum]->getDataRatioByDataSeq(
                        maxSwitchSeq1)
                        > PeerInfoList[maxSwitchNum]->getDataRatioByDataSeq(
                                maxSwitchSeq2)) {
                    //若maxSwitchSeq1比率大于maxSwitchSeq2，即maxSwitchSeq1的分发数更多
                    //maxSwitchSeq1 += maxSwitchSeq2;
                    //maxSwitchSeq2 = maxSwitchSeq1 - maxSwitchSeq2;
                    //maxSwitchSeq1 = maxSwitchSeq1 - maxSwitchSeq2;
                    unsigned temp = maxSwitchSeq1;
                    maxSwitchSeq1 = maxSwitchSeq2;
                    maxSwitchSeq2 = temp;
                }
                unsigned seq1 = maxSwitchSeq1;
                unsigned seq2 = maxSwitchSeq2;
                //peer[?]'s parent which deliver seq1 to peer[?]
                TransportAddress ppAddress =
                        PeerInfoList[maxSwitchNum]->parentlinklist[seq1]->getTargetAddress();
                EV << "ATSOverlay::Switch:ppAddress:" << ppAddress << "\n";
                //peer[?]
                TransportAddress pAddress =
                        PeerInfoList[maxSwitchNum]->getAddress();
                EV << "ATSOverlay::Switch:pAddress:" << pAddress << "\n";
                //one of peer[?]'s child which get seq1 from peer[?]
                TransportAddress pcAddress =
                        PeerInfoList[maxSwitchNum]->childlinklist[tag]->getLinkOwnerAddress();//2014-12-17：replace fromPeerInfoList[maxSwitchNum]->getChildAddressByDataSeq(seq1);
                EV << "ATSOverlay::Switch:pcAddress:" << pcAddress << "\n";
                //Msg to peer[?]'s parent to replace peer[?] and be its child to get seq1.
                ATSInsertMessage* insertMsgPPC = new ATSInsertMessage(
                        "insertMsgPPC_2");
                insertMsgPPC->setBeChildNode(true);
                insertMsgPPC->setDataSeq(seq1);
                insertMsgPPC->setSelectedNodeAddress(pAddress);
                insertMsgPPC->setSelectedDataSeq(seq1);

                parentLinkList[seq1]->setTargetAddress(ppAddress);
                parentLinkList[seq1]->setState(ATS_LINK_SELECTED);
                sendATSMessageToUDP(insertMsgPPC, ppAddress);

                //Msg to peer[?] to replace one of its child which get seq1 from peer[?] to get seq2
                ATSInsertMessage* insertMsgPC = new ATSInsertMessage(
                        "insertMsgPC_2");
                insertMsgPC->setBeChildNode(true);
                insertMsgPC->setDataSeq(seq2);
                insertMsgPC->setSelectedNodeAddress(pcAddress);
                insertMsgPC->setSelectedDataSeq(seq1);

                parentLinkList[seq2]->setTargetAddress(pAddress);
                parentLinkList[seq2]->setState(ATS_LINK_SELECTED);
                sendATSMessageToUDP(insertMsgPC, pAddress);

                //Msg to peer[?] to replace its parents to deliver seq1 to peer[?]
                ATSInsertMessage* insertMsgPP = new ATSInsertMessage(
                        "insertMsgPP_2");
                insertMsgPP->setBeChildNode(false);
                insertMsgPP->setDataSeq(seq1);
                insertMsgPP->setSelectedNodeAddress(ppAddress);
                insertMsgPP->setSelectedDataSeq(seq1);

                ATSLink *childLink1 = new ATSLink();
                childLink1->setTargetAddress(pAddress);
                childLink1->setDataSeq(seq1);
                childLink1->setLag(getLagByAddress(pAddress));
                childLink1->setState(ATS_LINK_SELECTED);
                childLinkList.push_back(childLink1);
                freeDegree = outputDegree - childLinkList.size();
                sendATSMessageToUDP(insertMsgPP, pAddress);

                //Msg to one of peer[?]'s child to replace peer[?] to deliver seq1 to this child
                ATSInsertMessage* insertMsgPCP = new ATSInsertMessage(
                        "insertMsgPCP_2");
                insertMsgPCP->setBeChildNode(false);
                insertMsgPCP->setDataSeq(seq1);
                insertMsgPCP->setSelectedNodeAddress(pAddress);
                insertMsgPCP->setSelectedDataSeq(seq1);

                ATSLink *childLink2 = new ATSLink();
                childLink2->setTargetAddress(pcAddress);
                childLink2->setDataSeq(seq1);
                childLink2->setLag(getLagByAddress(pcAddress));
                childLink2->setState(ATS_LINK_SELECTED);
                childLinkList.push_back(childLink2);
                freeDegree = outputDegree - childLinkList.size();
                sendATSMessageToUDP(insertMsgPCP, pcAddress);

                //Updata the selected peer's state
                unsigned int childSeq =
                        PeerInfoList[maxSwitchNum]->getChildIndexByDataSeq(
                                seq1);
                PeerInfoList[maxSwitchNum]->childlinklist[childSeq]->setTargetAddress(
                        thisNode);
                PeerInfoList[maxSwitchNum]->childlinklist[childSeq]->setDataSeq(
                        seq2); //Important!
            } else {
                //如果以上3个方法不行则采取强制insert方式加入组播
                //Msg to peer[?]'s parent and be its child node
                ATSInsertMessage *insertMsgPPC = new ATSInsertMessage(
                        "insertMsgPPC_4");
                insertMsgPPC->setBeChildNode(true);
                insertMsgPPC->setDataSeq(i);
                insertMsgPPC->setSelectedNodeAddress(
                        PeerInfoList[0]->getAddress());
                insertMsgPPC->setSelectedDataSeq(i);

                parentLinkList[i]->setTargetAddress(
                        PeerInfoList[0]->parentlinklist[i]->getTargetAddress());
                parentLinkList[i]->setState(ATS_LINK_SELECTED);
                sendATSMessageToUDP(insertMsgPPC,
                        PeerInfoList[0]->parentlinklist[i]->getTargetAddress());

                //Msg to peer[?] and be its parent node
                ATSInsertMessage *insertMsgPC = new ATSInsertMessage(
                        "insertMsgPC_4");
                insertMsgPC->setBeChildNode(false);
                insertMsgPC->setDataSeq(i);
                insertMsgPC->setSelectedNodeAddress(
                        PeerInfoList[0]->parentlinklist[i]->getTargetAddress());
                insertMsgPC->setSelectedDataSeq(i);

                ATSLink *childLink = new ATSLink();
                childLink->setTargetAddress(PeerInfoList[0]->getAddress());
                childLink->setDataSeq(i);
                childLink->setLag(
                        getLagByAddress(PeerInfoList[0]->getAddress()));
                childLink->setState(ATS_LINK_SELECTED);
                childLinkList.push_back(childLink);
                freeDegree = outputDegree - childLinkList.size();
                sendATSMessageToUDP(insertMsgPC, PeerInfoList[0]->getAddress());

                forceInsertTimes++;
                EV << "forceInsertTimes:" << forceInsertTimes << "\n";
                getParentModule()->getParentModule()->getDisplayString().setTagArg(
                        "i2", 1, "orange");
                getParentModule()->getParentModule()->getDisplayString().setTagArg(
                        "t", 0, "F");
            }
        }
    }
}

//在本节点的PeerInfoList中通过循环比对address取的对应节点的lag
double ATSOverlay::getLagByAddress(TransportAddress address) {
    if (address.isUnspecified()) {				//判断地址是否为空
        return 0;
    } else {				//若address不为空
        for (unsigned int i = 0; i < PeerInfoList.size(); i++) {
            if (PeerInfoList[i]->getAddress() == address) {
                double lag = PeerInfoList[i]->getLag();
                return lag;
            }
        }
        if (address == ServerAddress) {
            // TODO
        }
    }
    return 0;
}

//处理评估反馈消息，将评估反馈的消息存入自己的PeerInfoList中
void ATSOverlay::handleATSJoinEvalResponseMessage(
        ATSJoinEvalResponseMessage *atsJoinEvalResponseMsg) {
    if (nodeState != NodeState_Joining && nodeState != NodeState_Joined) {
        EV << "ATSOverlay::handleATSJoinEvalResponseMessage@Time" << simTime()
                  << "\n";
        EV << "\tdataTimeStamp.size()"
                  << atsJoinEvalResponseMsg->getDataTimeStampArraySize()
                  << "\n";
        ATSPeerInfo* atsPeerInfo = new ATSPeerInfo();
        atsPeerInfo->setAddress(atsJoinEvalResponseMsg->getSourceAddress());
        atsPeerInfo->setFreeResource(atsJoinEvalResponseMsg->getFreeDegree());
        atsPeerInfo->setLag(
                simTime() / SECOND - atsJoinEvalResponseMsg->getSendTime());
        for (unsigned int i = 0;
                i < atsJoinEvalResponseMsg->getDataTimeStampArraySize(); i++) {	//设置peerInfo的各个支流的时间戳
            atsPeerInfo->dataTimeStamp.push_back(
                    atsJoinEvalResponseMsg->getDataTimeStamp(i));
        }
        for (unsigned int i = 0;
                i < atsJoinEvalResponseMsg->getParentAddressArraySize(); i++) {	//设置peerInfo的各个支流的父节点
            ATSLink* atsLink = new ATSLink();
            atsLink->setTargetAddress(
                    atsJoinEvalResponseMsg->getParentAddress(i));
            atsLink->setDataSeq(i);
            atsLink->setLag(atsJoinEvalResponseMsg->getParentlag(i));
            atsPeerInfo->parentlinklist.push_back(atsLink);
        }
        for (unsigned int i = 0;
                i < atsJoinEvalResponseMsg->getChildAddressArraySize(); i++) {//设置peerInfo的各个支流的孩子节点
            ATSLink* atsLink = new ATSLink();
            atsLink->setTargetAddress(
                    atsJoinEvalResponseMsg->getChildAddress(i));
            atsLink->setDataSeq(atsJoinEvalResponseMsg->getChildDataSeq(i));
            atsLink->setLag(atsJoinEvalResponseMsg->getChildlag(i));
            atsPeerInfo->childlinklist.push_back(atsLink);
        }
        for (unsigned int i = 0;
                i < atsJoinEvalResponseMsg->getChildNum_dataSeqArraySize();
                i++) {				//设置peerInfo的各个支流的孩子节点数量
            atsPeerInfo->ChildNum_dataSeq.push_back(
                    atsJoinEvalResponseMsg->getChildNum_dataSeq(i));
        }
        PeerInfoList.push_back(atsPeerInfo);
        //To decide whether starting the join process
        if (PeerInfoList.size() >= infoCollectNum
                || PeerInfoList.size() >= memberNum) {
            startJoinProcess();
            nodeState = NodeState_Joining;
        }
    }
}

void ATSOverlay::handleATSJoinMessage(ATSJoinMessage *atsJoinMsg) {
    if (freeDegree > 0) {
        ATSLink *childLink = new ATSLink();
        childLink->setTargetAddress(atsJoinMsg->getSourceAddress());
        childLink->setDataSeq(atsJoinMsg->getDataSeq());
        childLink->setState(ATS_LINK_CONNECTED);
        childLinkList.push_back(childLink);
        freeDegree = outputDegree - childLinkList.size();

        ATSJoinResponseMessage* atsJoinResponseMsg = new ATSJoinResponseMessage(
                "atsJoinResponseMsg");
        atsJoinResponseMsg->setDataSeq(atsJoinMsg->getDataSeq());
        sendATSMessageToUDP(atsJoinResponseMsg, atsJoinMsg->getSourceAddress());
    } else {
        resourceErrorTimes++;
        getParentModule()->getParentModule()->getDisplayString().setTagArg("i2",
                1, "orange");
    }
}

void ATSOverlay::handleATSJoinResponseMessage(
        ATSJoinResponseMessage *atsJoinResponseMsg) {
    if (parentLinkList[atsJoinResponseMsg->getDataSeq()]->getTargetAddress()
            == atsJoinResponseMsg->getSourceAddress()) {
        parentLinkList[atsJoinResponseMsg->getDataSeq()]->setState(
                ATS_LINK_CONNECTED);
    }
    checkNodeState();
}

void ATSOverlay::checkNodeState() {
    EV << "ATSOverlay::checkNodeState@Time" << simTime() << "\n";
    for (unsigned int i = 0; i < parentLinkList.size(); i++) {
        if (parentLinkList[i]->getState() != ATS_LINK_CONNECTED) {
            EV << "ATSOverlay::check1:" << i << "\n";
            return;
        }
    }
    for (unsigned int i = 0; i < childLinkList.size(); i++) {
        if (childLinkList[i]->getState() != ATS_LINK_CONNECTED) {
            EV << "ATSOverlay::check2:" << i << "\n";
            return;
        }
    }
    endTime = simTime() / SECOND;
    //检查完毕，向服务器发送成功消息
    ATSJoinSuccessMessage* atsJoinSuccessMsg = new ATSJoinSuccessMessage(
            "atsJoinSuccessMsg");
    sendATSMessageToUDP(atsJoinSuccessMsg, ServerAddress);
    nodeState = NodeState_Joined;

//    //向每条支流的父节点发送消息，更新每条支流的节点数量
//    for (int i = 0; i < parentLinkList.size(); i++) {
//        ATSChildNumIncreaseMessage* atsChildNumIncreaseMsg =
//                new ATSChildNumIncreaseMessage("atsChildNumIncreaseMsg");
//        atsChildNumIncreaseMsg->setDataSeq(i);
//        atsChildNumIncreaseMsg->setParentTargetAddress(
//                parentLinkList[i]->getTargetAddress());	//设置目标父节点，主要用来控制到服务器节点停止向上反馈
//        sendATSMessageToUDP(atsChildNumIncreaseMsg,
//                parentLinkList[i]->getTargetAddress());			//将消息发送给自己对应的父节点
//
//    }

    getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 1,
            "white");
}

void ATSOverlay::handleATSChildNumIncreaseMessage(
        ATSChildNumIncreaseMessage* atsChildNumIncreaseMsg)		//增加对应支流的子节点数量
        {
    //判断是否为服务器,若是服务器则停止向上反馈,只操作自身的支流节点数量
    if (atsChildNumIncreaseMsg->getParentTargetAddress() == ServerAddress) {
        ChildNum_dataSeq[atsChildNumIncreaseMsg->getDataSeq()]++;//对应的记录支流数组的项目+1
    } else {				//非服务器节点则继续向上反馈
        //这里从0开始
        ATSChildNumIncreaseMessage* atsChildNumIncreaseMsg_C =
                new ATSChildNumIncreaseMessage("atsChildNumIncreaseMsg_C");
        ChildNum_dataSeq[atsChildNumIncreaseMsg->getDataSeq()]++;
        atsChildNumIncreaseMsg_C->setDataSeq(
                atsChildNumIncreaseMsg->getDataSeq());		//统一设置数据流
        atsChildNumIncreaseMsg_C->setParentTargetAddress(
                parentLinkList[atsChildNumIncreaseMsg->getDataSeq()]->getTargetAddress());//统一设置自身父节点
        // 刷新子节点延迟
        sendATSMessageToUDP(atsChildNumIncreaseMsg_C,
                parentLinkList[atsChildNumIncreaseMsg->getDataSeq()]->getTargetAddress());

    }

}

void ATSOverlay::handleATSInsertMessage(ATSInsertMessage *atsInsertMsg) {
    if (atsInsertMsg->getBeChildNode()) {
        for (unsigned int i = 0; i < childLinkList.size(); i++) {
            if (childLinkList[i]->getDataSeq()
                    == atsInsertMsg->getSelectedDataSeq()
                    && childLinkList[i]->getTargetAddress()
                            == atsInsertMsg->getSelectedNodeAddress()) {
                childLinkList[i]->setDataSeq(atsInsertMsg->getDataSeq());
                //TODO:2014-12-17
                childLinkList[i]->setLag(0);
                childLinkList[i]->setTargetAddress(
                        atsInsertMsg->getSourceAddress());

                ATSInsertResponseMessage* atsInsertResponseMsg =
                        new ATSInsertResponseMessage("atsInsertResponseMsg");
                atsInsertResponseMsg->setBeChildNode(
                        !atsInsertMsg->getBeChildNode());
                atsInsertResponseMsg->setDataSeq(atsInsertMsg->getDataSeq());
                sendATSMessageToUDP(atsInsertResponseMsg,
                        atsInsertMsg->getSourceAddress());
                break;
            }
        }
    } else {
        if (parentLinkList[atsInsertMsg->getSelectedDataSeq()]->getTargetAddress()
                == atsInsertMsg->getSelectedNodeAddress()) {
            parentLinkList[atsInsertMsg->getSelectedDataSeq()]->setTargetAddress(
                    atsInsertMsg->getSourceAddress());

            ATSInsertResponseMessage* atsInsertResponseMsg =
                    new ATSInsertResponseMessage("atsInsertResponseMsg");
            atsInsertResponseMsg->setBeChildNode(
                    !atsInsertMsg->getBeChildNode());
            atsInsertResponseMsg->setDataSeq(atsInsertMsg->getDataSeq());
            sendATSMessageToUDP(atsInsertResponseMsg,
                    atsInsertMsg->getSourceAddress());
        }
    }
}

void ATSOverlay::handleATSInsertResponseMessage(
        ATSInsertResponseMessage *atsInsertResponseMsg) {
    if (atsInsertResponseMsg->getBeChildNode()) {
        for (unsigned int i = 0; i < childLinkList.size(); i++) {
            if (childLinkList[i]->getDataSeq()
                    == atsInsertResponseMsg->getDataSeq()
                    && childLinkList[i]->getTargetAddress()
                            == atsInsertResponseMsg->getSourceAddress()) {
                childLinkList[i]->setState(ATS_LINK_CONNECTED);
                EV << "ATSOverlay::irc\n";
                break;
            }
        }
    } else {
        if (parentLinkList[atsInsertResponseMsg->getDataSeq()]->getTargetAddress()
                == atsInsertResponseMsg->getSourceAddress()) {
            EV << "ATSOverlay::irp\n";
            parentLinkList[atsInsertResponseMsg->getDataSeq()]->setState(
                    ATS_LINK_CONNECTED);
        }
    }
    checkNodeState();
}

void ATSOverlay::handleATSJoinSuccessMessage(
        ATSJoinSuccessMessage *atsJoinSuccessMsg) {
    // update peer info of the src node;
    for (unsigned int i = 0; i < PeerInfoList.size(); i++) {
        if (PeerInfoList[i]->getAddress()
                == atsJoinSuccessMsg->getSourceAddress()) {
            PeerInfoList[i]->setIsJoined(true);
            joinedMemberNum++;
        }
    }
    for (unsigned int i = 0; i < childLinkList.size(); i++) {
        ATSStatisticMessage* atsStatisticMsg = new ATSStatisticMessage(
                "atsStatisticMsg");
        atsStatisticMsg->setCreateTime(simTime() / SECOND);
        atsStatisticMsg->setDataSeq(childLinkList[i]->getDataSeq());
        atsStatisticMsg->setHop(0);
        sendATSMessageToUDP(atsStatisticMsg,
                childLinkList[i]->getTargetAddress());
    }
    if (joinedMemberNum == targetOverlayTerminalNum - 1) {
        ATSMessage* atsMsg = new ATSMessage("atsMsg");
        for (unsigned int i = 0; i < childLinkList.size(); i++) {
            if (0 == childLinkList[i]->getDataSeq()) {
                sendATSMessageToUDP(atsMsg->dup(),
                        childLinkList[i]->getTargetAddress());
            }
        }
    }
}

void ATSOverlay::handleATSStatisticMessage(
        ATSStatisticMessage *atsStatisticMsg) {
    parentLinkList[atsStatisticMsg->getDataSeq()]->setLag(
            simTime() / SECOND - atsStatisticMsg->getSendTime());
    dataTimeStamp[atsStatisticMsg->getDataSeq()] = simTime() / SECOND
            - atsStatisticMsg->getCreateTime();
    dataHops[atsStatisticMsg->getDataSeq()] = atsStatisticMsg->getHop() + 1;

    atsStatisticMsg->setHop(dataHops[atsStatisticMsg->getDataSeq()]);
    getParentModule()->getParentModule()->getDisplayString().setTagArg("t", 0,
            dataTimeStamp[seq] * 1000);
    for (unsigned int i = 0; i < childLinkList.size(); i++) {
        if (atsStatisticMsg->getDataSeq() == childLinkList[i]->getDataSeq()) {
            sendATSMessageToUDP(atsStatisticMsg->dup(),
                    childLinkList[i]->getTargetAddress());
        }
    }
    ATSMessage* atsMsg = new ATSMessage();
    sendATSMessageToUDP(atsMsg, ServerAddress);

}

//更新图形界面函数
void ATSOverlay::updateVisualization() {
    showOverlayNeighborArrow(ServerAddress, true, newArrows[0]);
    deleteOverlayNeighborArrow(ServerAddress);
    bool flag = true;
    unsigned int l = seq;
    for (unsigned int i = 0; i < childLinkList.size(); i++) {
        if (childLinkList[i]->getDataSeq() == l
                && childLinkList[i]->getState() == ATS_LINK_CONNECTED) {
            showOverlayNeighborArrow(childLinkList[i]->getTargetAddress(), flag,
                    newArrows[0]
                    //newArrows[i]
                    );
            flag = false;
        }
    }
}

ATSOverlay::ATSOverlay() {
    // TODO Auto-generated constructor stub

}

ATSOverlay::~ATSOverlay() {
    // TODO Auto-generated destructor stub
    for (unsigned int i = 0; i < parentLinkList.size(); i++) {
        delete parentLinkList[i];
    }
    parentLinkList.clear();
    for (unsigned int i = 0; i < childLinkList.size(); i++) {
        delete childLinkList[i];
    }
    childLinkList.clear();
    for (unsigned int i = 0; i < PeerInfoList.size(); i++) {
        delete PeerInfoList[i];
    }
    PeerInfoList.clear();
    dataTimeStamp.clear();
    dataHops.clear();
}
