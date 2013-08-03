
#include <iostream>
#include <string>
#include <UnderlayConfigurator.h>
#include <GlobalStatistics.h>
#include "NewOverlay.h"

// Important! This line must be present for each module you extend (see BaseApp)
Define_Module( NewOverlay);

#define BIGBIT (1 << 24)
const char *newArrows[] = { "m=m,50,50,50,50;ls=orange,2",
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
const char *newNumStr[] = {"0","1","2","3","4","5","6","7","8","9","10"};
void NewOverlay::initializeOverlay(int stage)
{
    if (stage != MIN_STAGE_OVERLAY) return;

    numOfLayers = par("numOfLayers");
    k = par("k");
    terminalNum = par("terminalNum");
    peerRatio = par("peerRatio");
    in = 0;

    myKey = thisNode.getIp().get4().getInt() & ~BIGBIT;
    visualizationTimer = new cMessage("Visualization Timer");
    scheduleAt(simTime() + 15, visualizationTimer);

    nodeAddress = TransportAddress(thisNode.getIp(),thisNode.getPort());
    serverNode = TransportAddress(IPAddress(BIGBIT+1),thisNode.getPort());

    getParentModule()->getParentModule()->getDisplayString().setTagArg("i", 0, "device/pc_vs");
    getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 0, "block/circle_s");
    if(serverNode == nodeAddress){
        nodeType = ServerNode;
        getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 1, "yellow");
    }else{
        nodeType = PeerNode;
        joinTimer = new cMessage("Join Timer");
        scheduleAt(simTime() + terminalNum, joinTimer);
    }
    dataTimeStamp.clear();
    for(unsigned int i=0;i<numOfLayers;i++){

        dataTimeStamp.push_back(0);
        parentList.push_back(nodeAddress);
        parentStateList.push_back(Link_Init);

        //Statistics
        jumpNum.push_back(0);
    }
    freeDegree = k;
    queryTime = 0;
    joinTime = 0;
    joinSuccessTime = 0;
    nodeState = NodeState_Init;


    EV << getParentModule()->getParentModule()->getDisplayString() << std::endl;
}


void NewOverlay::handleTimerEvent(cMessage *msg)
{
    if (msg == joinTimer) {
        // reschedule the timer
        scheduleAt(simTime() + terminalNum, joinTimer);

        // if the simulator is still busy creating the network, let's wait a bit longer
        if (underlayConfigurator->isInInitPhase()) return;
        if (nodeType == ServerNode) {
            EV<< "NewOverlay::Error - ServerNode Receives a Join Timer Messge." <<std::endl;
            cancelAndDelete(joinTimer);
            return;
        }
        NewQueryMessage *msg = new NewQueryMessage();
        msg->setCommand(NEW_QUERY);
        msg->setSrcNode(nodeAddress);
        msg->setSentTime(simTime());

        msg->setBitLength(NEWQUERYMESSAGE_L(msg));
        sendMessageToUDP(serverNode,msg);
        queryTime = simTime();
        globalStatistics->recordOutVector("Fanjing:New::queryTime:",myKey);
        EV << "NewOverlay::Sending 'QueryMessage' to ServerNode:" << serverNode.getIp().get4() << std::endl;

        nodeState = NodeState_Query;

        globalStatistics->recordOutVector("Fanjing:New::joinTime: ",myKey);
        cancelAndDelete(joinTimer);
    }else if(msg == visualizationTimer){
        if(nodeState == NodeState_Joined||nodeType == ServerNode) {
            updateVisualization();
        }
        scheduleAt(simTime() + 5, visualizationTimer);
    }
}
void NewOverlay::handleUDPMessage(BaseOverlayMessage *msg)
{
    EV<< "NewOverlay::handleUDPMessage@Time:" <<simTime()<< std::endl;
    if (dynamic_cast<NewMessage*>(msg) != NULL) {
        NewMessage *newMsg = check_and_cast<NewMessage*>(msg);

        switch(newMsg->getCommand()) {
            NewQueryMessage *queryMsg;
            NewQueryResponseMessage *queryResponseMsg;
            NewJoinEvalMessage *joinEvalMsg;
            NewJoinEvalResponseMessage *joinEvalResponseMsg;
            NewJoinMessage *joinMsg;
            NewJoinResponseMessage *joinResponseMsg;
            NewInsertQueryMessage *insertQueryMsg;
            NewInsertQueryResponseMessage *insertQueryResponseMsg;
            NewInsertEvalMessage *insertEvalMsg;
            NewInsertEvalResponseMessage *insertEvalResponseMsg;
            NewInsertMessage *insertMsg;
            NewInsertResponseMessage *insertResponseMsg;
            NewJoinSuccessMessage *joinSuccessMsg;
            NewStatisticMessage *statisticMsg;

            case NEW_QUERY:
            queryMsg = check_and_cast<NewQueryMessage*>(newMsg);
            handleNewQueryMessage(queryMsg);
            break;
            case NEW_QUERY_RESPONSE:
            queryResponseMsg = check_and_cast<NewQueryResponseMessage*>(newMsg);
            handleNewQueryResponseMessage(queryResponseMsg);
            break;
            case NEW_JOINEVAL:
            joinEvalMsg = check_and_cast<NewJoinEvalMessage*>(newMsg);
            handleNewJoinEvalMessage(joinEvalMsg);
            break;
            case NEW_JOINEVAL_RESPONSE:
            joinEvalResponseMsg = check_and_cast<NewJoinEvalResponseMessage*>(newMsg);
            handleNewJoinEvalResponseMessage(joinEvalResponseMsg);
            break;
            case NEW_JOIN:
            joinMsg = check_and_cast<NewJoinMessage*>(newMsg);
            handleNewJoinMessage(joinMsg);
            break;
            case NEW_JOIN_RESPONSE:
            joinResponseMsg = check_and_cast<NewJoinResponseMessage*>(newMsg);
            handleNewJoinResponseMessage(joinResponseMsg);
            break;
            case NEW_INSERT_QUERY:
            insertQueryMsg = check_and_cast<NewInsertQueryMessage*>(newMsg);
            handleNewInsertQueryMessage(insertQueryMsg);
            break;
            case NEW_INSERT_QUERY_RESPONSE:
            insertQueryResponseMsg = check_and_cast<NewInsertQueryResponseMessage*>(newMsg);
            handleNewInsertQueryResponseMessage(insertQueryResponseMsg);
            break;
            case NEW_INSERTEVAL:
            insertEvalMsg = check_and_cast<NewInsertEvalMessage*>(newMsg);
            handleNewInsertEvalMessage(insertEvalMsg);
            break;
            case NEW_INSERTEVAL_RESPONSE:
            insertEvalResponseMsg = check_and_cast<NewInsertEvalResponseMessage*>(newMsg);
            handleNewInsertEvalResponseMessage(insertEvalResponseMsg);
            break;
            case NEW_INSERT:
            insertMsg = check_and_cast<NewInsertMessage*>(newMsg);
            handleNewInsertMessage(insertMsg);
            break;
            case NEW_INSERT_RESPONSE:
            insertResponseMsg = check_and_cast<NewInsertResponseMessage*>(newMsg);
            handleNewInsertResponseMessage(insertResponseMsg);
            break;
            case NEW_JOIN_SUCCESS:
            joinSuccessMsg = check_and_cast<NewJoinSuccessMessage*>(newMsg);
            handleNewJoinSuccessMessage(joinSuccessMsg);
            break;
            case NEW_JOIN_STATISTIC:
            statisticMsg = check_and_cast<NewStatisticMessage*>(newMsg);
            handleNewStatisticMessage(statisticMsg);
            break;
            default:
            delete newMsg;
            break;
        }
    }else{
        delete msg;
    }
}

