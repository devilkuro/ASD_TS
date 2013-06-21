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

#include "ATSOverlay.h"


// Important! This line must be present for each module you extend (see BaseApp)
Define_Module( ATSOverlay);

#define BIGBIT (1 << 24)

static const char *newArrows[] = { "m=m,50,50,50,50;ls=yellow,2",
                                "m=m,50,50,50,50;ls=magenta,3",
                                "m=m,50,50,50,50;ls=red,4",
                                "m=m,50,50,50,50;ls=orange,5",
                                "m=m,50,50,50,50;ls=green,6",
                                "m=m,50,50,50,50;ls=aquamarine,7",
                                "m=m,50,50,50,50;ls=cyan,8",
                                "m=m,50,50,50,50;ls=blue,9",
                                "m=m,50,50,50,50;ls=navy,10",
                                "m=m,50,50,50,50;ls=yellow,11"
                              };
// Overwrite BaseOverlay
void ATSOverlay::initializeOverlay(int stage)
{
    if (stage != MIN_STAGE_OVERLAY) return;

    SECOND = 1.0;
    ServerAddress = TransportAddress(IPAddress(BIGBIT+1),thisNode.getPort());
    nodeAddress = TransportAddress(thisNode.getIp(),thisNode.getPort());

    inputDegree = par("inputDegree");
    outputDegree = par("outputDegree");
    targetOverlayTerminalNum = par("targetOverlayTerminalNum");
    seq = par("seq");
    freeDegree = outputDegree;
    serverFreeDegree = outputDegree;

    memberNum = 0;
    joinedMemberNum = 0;
    readyMenberNum = 0;
    isBusy = false;

    WATCH(isBusy);
    WATCH(joinedMemberNum);
    WATCH(readyMenberNum);

    getParentModule()->getParentModule()->getDisplayString().setTagArg("i", 0, "device/pc_vs");
    getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 0, "block/circle_vs");
    if(nodeAddress!=ServerAddress){
        ATSQueryMessage* atsQueryMsg = new ATSQueryMessage();
        sendATSMessageToUDP(atsQueryMsg,ServerAddress);
    }else{
        getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 1, "yellow");
    }
}

void ATSOverlay::handleUDPMessage(BaseOverlayMessage* msg)
{
    EV<< "ATSOverlay::handleUDPMessage@Time:" <<simTime()<< std::endl;
    if (dynamic_cast<ATSMessage*>(msg) != NULL) {
        ATSMessage *atsMsg = check_and_cast<ATSMessage*>(msg);
        handleATSMessgae(atsMsg);
    } else {
        delete(msg);
    }
}
void ATSOverlay::handleAppMessage(cMessage* msg)
{
    if(msg){
        delete(msg);
    }
}
void ATSOverlay::handleTimerEvent(cMessage* msg)
{
    if(msg){
        delete(msg);
    }
}
void ATSOverlay::finishOverlay() {

	if (nodeState == NodeState_Joined&&nodeAddress!=ServerAddress)
	{
		double maxDataTimeStamp = 0;
		for (unsigned int i = 0; i < dataTimeStamp.size(); i++)
		{
			if (i == 0)
				globalStatistics->recordOutVector(
						"Fanjing:ATS:maxdataTimeStamp0", dataTimeStamp[i]);
			else if (i == 1)
				globalStatistics->recordOutVector(
						"Fanjing:ATS:maxdataTimeStamp1", dataTimeStamp[i]);
			else if (i == 2)
				globalStatistics->recordOutVector(
						"Fanjing:ATS:maxdataTimeStamp2", dataTimeStamp[i]);
			maxDataTimeStamp
					= maxDataTimeStamp > dataTimeStamp[i] ? maxDataTimeStamp
							: dataTimeStamp[i];
		}
		globalStatistics->recordOutVector("Fanjing:ATS:maxdataTimeStamp",
				maxDataTimeStamp);
		globalStatistics->recordOutVector("Fanjing:ATS:JoinTime", endTime
				- startTime);
	}
}