void NewOverlay::joinOverlay()
{
//    setOverlayReady(true);
}

void NewOverlay::finishOverlay()
{
//    setOverlayReady(false);
}

void NewOverlay::setOwnNodeID()
{
    thisNode.setKey(OverlayKey(myKey));
}
void NewOverlay::updateVisualization(){
    showOverlayNeighborArrow(serverNode,true,newArrows[0]);
    deleteOverlayNeighborArrow(serverNode);
    bool flag=true;
    unsigned int l=0;
    for(unsigned int i = 0;i<childList.size();i++){
        if(childDataSeqList[i]==l){
            showOverlayNeighborArrow(childList[i],flag,newArrows[0]);
            flag=false;
        }
    }

//    for(unsigned int i = 0;i<parentList.size();i++){
//        showOverlayNeighborArrow(parentList[l],flag,newArrows[1]);
//        flag=false;
//    }
}

bool NewOverlay::isSiblingFor(const NodeHandle& node,const OverlayKey& key, int numSiblings, bool* err){

    // is it our node and our key?
    if (node == thisNode && key == thisNode.getKey()) {
        return true;
    }
    // we don't know otherwise
    return false;
}

NodeVector *NewOverlay::findNode(const OverlayKey& key,
                                int numRedundantNodes,
                                int numSiblings,
                                BaseOverlayMessage* msg){
    NodeVector* nextHops;
    nextHops = new NodeVector(1);

    NodeHandle nextNode;
    nextNode.setIp(IPAddress(BIGBIT | (int)key.toDouble()));
    nextNode.setPort(thisNode.getPort());
    nextNode.setKey(key);

    nextHops->add(nextNode);
    return nextHops;
}
int NewOverlay::getMaxNumSiblings(){
    return 1;
}
int NewOverlay::getMaxNumRedundantNodes(){
    return 1;
}
void NewOverlay::startJoiningOverlay(){
    EV<<"[Fanjing]NewOverlay::startJoin: " << nodeAddress <<std::endl;
    globalStatistics->recordOutVector("Fanjing:New::startJoiningTime: ",myKey);
    //Todo:Important~!
    joinTime=simTime();
    globalStatistics->recordOutVector("Fanjing:New::joinTime:",myKey);
    nodeState = NodeState_Join;
    for(unsigned int i=0;i<numOfLayers;i++){
        EV<<"[Fanjing]NewOverlay::startJoin: i - " << i <<std::endl;
        if (parentStateList[i] == Link_Init) {
            //1st.Use the server free resource.
            if (serverFreeDegree > 0) {
                EV<<"[Fanjing]NewOverlay::startJoin: " << nodeAddress <<" Use server free resource."<<std::endl;
                //Creat the join message.
                NewJoinMessage *joinMsg = new NewJoinMessage();
                joinMsg->setSrcNode(nodeAddress);
                joinMsg->setSentTime(simTime());
                joinMsg->setCommand(NEW_JOIN);

                joinMsg->setDataSeq(i);

                //Send the join message.
                joinMsg->setBitLength(NEWJOINMESSAGE_L(joinMsg));
                sendMessageToUDP(serverNode, joinMsg);

                //Update the node statis state.
                parentList[i] = serverNode;
                parentStateList[i] = Link_Selected;

                //Remove the free resource.
                serverFreeDegree--;
                continue;
            }
            //2nd. Use the best free resource of other peer.
            double *dataRate=new double[peerInfoList.size()];
            //2nd. 1.Calculate the using rate of each DataSeq in every neighbor peer.
            for(unsigned int j=0;j<peerInfoList.size();j++){
                //Init the dataRate.
                dataRate[j]=0;
                EV<<"[Fanjing]NewOverlay::startJoin: j - "<<j<<std::endl;
                if(peerInfoList[j]->freeDegree>0){
                    EV<<"[Fanjing]NewOverlay::startJoin: peerInfoList[j]->freeDegree - "<<peerInfoList[j]->freeDegree<<std::endl;
                    if (peerInfoList[j]->childDataSeqList.size() != 0) {
                        EV<<"[Fanjing]NewOverlay::startJoin: peerInfoList[j]->childDataSeqList.size() - "<<peerInfoList[j]->childDataSeqList.size()<<std::endl;
                        for (unsigned int k = 0; k < peerInfoList[j]->childDataSeqList.size(); k++) {
                            if (peerInfoList[j]->childDataSeqList[k] == i) {
                                dataRate[j] += 1;
                            }
                        }
                        dataRate[j] = dataRate[j]
                                / peerInfoList[j]->childDataSeqList.size();
                    }
                }
            }
            //2nd. 2.Choose the best peer which has the highest using rate of the selected DataSeq.
            unsigned int bestPeerNum=0;
            for(unsigned int j=0;j<peerInfoList.size();j++){
                bestPeerNum=dataRate[j]>dataRate[bestPeerNum]?j:bestPeerNum;
            }
            EV<<"[Fanjing]NewOverlay::startJoin: bestPeerNum - "<<bestPeerNum<<std::endl;
            //2nd. 3.If the highest using rate is bigger than 'zero', use it.
            if(dataRate[bestPeerNum]>0){
                EV<<"[Fanjing]NewOverlay::startJoin: " << nodeAddress <<" Use peer's free resource."<<std::endl;
                //Creat the join message.
                NewJoinMessage *joinMsg = new NewJoinMessage();
                joinMsg->setSrcNode(nodeAddress);
                joinMsg->setSentTime(simTime());
                joinMsg->setCommand(NEW_JOIN);

                joinMsg->setDataSeq(i);

                //Send the join message.
                joinMsg->setBitLength(NEWJOINMESSAGE_L(joinMsg));
                sendMessageToUDP(peerInfoList[bestPeerNum]->nodeAddress, joinMsg);

                //Update the node statis state.
                parentList[i] = peerInfoList[bestPeerNum]->nodeAddress;
                parentStateList[i] = Link_Selected;
                //Update the peerInfo state.
                peerInfoList[bestPeerNum]->childDataSeqList.push_back(i);
                peerInfoList[bestPeerNum]->childList.push_back(nodeAddress);
                //Remove the free resource.
                peerInfoList[bestPeerNum]->freeDegree--;
                continue;
            }
            //3rd. Replace weak data link with good data link.
            //Todo:2012-11-10
            //3rd. 1.Tell if any link can be replaced.

            bool replaceFlag=false;
            unsigned int goodDataSeq;
            unsigned int badDataSeq;
            unsigned int peerInfoNum;
            for(unsigned int j=0;j<peerInfoList.size();j++){
                double dataRateI = peerInfoList[j]->getChildDataRate(i);
                if (dataRateI > 0 && dataRateI < 1) {
                    for (unsigned int k = i + 1; k < parentStateList.size(); k++) {
                        if (parentStateList[k] == Link_Init) {
                            double dataRateK =
                                    peerInfoList[j]->getChildDataRate(k);
                            if (dataRateK > 0 && dataRateK < 1) {
                                replaceFlag=true;
                                //3rd. 2.Set good and weak dataSeq and send the messages;
                                if (dataRateI > dataRateK) {
                                    goodDataSeq=i;
                                    badDataSeq=k;
                                }else{
                                    goodDataSeq=k;
                                    badDataSeq=i;
                                }
                                peerInfoNum=j;
                                break;
                            }
                        }
                    }
                }
                if(replaceFlag)
                    break;
            }
            //3rd. 3.Send insertMsgs to related peers;
            if (replaceFlag) {
                //Msg to peer[j]'s parent and be its child node
                NewInsertMessage *insertMsgPPC = new NewInsertMessage();
                insertMsgPPC->setSrcNode(nodeAddress);
                insertMsgPPC->setSentTime(simTime());
                insertMsgPPC->setCommand(NEW_INSERT);

                insertMsgPPC->setIsChildNode(true);
                //Msg to peer[j]'s child and be its parent node
                NewInsertMessage *insertMsgPCP = new NewInsertMessage();
                insertMsgPCP->setSrcNode(nodeAddress);
                insertMsgPCP->setSentTime(simTime());
                insertMsgPCP->setCommand(NEW_INSERT);

                insertMsgPCP->setIsChildNode(false);
                //Msg to peer[j] and be its parent node
                NewInsertMessage *insertMsgPP = new NewInsertMessage();
                insertMsgPP->setSrcNode(nodeAddress);
                insertMsgPP->setSentTime(simTime());
                insertMsgPP->setCommand(NEW_INSERT);

                insertMsgPP->setIsChildNode(false);
                //Msg to peer[j] and be its child node
                NewInsertMessage *insertMsgPC = new NewInsertMessage();
                insertMsgPC->setSrcNode(nodeAddress);
                insertMsgPC->setSentTime(simTime());
                insertMsgPC->setCommand(NEW_INSERT);

                insertMsgPC->setIsChildNode(true);

                insertMsgPC->setDataSeq(goodDataSeq);
                insertMsgPC->setSelectedNode(peerInfoList[peerInfoNum]->getChildByDataSeq(badDataSeq));
                insertMsgPC->setSelectedDataSeq(badDataSeq);
                insertMsgPC->setBitLength(NEWINSERTMESSAGE_L(insertMsgPC));
                sendMessageToUDP(peerInfoList[peerInfoNum]->nodeAddress, insertMsgPC);

                insertMsgPP->setDataSeq(badDataSeq);
                insertMsgPP->setSelectedNode(peerInfoList[peerInfoNum]->parentList[badDataSeq]);
                insertMsgPP->setSelectedDataSeq(badDataSeq);
                insertMsgPP->setBitLength(NEWINSERTMESSAGE_L(insertMsgPP));
                sendMessageToUDP(peerInfoList[peerInfoNum]->nodeAddress, insertMsgPP);

                insertMsgPPC->setDataSeq(badDataSeq);
                insertMsgPPC->setSelectedNode(peerInfoList[peerInfoNum]->nodeAddress);
                insertMsgPPC->setSelectedDataSeq(badDataSeq);
                insertMsgPPC->setBitLength(NEWINSERTMESSAGE_L(insertMsgPPC));
                sendMessageToUDP(peerInfoList[peerInfoNum]->parentList[badDataSeq],insertMsgPPC);

                insertMsgPCP->setDataSeq(badDataSeq);
                insertMsgPCP->setSelectedNode(peerInfoList[peerInfoNum]->nodeAddress);
                insertMsgPCP->setSelectedDataSeq(badDataSeq);
                insertMsgPCP->setBitLength(NEWINSERTMESSAGE_L(insertMsgPCP));
                sendMessageToUDP(peerInfoList[peerInfoNum]->getChildByDataSeq(badDataSeq),insertMsgPCP);

                //Update the node statis state.
                parentList[goodDataSeq] = peerInfoList[peerInfoNum]->nodeAddress;
                parentStateList[goodDataSeq] = Link_Selected;
                parentList[badDataSeq] = peerInfoList[peerInfoNum]->parentList[badDataSeq];
                parentStateList[badDataSeq] = Link_Selected;

                childList.push_back(peerInfoList[peerInfoNum]->nodeAddress);
                childDataSeqList.push_back(badDataSeq);
                childStateList.push_back(Link_Selected);
                childList.push_back(peerInfoList[peerInfoNum]->getChildByDataSeq(badDataSeq));
                childDataSeqList.push_back(badDataSeq);
                childStateList.push_back(Link_Selected);

                //Update the peerInfo state.(maybe not necessary)
                //Will be added, if necessary
                //Remove the free resource. Just itself.
                freeDegree-=2;
                //Next dataSeq.
                continue;
            }
            //4th. Use the rest free resource.
            //4th. 1.Find free resource.
            unsigned int freeNode = peerInfoList.size();
            for(unsigned int j=0;j<peerInfoList.size();j++){
                if(peerInfoList[j]->freeDegree>0){
                    freeNode=j;
                    break;
                }
            }
            //4th. 2.If there some free resource, just use.
            if(freeNode<peerInfoList.size()){
                //Creat the join message.
                NewJoinMessage *joinMsg = new NewJoinMessage();
                joinMsg->setSrcNode(nodeAddress);
                joinMsg->setSentTime(simTime());
                joinMsg->setCommand(NEW_JOIN);

                joinMsg->setDataSeq(i);

                //Send the join message.
                joinMsg->setBitLength(NEWJOINMESSAGE_L(joinMsg));
                sendMessageToUDP(peerInfoList[freeNode]->nodeAddress, joinMsg);

                //Update the node statis state.
                parentList[i] = peerInfoList[freeNode]->nodeAddress;
                parentStateList[i] = Link_Selected;
                //Update the peerInfo state.(maybe not necessary)
                //Will be added, if necessary
                //Remove the free resource.
                peerInfoList[freeNode]->freeDegree--;
                continue;
            }
            //5th. If this dataSeq still haven't joined the overlay, use insert operation to join.
            //Msg to peer[?]'s parent and be its child node
            NewInsertMessage *insertMsgPPC = new NewInsertMessage();
            insertMsgPPC->setSrcNode(nodeAddress);
            insertMsgPPC->setSentTime(simTime());
            insertMsgPPC->setCommand(NEW_INSERT);

            insertMsgPPC->setIsChildNode(true);
            //Msg to peer[?] and be its parent node
            NewInsertMessage *insertMsgPP = new NewInsertMessage();
            insertMsgPP->setSrcNode(nodeAddress);
            insertMsgPP->setSentTime(simTime());
            insertMsgPP->setCommand(NEW_INSERT);

            insertMsgPP->setIsChildNode(false);

            insertMsgPPC->setDataSeq(i);
            insertMsgPP->setDataSeq(i);
            insertMsgPPC->setSelectedNode(peerInfoList[0]->nodeAddress);
            insertMsgPP->setSelectedNode(peerInfoList[0]->parentList[i]);
            insertMsgPPC->setSelectedDataSeq(i);
            insertMsgPP->setSelectedDataSeq(i);

            insertMsgPPC->setBitLength(NEWINSERTMESSAGE_L(insertMsgPPC));
            sendMessageToUDP(peerInfoList[0]->parentList[i],insertMsgPPC);
            insertMsgPP->setBitLength(NEWINSERTMESSAGE_L(insertMsgPP));
            sendMessageToUDP(peerInfoList[0]->nodeAddress,insertMsgPP);
            //Update the node statis state.
            parentList[i] = peerInfoList[0]->parentList[i];
            parentStateList[i] = Link_Selected;
            childList.push_back(peerInfoList[0]->nodeAddress);
            childDataSeqList.push_back(i);
            childStateList.push_back(Link_Selected);
            //Update the peerInfo state.(maybe not necessary)
            //Will be added, if necessary
            //Remove the free resource.
            freeDegree--;
            continue;

        }
    }
}