// Private functions
void ATSOverlay::handleATSMessgae(ATSMessage *atsMsg)
{
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
        atsQueryMsg = check_and_cast<ATSQueryMessage*> (atsMsg);
        handleATSQueryMessage(atsQueryMsg);
        break;
    case ATS_QUERY_RESPONSE:
        atsQueryResponseMsg = check_and_cast<ATSQueryResponseMessage*> (atsMsg);
        handleATSQueryResponseMessage(atsQueryResponseMsg);
        break;
    case ATS_JOINEVAL:
        atsJoinEvalMsg = check_and_cast<ATSJoinEvalMessage*> (atsMsg);
        handleATSJoinEvalMessage(atsJoinEvalMsg);
        break;
    case ATS_JOINEVAL_RESPONSE:
        atsJoinEvalResponseMsg
                = check_and_cast<ATSJoinEvalResponseMessage*> (atsMsg);
        handleATSJoinEvalResponseMessage(atsJoinEvalResponseMsg);
        break;
    case ATS_JOIN:
        atsJoinMsg = check_and_cast<ATSJoinMessage*> (atsMsg);
        handleATSJoinMessage(atsJoinMsg);
        break;
    case ATS_JOIN_RESPONSE:
        atsJoinResponseMsg = check_and_cast<ATSJoinResponseMessage*> (atsMsg);
        handleATSJoinResponseMessage(atsJoinResponseMsg);
        break;
    case ATS_INSERT:
        atsInsertMsg = check_and_cast<ATSInsertMessage*> (atsMsg);
        handleATSInsertMessage(atsInsertMsg);
        break;
    case ATS_INSERT_RESPONSE:
        atsInsertResponseMsg
                = check_and_cast<ATSInsertResponseMessage*> (atsMsg);
        handleATSInsertResponseMessage(atsInsertResponseMsg);
        break;
    case ATS_JOIN_SUCCESS:
        atsJoinSuccessMsg = check_and_cast<ATSJoinSuccessMessage*> (atsMsg);
        handleATSJoinSuccessMessage(atsJoinSuccessMsg);
        break;
    case ATS_STATISTIC:
        atsStatisticMsg = check_and_cast<ATSStatisticMessage*> (atsMsg);
        handleATSStatisticMessage( atsStatisticMsg);
        break;
    default:
        EV<< "ATSOverlay::handleATSMessage@Time" <<simTime()<<"\n"<<"{\tError:unKnown Message Type.}\n";
        break;
    }
    if (atsMsg) {
        delete (atsMsg);
    }
}

void ATSOverlay::handleATSQueryMessage(ATSQueryMessage *atsQueryMsg)
{
    EV<< "ATSOverlay::handleATSQueryMessage@Time" <<simTime()<<"\n";
    ATSPeerInfo* atsPeerInfo = new ATSPeerInfo();
    atsPeerInfo->setAddress(atsQueryMsg->getSourceAddress());
    atsPeerInfo->setIsJoined(false);
    PeerInfoList.push_back(atsPeerInfo);
    if(!isBusy){
        sendATSQueryResponseMessage(atsQueryMsg->getSourceAddress());
    }
}

void ATSOverlay::initializeATSMessage(ATSMessage* atsMsg){
    atsMsg->setSourceAddress(thisNode);
    atsMsg->setSendTime(simTime()/SECOND);
}
unsigned int ATSOverlay::calculateATSMessageBitLength(ATSMessage* atsMsg){

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

    unsigned int result = 0;
    switch (atsMsg->getCommand()) {
    case ATS_NULL:
        result = ATSMESSAGE_L(atsMsg);
        break;
    case ATS_QUERY:
        atsQueryMsg = check_and_cast<ATSQueryMessage*> (atsMsg);
        result = ATSQUERYMESSAGE_L(atsQueryMsg);
        break;
    case ATS_QUERY_RESPONSE:
        atsQueryResponseMsg = check_and_cast<ATSQueryResponseMessage*> (atsMsg);
        result = ATSQUERYRESPONSEMESSAGE_L(atsQueryResponseMsg);
        break;
    case ATS_JOINEVAL:
        atsJoinEvalMsg = check_and_cast<ATSJoinEvalMessage*> (atsMsg);
        result = ATSJOINEVALMESSAGE_L(atsJoinEvalMsg);
        break;
    case ATS_JOINEVAL_RESPONSE:
        atsJoinEvalResponseMsg
                = check_and_cast<ATSJoinEvalResponseMessage*> (atsMsg);
        result = ATSJOINEVALRESPONSEMESSAGE_L(atsJoinEvalResponseMsg);
        break;
    case ATS_JOIN:
        atsJoinMsg = check_and_cast<ATSJoinMessage*> (atsMsg);
        result = ATSJOINMESSAGE_L(atsJoinMsg);
        break;
    case ATS_JOIN_RESPONSE:
        atsJoinResponseMsg = check_and_cast<ATSJoinResponseMessage*> (atsMsg);
        result = ATSJOINRESPONSEMESSAGE_L(atsJoinResponseMsg);
        break;
    case ATS_INSERT:
        atsInsertMsg = check_and_cast<ATSInsertMessage*> (atsMsg);
        result = ATSINSERTMESSAGE_L(atsInsertMsg);
        break;
    case ATS_INSERT_RESPONSE:
        atsInsertResponseMsg
                = check_and_cast<ATSInsertResponseMessage*> (atsMsg);
        result = ATSINSERTRESPONSEMESSAGE_L(atsInsertResponseMsg);
        break;
    case ATS_JOIN_SUCCESS:
        atsJoinSuccessMsg = check_and_cast<ATSJoinSuccessMessage*> (atsMsg);
        result = ATSJOINSUCCESSMESSAGE_L(atsJoinSuccessMsg);
        break;
    case ATS_STATISTIC:
        atsStatisticMsg = check_and_cast<ATSStatisticMessage*> (atsMsg);
        result = ATSSTATISTICMESSAGE_L(atsStatisticMsg);
        break;
    default:
        EV<< "ATSOverlay::setATSMessageBitLength@Time" <<simTime()<<"\n"<<"{\tError:unKnown Message Type.}\n";
        result = 0;
        break;
    }
    return result;
}
void ATSOverlay::setATSMessageBitLength(ATSMessage* atsMsg)
{
    atsMsg->setBitLength(calculateATSMessageBitLength(atsMsg));
}
//Send ATSMessage to certain Address with sourceAddress and sendTime
void ATSOverlay::sendATSMessageToUDP(ATSMessage* atsMsg,TransportAddress address){

    initializeATSMessage(atsMsg);
    setATSMessageBitLength(atsMsg);
    sendMessageToUDP(address,atsMsg);
}

//Send ATSQueryResponseMessage to certain Address
void ATSOverlay::sendATSQueryResponseMessage(TransportAddress address){
    isBusy=true;
    ATSQueryResponseMessage* atsQueryResponseMsg =new ATSQueryResponseMessage();
    int mSize = 0;
    for(unsigned int i=0;i<PeerInfoList.size();i++){
        if(PeerInfoList[i]->getIsJoined())
            mSize++;
    }
    atsQueryResponseMsg->setMemberAddressArraySize(mSize);
    for(unsigned int i=0,j=0;i<PeerInfoList.size();i++){
        if(PeerInfoList[i]->getIsJoined()){
            atsQueryResponseMsg->setMemberAddress(j,PeerInfoList[i]->getAddress());
            j++;
        }
    }
    atsQueryResponseMsg->setFreeDegree(freeDegree);
    sendATSMessageToUDP(atsQueryResponseMsg,address);
}

void ATSOverlay::handleATSQueryResponseMessage(ATSQueryResponseMessage *atsQueryResponseMsg)
{
    startTime = simTime()/SECOND-2*(simTime()/SECOND - atsQueryResponseMsg->getSendTime());
    serverFreeDegree = atsQueryResponseMsg->getFreeDegree();
    if(inputDegree<=serverFreeDegree){
        startJoinProcess();
    }else{
        memberNum = atsQueryResponseMsg->getMemberAddressArraySize();
        for(unsigned int i=0;i<atsQueryResponseMsg->getMemberAddressArraySize();i++){
            ATSJoinEvalMessage* atsJoinEvalMsg = new ATSJoinEvalMessage();
            sendATSMessageToUDP(atsJoinEvalMsg,atsQueryResponseMsg->getMemberAddress(i));
        }
    }
}

void ATSOverlay::handleATSJoinEvalMessage(ATSJoinEvalMessage *atsJoinEvalMsg)
{
    EV<< "ATSOverlay::handleATSJoinEvalMessage@Time" <<simTime()<<"\n";
    EV<< "\tdataTimeStamp.size()" <<dataTimeStamp.size()<<"\n";
    ATSJoinEvalResponseMessage* atsJoinEvalResponseMsg = new ATSJoinEvalResponseMessage();
    atsJoinEvalResponseMsg->setFreeDegree(freeDegree);
    atsJoinEvalResponseMsg->setDataTimeStampArraySize(dataTimeStamp.size());
    for(unsigned int i=0;i<dataTimeStamp.size();i++){
        atsJoinEvalResponseMsg->setDataTimeStamp(i,dataTimeStamp[i]);
    }
    atsJoinEvalResponseMsg->setParentAddressArraySize(parentLinkList.size());
    for(unsigned int i=0;i<parentLinkList.size();i++){
        atsJoinEvalResponseMsg->setParentAddress(i,parentLinkList[i]->getTargetAddress());
    }
    atsJoinEvalResponseMsg->setChildAddressArraySize(childLinkList.size());
    atsJoinEvalResponseMsg->setChildDataSeqArraySize(childLinkList.size());
    for(unsigned int i=0;i<childLinkList.size();i++){
        atsJoinEvalResponseMsg->setChildAddress(i,childLinkList[i]->getTargetAddress());
        atsJoinEvalResponseMsg->setChildDataSeq(i,childLinkList[i]->getDataSeq());
    }
    sendATSMessageToUDP(atsJoinEvalResponseMsg,atsJoinEvalMsg->getSourceAddress());
}