void NewOverlay::checkLinkState(){
    EV<<"[Fanjing]NewOverlay::checkLinkState: " <<nodeAddress<<std::endl;
    for(unsigned int i=0;i<parentStateList.size();i++){
        if(parentStateList[i]!=Link_Connected){
            EV<<"[Fanjing]NewOverlay::checkLinkState: parentStateList - " <<i<<std::endl;
            EV<<"[Fanjing]NewOverlay::checkLinkState: parentList - " <<parentList[i]<<std::endl;
            return;
        }
    }
    for(unsigned int i=0;i<childStateList.size();i++){
        if(childStateList[i]!=Link_Connected){
            EV<<"[Fanjing]NewOverlay::checkLinkState: childStateList - " <<i<<std::endl;
            return;
        }
    }
    NewJoinSuccessMessage *joinSuccessMsg = new NewJoinSuccessMessage();
    joinSuccessMsg->setSrcNode(nodeAddress);
    joinSuccessMsg->setSentTime(simTime());
    joinSuccessMsg->setCommand(NEW_JOIN_SUCCESS);

    joinSuccessMsg->setBitLength(NEWJOINSUCCESSMESSAGE_L(joinSuccessMsg));
    sendMessageToUDP(serverNode,joinSuccessMsg);
    joinSuccessTime = simTime();
    globalStatistics->recordOutVector("Fanjing:New::joinSuccessTime: ",myKey);
    getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 1, "white");
    nodeState = NodeState_Joined;
}