void ATSOverlay::startJoinProcess(){
    EV<< "ATSOverlay::startJoinProcess@Time" <<simTime()<<"\n";
    for(unsigned int i = 0;i<inputDegree;i++){
        ATSLink *atsLink = new ATSLink();
        atsLink->setDataSeq(i);
        atsLink->setState(ATS_LINK_INIT);
        parentLinkList.push_back(atsLink);
        double timeStamp = 0;
        dataTimeStamp.push_back(timeStamp);
    }
    EV<< "\tdataTimeStamp.size()" <<dataTimeStamp.size()<<"\n";
    for(unsigned int i = 0;i<inputDegree;i++){
        //If the link has already selected, break out.
        if(parentLinkList[i]->getState()!=ATS_LINK_INIT){
            continue;
        }
        //Use server free resource
        if(serverFreeDegree>0){
            EV<< "ATSOverlay::Server\n";
            ATSJoinMessage* atsJoinMsg = new ATSJoinMessage();
            atsJoinMsg->setDataSeq(i);
            parentLinkList[i]->setTargetAddress(ServerAddress);
            parentLinkList[i]->setState(ATS_LINK_SELECTED);
            serverFreeDegree--;
            sendATSMessageToUDP(atsJoinMsg,ServerAddress);
        }
        //Use peer nodes resource
        else{
            double maxJoinScore = 0;
            double maxInsertScore = 0;
            double maxSwitchScore = 0;
            unsigned int maxJoinNum = 0;
            unsigned int maxInsertNum = 0;
            unsigned int maxSwitchNum = 0;
            unsigned int maxSwitchSeq1 = 0;
            unsigned int maxSwitchSeq2 = 0;
            for(unsigned int j=0;j<PeerInfoList.size();j++){
                double joinScore = PeerInfoList[j]->getJoinScoreByDataSeq(i);
                if(joinScore>maxJoinScore){
                    maxJoinScore=joinScore;
                    maxJoinNum=j;
                }
                double insertScore = PeerInfoList[j]->getInsertScoreByDataSeq(i);
                if(insertScore>maxInsertScore){
                    maxInsertScore=insertScore;
                    maxInsertNum=j;
                }
                double switchScore = 0;
                unsigned int switchSeq1 = 0;
                unsigned int switchSeq2 = 0;
                for(unsigned int k=i+1;k<inputDegree;k++){
                    if (parentLinkList[k]->getState() == ATS_LINK_INIT) {
                        double tempSwitchScore =
                                PeerInfoList[j]->getSwitchScoreByDataSeq(i, k);
                        if (tempSwitchScore > switchScore) {
                            switchScore = tempSwitchScore;
                            switchSeq1 = i;
                            switchSeq2 = k;
                        }
                    }
                }
                if(switchScore>maxSwitchScore){
                    maxSwitchScore=switchScore;
                    maxSwitchNum=j;
                    maxSwitchSeq1=switchSeq1;
                    maxSwitchSeq2=switchSeq2;
                }
            }
            if(maxJoinScore>0&&maxJoinScore>=maxInsertScore&&maxJoinScore>=maxSwitchScore){
                EV<< "ATSOverlay::Join\n";
                ATSJoinMessage* atsJoinMsg = new ATSJoinMessage();
                atsJoinMsg->setDataSeq(i);
                parentLinkList[i]->setTargetAddress(PeerInfoList[maxJoinNum]->getAddress());
                parentLinkList[i]->setState(ATS_LINK_SELECTED);
                PeerInfoList[maxJoinNum]->setFreeResource(PeerInfoList[maxJoinNum]->getFreeResource()-1);
                sendATSMessageToUDP(atsJoinMsg,PeerInfoList[maxJoinNum]->getAddress());
            }else if(maxInsertScore>0&&maxInsertScore>=maxJoinScore&&maxInsertScore>=maxSwitchScore){
                EV<< "ATSOverlay::Insert\n";
                //Msg to peer[?]'s parent and be its child node
                ATSInsertMessage *insertMsgPPC = new ATSInsertMessage();
                insertMsgPPC->setBeChildNode(true);
                insertMsgPPC->setDataSeq(i);
                insertMsgPPC->setSelectedNodeAddress(PeerInfoList[maxInsertNum]->getAddress());
                insertMsgPPC->setSelectedDataSeq(i);

                parentLinkList[i]->setTargetAddress(PeerInfoList[maxInsertNum]->parentlinklist[i]->getTargetAddress());
                parentLinkList[i]->setState(ATS_LINK_SELECTED);
                sendATSMessageToUDP(insertMsgPPC,PeerInfoList[maxInsertNum]->parentlinklist[i]->getTargetAddress());

                //Msg to peer[?] and be its parent node
                ATSInsertMessage *insertMsgPC = new ATSInsertMessage();
                insertMsgPC->setBeChildNode(false);
                insertMsgPC->setDataSeq(i);
                insertMsgPC->setSelectedNodeAddress(PeerInfoList[maxInsertNum]->parentlinklist[i]->getTargetAddress());
                insertMsgPC->setSelectedDataSeq(i);

                ATSLink *childLink = new ATSLink();
                childLink->setTargetAddress(PeerInfoList[maxInsertNum]->getAddress());
                childLink->setDataSeq(i);
                childLink->setState(ATS_LINK_SELECTED);
                childLinkList.push_back(childLink);
                freeDegree=outputDegree-childLinkList.size();
                sendATSMessageToUDP(insertMsgPC,PeerInfoList[maxInsertNum]->getAddress());
            }else if(maxSwitchScore>0&&maxSwitchScore>=maxJoinScore&&maxSwitchScore>=maxInsertScore){
                EV<< "ATSOverlay::Switch\n";
                //Replace peer[?] to deliver seq1 from peer[?]'s parent node to peer[?] and one of its child, and get seq2 from peer[?].
                //Since peer[?] should continue to deliver the higher ratio seq, so we should confirm seq1 is the low ratio seq and seq2 is the higher one.
                if(PeerInfoList[maxSwitchNum]->getDataRatioByDataSeq(maxSwitchSeq1)>PeerInfoList[maxSwitchNum]->getDataRatioByDataSeq(maxSwitchSeq2)){
//                    maxSwitchSeq1 += maxSwitchSeq2;
//                    maxSwitchSeq2 = maxSwitchSeq1 - maxSwitchSeq2;
//                    maxSwitchSeq1 = maxSwitchSeq1 - maxSwitchSeq2;
                    unsigned temp = maxSwitchSeq1;
                    maxSwitchSeq1 = maxSwitchSeq2;
                    maxSwitchSeq2 = temp;
                }
                unsigned seq1 = maxSwitchSeq1;
                unsigned seq2 = maxSwitchSeq2;
                //peer[?]'s parent which deliver seq1 to peer[?]
                TransportAddress ppAddress = PeerInfoList[maxSwitchNum]->parentlinklist[seq1]->getTargetAddress();
                EV<< "ATSOverlay::Switch:ppAddress:"<<ppAddress<<"\n";
                //peer[?]
                TransportAddress pAddress = PeerInfoList[maxSwitchNum]->getAddress();
                EV<< "ATSOverlay::Switch:pAddress:"<<pAddress<<"\n";
                //one of peer[?]'s child which get seq1 from peer[?]
                TransportAddress pcAddress = PeerInfoList[maxSwitchNum]->getChildAddressByDataSeq(seq1);
                EV<< "ATSOverlay::Switch:pcAddress:"<<pcAddress<<"\n";
                //Msg to peer[?]'s parent to replace peer[?] and be its child to get seq1.
                ATSInsertMessage* insertMsgPPC = new ATSInsertMessage();
                insertMsgPPC->setBeChildNode(true);
                insertMsgPPC->setDataSeq(seq1);
                insertMsgPPC->setSelectedNodeAddress(pAddress);
                insertMsgPPC->setSelectedDataSeq(seq1);

                parentLinkList[seq1]->setTargetAddress(ppAddress);
                parentLinkList[seq1]->setState(ATS_LINK_SELECTED);
                sendATSMessageToUDP(insertMsgPPC,ppAddress);

                //Msg to peer[?] to replace one of its child which get seq1 from peer[?] to get seq2
                ATSInsertMessage* insertMsgPC = new ATSInsertMessage();
                insertMsgPC->setBeChildNode(true);
                insertMsgPC->setDataSeq(seq2);
                insertMsgPC->setSelectedNodeAddress(pcAddress);
                insertMsgPC->setSelectedDataSeq(seq1);

                parentLinkList[seq2]->setTargetAddress(pAddress);
                parentLinkList[seq2]->setState(ATS_LINK_SELECTED);
                sendATSMessageToUDP(insertMsgPC,pAddress);

                //Msg to peer[?] to replace its parents to deliver seq1 to peer[?]
                ATSInsertMessage* insertMsgPP = new ATSInsertMessage();
                insertMsgPP->setBeChildNode(false);
                insertMsgPP->setDataSeq(seq1);
                insertMsgPP->setSelectedNodeAddress(ppAddress);
                insertMsgPP->setSelectedDataSeq(seq1);

                ATSLink *childLink1 = new ATSLink();
                childLink1->setTargetAddress(pAddress);
                childLink1->setDataSeq(seq1);
                childLink1->setState(ATS_LINK_SELECTED);
                childLinkList.push_back(childLink1);
                freeDegree=outputDegree-childLinkList.size();
                sendATSMessageToUDP(insertMsgPP,pAddress);

                //Msg to one of peer[?]'s child to replace peer[?] to deliver seq1 to this child
                ATSInsertMessage* insertMsgPCP = new ATSInsertMessage();
                insertMsgPCP->setBeChildNode(false);
                insertMsgPCP->setDataSeq(seq1);
                insertMsgPCP->setSelectedNodeAddress(pAddress);
                insertMsgPCP->setSelectedDataSeq(seq1);

                ATSLink *childLink2 = new ATSLink();
                childLink2->setTargetAddress(pcAddress);
                childLink2->setDataSeq(seq1);
                childLink2->setState(ATS_LINK_SELECTED);
                childLinkList.push_back(childLink2);
                freeDegree=outputDegree-childLinkList.size();
                sendATSMessageToUDP(insertMsgPCP,pcAddress);

                //Updata the selected peer's state
                unsigned int childSeq = PeerInfoList[maxSwitchNum]->getChildIndexByDataSeq(seq1);
                PeerInfoList[maxSwitchNum]->childlinklist[childSeq]->setTargetAddress(thisNode);
                PeerInfoList[maxSwitchNum]->childlinklist[childSeq]->setDataSeq(seq2);	//Important!
            }else{
                //Msg to peer[?]'s parent and be its child node
                ATSInsertMessage *insertMsgPPC = new ATSInsertMessage();
                insertMsgPPC->setBeChildNode(true);
                insertMsgPPC->setDataSeq(i);
                insertMsgPPC->setSelectedNodeAddress(PeerInfoList[0]->getAddress());
                insertMsgPPC->setSelectedDataSeq(i);

                parentLinkList[i]->setTargetAddress(PeerInfoList[0]->parentlinklist[i]->getTargetAddress());
                parentLinkList[i]->setState(ATS_LINK_SELECTED);
                sendATSMessageToUDP(insertMsgPPC,PeerInfoList[0]->parentlinklist[i]->getTargetAddress());

                //Msg to peer[?] and be its parent node
                ATSInsertMessage *insertMsgPC = new ATSInsertMessage();
                insertMsgPC->setBeChildNode(false);
                insertMsgPC->setDataSeq(i);
                insertMsgPC->setSelectedNodeAddress(PeerInfoList[0]->parentlinklist[i]->getTargetAddress());
                insertMsgPC->setSelectedDataSeq(i);

                ATSLink *childLink = new ATSLink();
                childLink->setTargetAddress(PeerInfoList[0]->getAddress());
                childLink->setDataSeq(i);
                childLink->setState(ATS_LINK_SELECTED);
                childLinkList.push_back(childLink);
                freeDegree=outputDegree-childLinkList.size();
                sendATSMessageToUDP(insertMsgPC,PeerInfoList[0]->getAddress());

                forceInsertTimes++;
                EV<< "forceInsertTimes:" <<forceInsertTimes<<"\n";
                getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 1, "orange");
                getParentModule()->getParentModule()->getDisplayString().setTagArg("t",0,"F");
            }
        }
    }
}
void ATSOverlay::handleATSJoinEvalResponseMessage(ATSJoinEvalResponseMessage *atsJoinEvalResponseMsg)
{
    if (nodeState != NodeState_Joining&&nodeState!=NodeState_Joined) {
        EV<< "ATSOverlay::handleATSJoinEvalResponseMessage@Time" <<simTime()<<"\n";
        EV<< "\tdataTimeStamp.size()" <<atsJoinEvalResponseMsg->getDataTimeStampArraySize()<<"\n";
        ATSPeerInfo* atsPeerInfo = new ATSPeerInfo();
        atsPeerInfo->setAddress(atsJoinEvalResponseMsg->getSourceAddress());
        atsPeerInfo->setFreeResource(atsJoinEvalResponseMsg->getFreeDegree());
        atsPeerInfo->setLag(simTime()/SECOND-atsJoinEvalResponseMsg->getSendTime());
        for(unsigned int i=0;i<atsJoinEvalResponseMsg->getDataTimeStampArraySize();i++) {
            atsPeerInfo->dataTimeStamp.push_back(atsJoinEvalResponseMsg->getDataTimeStamp(i));
        }
        for(unsigned int i=0;i<atsJoinEvalResponseMsg->getParentAddressArraySize();i++) {
            ATSLink* atsLink = new ATSLink();
            atsLink->setTargetAddress(atsJoinEvalResponseMsg->getParentAddress(i));
            atsLink->setDataSeq(i);
            atsPeerInfo->parentlinklist.push_back(atsLink);
        }
        for(unsigned int i=0;i<atsJoinEvalResponseMsg->getChildAddressArraySize();i++) {
            ATSLink* atsLink = new ATSLink();
            atsLink->setTargetAddress(atsJoinEvalResponseMsg->getChildAddress(i));
            atsLink->setDataSeq(atsJoinEvalResponseMsg->getChildDataSeq(i));
            atsPeerInfo->childlinklist.push_back(atsLink);
        }
        PeerInfoList.push_back(atsPeerInfo);
        //To decide whether starting the join process
        if(PeerInfoList.size()>=20||PeerInfoList.size()>=memberNum) {
            startJoinProcess();
            nodeState=NodeState_Joining;
        }
    }
}

void ATSOverlay::handleATSJoinMessage(ATSJoinMessage *atsJoinMsg)
{
    if(freeDegree>0){
        ATSLink *childLink = new ATSLink();
        childLink->setTargetAddress(atsJoinMsg->getSourceAddress());
        childLink->setDataSeq(atsJoinMsg->getDataSeq());
        childLink->setState(ATS_LINK_CONNECTED);
        childLinkList.push_back(childLink);
        freeDegree=outputDegree-childLinkList.size();

        ATSJoinResponseMessage* atsJoinResponseMsg = new ATSJoinResponseMessage();
        atsJoinResponseMsg->setDataSeq(atsJoinMsg->getDataSeq());
        sendATSMessageToUDP(atsJoinResponseMsg,atsJoinMsg->getSourceAddress());
    }else{
        resourceErrorTimes++;
        getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 1, "orange");
    }
}

void ATSOverlay::handleATSJoinResponseMessage(ATSJoinResponseMessage *atsJoinResponseMsg)
{
    if(parentLinkList[atsJoinResponseMsg->getDataSeq()]->getTargetAddress()==atsJoinResponseMsg->getSourceAddress()){
        parentLinkList[atsJoinResponseMsg->getDataSeq()]->setState(ATS_LINK_CONNECTED);
    }
    checkNodeState();
}