void NewOverlay::finishJoiningOverlay(){
//    NewJoinSuccessMessage *joinSuccessMsg = new NewJoinSuccessMessage();
//    joinSuccessMsg->setSrcNode(nodeAddress);
//    joinSuccessMsg->setBitLength(NEWJOINSUCCESSMESSAGE_L(joinSuccessMsg));
//    joinSuccessMsg->setSentTime(simTime());
//    joinSuccessMsg->setCommand(NEW_JOIN_SUCCESS);
//
//    sendMessageToUDP(serverNode,joinSuccessMsg);
}

void NewOverlay::handleNewQueryMessage(NewQueryMessage *msg)
{
    EV << "NewOverlay::handleNewQueryMessage" << std::endl;
    if (nodeType == ServerNode){
        nodeList.push_back(msg->getSrcNode());
        if (nodeState != NodeState_Wait) {
            NewQueryResponseMessage *queryResponseMsg =
                    new NewQueryResponseMessage();
            queryResponseMsg->setSrcNode(nodeAddress);
            queryResponseMsg->setSentTime(simTime());
            queryResponseMsg->setCommand(NEW_QUERY_RESPONSE);

            queryResponseMsg->setFreeDegree(freeDegree);
            queryResponseMsg->setMembersArraySize(joinedNodeList.size());
            for (unsigned int i = 0; i < joinedNodeList.size(); i++)
                queryResponseMsg->setMembers(i, joinedNodeList[i]);

            queryResponseMsg->setBitLength(NEWQUERYRESPONSEMESSAGE_L(queryResponseMsg));
            sendMessageToUDP(msg->getSrcNode(),queryResponseMsg);
            nodeState = NodeState_Wait;

            EV<<"[Fanjing]NewOverlay::ServerNode -> NodeState_Wait: " <<msg->getSrcNode()<<std::endl;
        }

    }else{
        EV << "NewOverlay::Error - PeerNode Receives a 'QueryMessage'." <<std::endl;
    }
    delete msg;
}



void NewOverlay::handleNewQueryResponseMessage(NewQueryResponseMessage *msg)
{
    EV << "NewOverlay::handleNewQueryResponseMessage" <<nodeAddress<< std::endl;
    globalStatistics->recordOutVector("Fanjing:New::QueryResponseTime: ",myKey);
    if(nodeType == PeerNode){
        serverFreeDegree=msg->getFreeDegree();
        joinEvalTime = simTime();
        globalStatistics->recordOutVector("Fanjing:New::joinEvalTime:",myKey);
        EV<<"[Fanjing]NewOverlay::serverFreeDegree: " << msg->getFreeDegree() <<std::endl;
        if (msg->getFreeDegree() < numOfLayers) {
            for (unsigned int i = 0; i < msg->getMembersArraySize(); i++) {
                NewJoinEvalMessage *joinEvalMsg = new NewJoinEvalMessage();
                joinEvalMsg->setSrcNode(nodeAddress);
                joinEvalMsg->setSentTime(simTime());
                joinEvalMsg->setCommand(NEW_JOINEVAL);

                nodeList.push_back(msg->getMembers(i));
                joinEvalMsg->setBitLength(NEWJOINEVALMESSAGE_L(joinEvalMsg));
                sendMessageToUDP(msg->getMembers(i), joinEvalMsg);
            }
            nodeState = NodeState_JoinEval;
        }else{
            startJoiningOverlay();
        }
    }else{
        EV << "NewOverlay::Error - ServerNode Receives a 'QueryResponseMessage'." <<std::endl;
    }
    delete msg;
}