void ATSOverlay::checkNodeState(){
    EV<< "ATSOverlay::checkNodeState@Time" <<simTime()<<"\n";
    for (unsigned int i = 0; i < parentLinkList.size(); i++) {
        if (parentLinkList[i]->getState() != ATS_LINK_CONNECTED) {
            EV<< "ATSOverlay::check1:"<<i<<"\n";
            return;
        }
    }
    for (unsigned int i = 0; i < childLinkList.size(); i++) {
        if (childLinkList[i]->getState() != ATS_LINK_CONNECTED) {
            EV<< "ATSOverlay::check2:"<<i<<"\n";
            return;
        }
    }
    endTime = simTime()/SECOND;
    ATSJoinSuccessMessage* atsJoinSuccessMsg = new ATSJoinSuccessMessage();
    sendATSMessageToUDP(atsJoinSuccessMsg, ServerAddress);
    nodeState = NodeState_Joined;
    getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 1, "green");
}

void ATSOverlay::handleATSInsertMessage(ATSInsertMessage *atsInsertMsg)
{
    if(atsInsertMsg->getBeChildNode()){
        for(unsigned int i=0;i<childLinkList.size();i++){
            if(childLinkList[i]->getDataSeq()==atsInsertMsg->getSelectedDataSeq()&&childLinkList[i]->getTargetAddress()==atsInsertMsg->getSelectedNodeAddress()){
                childLinkList[i]->setDataSeq(atsInsertMsg->getDataSeq());
                childLinkList[i]->setTargetAddress(atsInsertMsg->getSourceAddress());

                ATSInsertResponseMessage* atsInsertResponseMsg = new ATSInsertResponseMessage();
                atsInsertResponseMsg->setBeChildNode(!atsInsertMsg->getBeChildNode());
                atsInsertResponseMsg->setDataSeq(atsInsertMsg->getDataSeq());
                sendATSMessageToUDP(atsInsertResponseMsg,atsInsertMsg->getSourceAddress());
                break;
            }
        }
    }else{
        if(parentLinkList[atsInsertMsg->getSelectedDataSeq()]->getTargetAddress()==atsInsertMsg->getSelectedNodeAddress()){
            parentLinkList[atsInsertMsg->getSelectedDataSeq()]->setTargetAddress(atsInsertMsg->getSourceAddress());

            ATSInsertResponseMessage* atsInsertResponseMsg = new ATSInsertResponseMessage();
            atsInsertResponseMsg->setBeChildNode(!atsInsertMsg->getBeChildNode());
            atsInsertResponseMsg->setDataSeq(atsInsertMsg->getDataSeq());
            sendATSMessageToUDP(atsInsertResponseMsg,atsInsertMsg->getSourceAddress());
        }
    }
}

void ATSOverlay::handleATSInsertResponseMessage(ATSInsertResponseMessage *atsInsertResponseMsg)
{
    if(atsInsertResponseMsg->getBeChildNode()){
        for(unsigned int i=0;i<childLinkList.size();i++){
            if(childLinkList[i]->getDataSeq()==atsInsertResponseMsg->getDataSeq()&&childLinkList[i]->getTargetAddress()==atsInsertResponseMsg->getSourceAddress()){
                childLinkList[i]->setState(ATS_LINK_CONNECTED);
                EV<< "ATSOverlay::irc\n";
                break;
            }
        }
    }else{
        if(parentLinkList[atsInsertResponseMsg->getDataSeq()]->getTargetAddress()==atsInsertResponseMsg->getSourceAddress()){
            EV<< "ATSOverlay::irp\n";
            parentLinkList[atsInsertResponseMsg->getDataSeq()]->setState(ATS_LINK_CONNECTED);
        }
    }
    checkNodeState();
}

void ATSOverlay::handleATSJoinSuccessMessage(ATSJoinSuccessMessage *atsJoinSuccessMsg)
{
    for(unsigned int i=0;i<PeerInfoList.size();i++){
        if(PeerInfoList[i]->getAddress()==atsJoinSuccessMsg->getSourceAddress()){
            PeerInfoList[i]->setIsJoined(true);
            joinedMemberNum++;
        }
    }
    for(unsigned int i=0;i<childLinkList.size();i++){
        ATSStatisticMessage* atsStatisticMsg = new ATSStatisticMessage();
        atsStatisticMsg->setCreateTime(simTime()/SECOND);
        atsStatisticMsg->setDataSeq(childLinkList[i]->getDataSeq());
        atsStatisticMsg->setHop(0);
        sendATSMessageToUDP(atsStatisticMsg,childLinkList[i]->getTargetAddress());
    }
    if(joinedMemberNum==targetOverlayTerminalNum-1){
        ATSMessage* atsMsg = new ATSMessage();
        for (unsigned int i = 0; i < childLinkList.size(); i++) {
            if (0 == childLinkList[i]->getDataSeq()) {
                sendATSMessageToUDP(atsMsg->dup(),
                                    childLinkList[i]->getTargetAddress());
            }
        }

    }
}