void NewOverlay::handleNewJoinEvalMessage(NewJoinEvalMessage *msg)
{
    EV << "NewOverlay::handleNewJoinEvalMessage" << std::endl;
    if (nodeType == PeerNode) {
        NewJoinEvalResponseMessage *joinEvalResponseMsg =
                new NewJoinEvalResponseMessage();
        joinEvalResponseMsg->setSrcNode(nodeAddress);
        joinEvalResponseMsg->setSentTime(msg->getSentTime());
        joinEvalResponseMsg->setCommand(NEW_JOINEVAL_RESPONSE);

        joinEvalResponseMsg->setFreeDegree(freeDegree);
        joinEvalResponseMsg->setDataTimeStampArraySize(dataTimeStamp.size());
        for (unsigned int i = 0; i < dataTimeStamp.size(); i++) {
            joinEvalResponseMsg->setDataTimeStamp(i, dataTimeStamp[i]);
        }
        joinEvalResponseMsg->setParentNodeArraySize(parentList.size());
        for (unsigned int i = 0; i < parentList.size(); i++) {
            joinEvalResponseMsg->setParentNode(i, parentList[i]);
        }
        joinEvalResponseMsg->setChildNodeArraySize(childList.size());
        for (unsigned int i = 0; i < childList.size(); i++) {
            joinEvalResponseMsg->setChildNode(i, childList[i]);
        }
        joinEvalResponseMsg->setChildDataSeqArraySize(childDataSeqList.size());
        for (unsigned int i = 0; i < childDataSeqList.size(); i++) {
            joinEvalResponseMsg->setChildDataSeq(i, childDataSeqList[i]);
        }
        joinEvalResponseMsg->setBitLength(NEWJOINEVALRESPONSEMESSAGE_L(joinEvalResponseMsg));
        sendMessageToUDP(msg->getSrcNode(),joinEvalResponseMsg);
    }else{
        EV << "NewOverlay::Error - ServerNode Receives a 'JoinEvalMessage'." <<std::endl;
    }
    delete msg;
    return;
}

void NewOverlay::handleNewJoinEvalResponseMessage(NewJoinEvalResponseMessage *msg)
{
    EV<<"[Fanjing]NewOverlay::JoinEval: " <<msg->getSrcNode()<<std::endl;
    if (nodeType == PeerNode) {
        if (nodeState == NodeState_JoinEval) {
            NewPeerInfo *peerInfo = new NewPeerInfo();
            peerInfo->freeDegree = msg->getFreeDegree();
            peerInfo->nodeAddress = msg->getSrcNode();
            for (unsigned int i = 0; i < msg->getDataTimeStampArraySize(); i++) {
                peerInfo->dataTimeStamp.push_back(msg->getDataTimeStamp(i));
            }
            for (unsigned int i = 0; i < msg->getParentNodeArraySize(); i++) {
                peerInfo->parentList.push_back(msg->getParentNode(i));
            }
            for (unsigned int i = 0; i < msg->getChildNodeArraySize(); i++) {
                peerInfo->childList.push_back(msg->getChildNode(i));
            }
            for (unsigned int i = 0; i < msg->getChildDataSeqArraySize(); i++) {
                peerInfo->childDataSeqList.push_back(msg->getChildDataSeq(i));
            }
            peerInfoList.push_back(peerInfo);
            if (peerInfoList.size() == nodeList.size() || peerInfoList.size()
                    == peerRatio * k) {
                startJoiningOverlay();
            }
        }
    }
    delete msg;
}

void NewOverlay::handleNewInsertMessage(NewInsertMessage *msg)
{
    EV<<"[Fanjing]NewOverlay::Insert: " <<msg->getSrcNode()<<std::endl;
    if (msg->getIsChildNode()) {
        for (unsigned int i = 0; i < childList.size(); i++) {
            if (childList[i] == msg->getSelectedNode() && childDataSeqList[i] == msg->getSelectedDataSeq()) {
                childList[i] = msg->getSrcNode();
                childDataSeqList[i] = msg->getDataSeq();
                NewInsertResponseMessage *insertResponseMsg = new NewInsertResponseMessage();
                insertResponseMsg->setSrcNode(nodeAddress);
                insertResponseMsg->setSentTime(simTime());
                insertResponseMsg->setCommand(NEW_INSERT_RESPONSE);

                insertResponseMsg->setIsChildNode(!msg->getIsChildNode());
                insertResponseMsg->setDataSeq(msg->getDataSeq());
                insertResponseMsg->setBitLength(NEWINSERTRESPONSEMESSAGE_L(insertResponseMsg));
                sendMessageToUDP(msg->getSrcNode(), insertResponseMsg);
                break;
            }
        }
    }else{
        if(parentList[msg->getSelectedDataSeq()]==msg->getSelectedNode()){
            parentList[msg->getDataSeq()]=msg->getSrcNode();
            NewInsertResponseMessage *insertResponseMsg = new NewInsertResponseMessage();
            insertResponseMsg->setSrcNode(nodeAddress);
            insertResponseMsg->setSentTime(simTime());
            insertResponseMsg->setCommand(NEW_INSERT_RESPONSE);

            insertResponseMsg->setIsChildNode(!msg->getIsChildNode());
            insertResponseMsg->setDataSeq(msg->getDataSeq());
            insertResponseMsg->setBitLength(NEWINSERTRESPONSEMESSAGE_L(insertResponseMsg));
            sendMessageToUDP(msg->getSrcNode(),insertResponseMsg);
        }
    }
    delete msg;
}