void ATSOverlay::handleATSStatisticMessage(ATSStatisticMessage *atsStatisticMsg)
{
    parentLinkList[atsStatisticMsg->getDataSeq()]->setLag(simTime()/SECOND-atsStatisticMsg->getSendTime());
    dataTimeStamp[atsStatisticMsg->getDataSeq()]=simTime()/SECOND-atsStatisticMsg->getCreateTime();

    getParentModule()->getParentModule()->getDisplayString().setTagArg("t",0,dataTimeStamp[seq]*1000);
    for(unsigned int i=0;i<childLinkList.size();i++){
        if(atsStatisticMsg->getDataSeq()==childLinkList[i]->getDataSeq()){
            sendATSMessageToUDP(atsStatisticMsg->dup(),childLinkList[i]->getTargetAddress());
        }
    }
    ATSMessage* atsMsg = new ATSMessage();
    sendATSMessageToUDP(atsMsg,ServerAddress);

}

void ATSOverlay::updateVisualization(){
    showOverlayNeighborArrow(ServerAddress,true,newArrows[0]);
    deleteOverlayNeighborArrow(ServerAddress);
    bool flag=true;
    unsigned int l=seq;
    for(unsigned int i = 0;i<childLinkList.size();i++){
        if(childLinkList[i]->getDataSeq()==l&&childLinkList[i]->getState()==ATS_LINK_CONNECTED){
            showOverlayNeighborArrow(childLinkList[i]->getTargetAddress(),flag,newArrows[0]);
            flag=false;
        }
    }
}


ATSOverlay::ATSOverlay()
{
    // TODO Auto-generated constructor stub

}

ATSOverlay::~ATSOverlay()
{
    // TODO Auto-generated destructor stub
    for(unsigned int i=0;i<parentLinkList.size();i++){
        delete parentLinkList[i];
    }
    parentLinkList.clear();
    for(unsigned int i=0;i<childLinkList.size();i++){
        delete childLinkList[i];
    }
    childLinkList.clear();
    for(unsigned int i=0;i<PeerInfoList.size();i++){
        delete PeerInfoList[i];
    }
    PeerInfoList.clear();
    dataTimeStamp.clear();
}