void NewOverlay::handleNewInsertResponseMessage(NewInsertResponseMessage *msg)
{
    EV<<"[Fanjing]NewOverlay::InsertResponse: " <<msg->getSrcNode()<<std::endl;
    if(nodeType==PeerNode){
        if(msg->getIsChildNode()){
            for (unsigned int i = 0; i < childList.size(); i++) {
                if(childList[i]==msg->getSrcNode()&&childDataSeqList[i]==msg->getDataSeq()){
                    childStateList[i]=Link_Connected;
                    checkLinkState();
                    break;
                }
            }
        }else{
            if(parentList[msg->getDataSeq()]==msg->getSrcNode()){
                parentStateList[msg->getDataSeq()]=Link_Connected;
                checkLinkState();
            }
        }
    }
    delete msg;
}

void NewOverlay::handleNewJoinMessage(NewJoinMessage *msg)
{
    EV<<"[Fanjing]NewOverlay::Join: " <<msg->getSrcNode()<<std::endl;
    if(freeDegree>0){
        childList.push_back(msg->getSrcNode());
        childDataSeqList.push_back(msg->getDataSeq());
        freeDegree--;
        NewJoinResponseMessage *joinResponseMsg = new NewJoinResponseMessage();
        joinResponseMsg->setSrcNode(nodeAddress);
        joinResponseMsg->setSentTime(simTime());
        joinResponseMsg->setCommand(NEW_JOIN_RESPONSE);

        joinResponseMsg->setDataSeq(msg->getDataSeq());
        joinResponseMsg->setBitLength(NEWJOINRESPONSEMESSAGE_L(joinResponseMsg));
        sendMessageToUDP(msg->getSrcNode(),joinResponseMsg);
    }else{
        EV << "NewOverlay::Error - Node doesn't have enough resource." <<std::endl;
    }
    delete msg;
}

void NewOverlay::handleNewJoinResponseMessage(NewJoinResponseMessage *msg)
{
    EV<<"[Fanjing]NewOverlay::JoinResponse: " <<msg->getSrcNode()<<std::endl;
    if (nodeType == PeerNode) {
        if (nodeState == NodeState_Join) {
            if (parentList[msg->getDataSeq()] == msg->getSrcNode()
                    && parentStateList[msg->getDataSeq()]
                            == Link_Selected) {
                EV<<"[Fanjing]NewOverlay::parentStateList: " <<msg->getDataSeq()<<std::endl;
                parentStateList[msg->getDataSeq()] = Link_Connected;
            }
        }
        checkLinkState();
    }
    delete msg;
}

void NewOverlay::handleNewJoinSuccessMessage(NewJoinSuccessMessage *msg){
    if(nodeType==ServerNode){
        EV<<"[Fanjing]NewOverlay::JoinSuccess: " <<msg->getSrcNode()<<std::endl;
        joinedNodeList.push_back(msg->getSrcNode());
        if(joinedNodeList.size()<nodeList.size()){

            NewQueryResponseMessage *queryResponseMsg =
                    new NewQueryResponseMessage();
            queryResponseMsg->setSrcNode(nodeAddress);
            queryResponseMsg->setSentTime(simTime());
            queryResponseMsg->setCommand(NEW_QUERY_RESPONSE);

            queryResponseMsg->setFreeDegree(freeDegree);
            queryResponseMsg->setMembersArraySize(joinedNodeList.size());
            for (unsigned int i = 0; i < joinedNodeList.size(); i++)
                queryResponseMsg->setMembers(i, joinedNodeList[i]);

            queryResponseMsg->setBitLength(NEWQUERYRESPONSEMESSAGE_L(queryResponseMsg));
            sendMessageToUDP(nodeList[joinedNodeList.size()],queryResponseMsg);
            nodeState = NodeState_Wait;
            EV<<"[Fanjing]NewOverlay::ServerNode -> NodeState_Wait: " <<msg->getSrcNode()<<std::endl;
        }else{
            nodeState = NodeState_Init;
            EV<<"[Fanjing]NewOverlay::ServerNode -> NodeState_Init: " <<msg->getSrcNode()<<std::endl;
            if(joinedNodeList.size()==terminalNum-1){

                getParentModule()->getParentModule()->getDisplayString().setTagArg("i2", 1, "black");
                for(unsigned int i=0;i<childList.size();i++) {
                    NewStatisticMessage *statisticMsg = new NewStatisticMessage();
                    statisticMsg->setSrcNode(nodeAddress);
                    statisticMsg->setSentTime(simTime());
                    statisticMsg->setCommand(NEW_JOIN_STATISTIC);

                    statisticMsg->setDataSeq(childDataSeqList[i]);
                    statisticMsg->setJumpNum(0);
                    statisticMsg->setDataTimeStamp(0);
                    statisticMsg->setBitLength(NEWSTATISTICMESSAGE_L(statisticMsg));
                    sendMessageToUDP(childList[i],statisticMsg);
                }
            }
        }
    }
    delete msg;
}


void NewOverlay::handleNewStatisticMessage(NewStatisticMessage *msg)
{
    std::string str0;
    std::string str1;
    str1=std::string(newNumStr[msg->getDataSeq()]);
    simtime_t second=1.0;
    dataTimeStamp[msg->getDataSeq()]=msg->getDataTimeStamp()+simTime()-msg->getSentTime();
    jumpNum[msg->getDataSeq()]=msg->getJumpNum()+1;
    str0="Fanjing:NEW::jumpNumHistogram";
    str0+=str1;
    globalStatistics->recordHistogram(str0,jumpNum[msg->getDataSeq()]);
    str0="Fanjing:NEW::dataTimeStampHistogram";
    str0+=str1;
    globalStatistics->recordHistogram(str0,dataTimeStamp[msg->getDataSeq()]/second);
    str0="Fanjing:NEW:dataTimeStamp";
    str0+=str1;
    globalStatistics->recordOutVector(str0,dataTimeStamp[msg->getDataSeq()]/second);
    unsigned int branchNum=0;
    for(unsigned int i=0;i<childDataSeqList.size();i++){
        if(childDataSeqList[i]==msg->getDataSeq()){
            branchNum++;
        }
    }
    if(branchNum>0){
        double branchRate = (double)branchNum/childDataSeqList.size();
        str0="Fanjing:New::branchNumDistribution";
        str0+=str1;
        globalStatistics->recordHistogram(str0,branchNum);
        str0="Fanjing:New::branchRateDistribution";
        str0+=str1;
        globalStatistics->recordHistogram(str0,branchRate);
    }
    for(unsigned int i = 0;i<childList.size();i++){
        if(childDataSeqList[i]==msg->getDataSeq()){

            NewStatisticMessage *statisticMsg = new NewStatisticMessage();
            statisticMsg->setSrcNode(nodeAddress);
            statisticMsg->setSentTime(simTime());
            statisticMsg->setCommand(NEW_JOIN_STATISTIC);

            statisticMsg->setDataSeq(msg->getDataSeq());
            statisticMsg->setJumpNum(msg->getJumpNum()+1);
            statisticMsg->setDataTimeStamp(dataTimeStamp[msg->getDataSeq()]);
            statisticMsg->setBitLength(NEWSTATISTICMESSAGE_L(statisticMsg));
            sendMessageToUDP(childList[i],statisticMsg);
        }
    }
    unsigned int minJumpNum=jumpNum[0];
    unsigned int maxJumpNum=jumpNum[0];
    simtime_t maxDataTimeStamp=dataTimeStamp[0];
    for(unsigned int i = 0;i<jumpNum.size();i++){
        minJumpNum=minJumpNum<jumpNum[i]?minJumpNum:jumpNum[i];
        maxJumpNum=maxJumpNum>jumpNum[i]?maxJumpNum:jumpNum[i];
        maxDataTimeStamp=maxDataTimeStamp>dataTimeStamp[i]?maxDataTimeStamp:dataTimeStamp[i];
    }
    if(minJumpNum>0){
        globalStatistics->addStdDev("Fanjing:NEW::maxJumpNum",maxJumpNum);
        globalStatistics->addStdDev("Fanjing:NEW::maxDataTimeStamp",maxDataTimeStamp/second);
        globalStatistics->recordHistogram("Fanjing:NEW::QueryTime",queryTime/second);
        globalStatistics->recordHistogram("Fanjing:NEW:joinEval-queryTime",(joinEvalTime-queryTime)/second);
        globalStatistics->recordHistogram("Fanjing:NEW:joinTime-joinEvalTime",(joinTime-joinEvalTime)/second);
        globalStatistics->recordOutVector("Fanjing:NEW::joinSuccessTime-joinEvalTime",(joinSuccessTime-joinEvalTime)/second);
        globalStatistics->recordOutVector("Fanjing:NEW::joinSuccessTime-queryTime",(joinSuccessTime-queryTime)/second);
        globalStatistics->recordOutVector("Fanjing:NEW:maxdataTimeStamp",maxDataTimeStamp/second);

//        globalStatistics->addStdDev("Fanjing:New::queryTime:"+itoa(myKey),queryTime/second);
//        globalStatistics->addStdDev("Fanjing:New::joinEvalTime:"+itoa(myKey),joinEvalTime/second);
//        globalStatistics->addStdDev("Fanjing:New::joinTime:"+itoa(myKey),joinTime/second);
//        globalStatistics->addStdDev("Fanjing:New::joinSuccessTime:"+itoa(myKey),joinSuccessTime/second);
    }
    delete msg;
}
void NewOverlay::handleNewInsertQueryMessage(NewInsertQueryMessage *msg)
{
    //Abandoned
}


void NewOverlay::handleNewInsertQueryResponseMessage(NewInsertQueryResponseMessage *msg)
{
    //Abandoned
}

void NewOverlay::handleNewInsertEvalMessage(NewInsertEvalMessage *msg)
{
    //Abandoned
}


void NewOverlay::handleNewInsertEvalResponseMessage(NewInsertEvalResponseMessage *msg)
{
    //Abandoned
}


NewOverlay::NewOverlay()
{
    // TODO Auto-generated constructor stub
    joinTimer = NULL;
    visualizationTimer = NULL;
}

NewOverlay::~NewOverlay()
{
    // TODO Auto-generated destructor stub
    cancelAndDelete(joinTimer);
    cancelAndDelete(visualizationTimer);
}
