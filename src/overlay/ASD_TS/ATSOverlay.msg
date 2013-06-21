//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

//
// TODO generated message class
//
cplusplus {{
#include <TransportAddress.h>
#include <CommonMessages_m.h>

static const int ATSCOMMAND_L = 8;
static const int INT_L = 32;
static const int SIMTIME_L = 32;
static const int BOOL_L = 8;
static const int DOUBLE_L = 64;
static const int SHORT_L = 16;

#define TRANSPORTADDRESS_L (IPADDR_L + UDPPORT_L)

#define ATSMESSAGE_L(msg) (BASEOVERLAY_L(msg) + ATSCOMMAND_L + TRANSPORTADDRESS_L + SIMTIME_L)
#define ATSQUERYMESSAGE_L(msg) (ATSMESSAGE_L(msg))
#define ATSQUERYRESPONSEMESSAGE_L(msg) (ATSMESSAGE_L(msg)\
		+(msg->getMemberAddressArraySize() * TRANSPORTADDRESS_L)+INT_L)
#define ATSJOINEVALMESSAGE_L(msg) (ATSMESSAGE_L(msg))
#define ATSJOINEVALRESPONSEMESSAGE_L(msg) (ATSMESSAGE_L(msg)+INT_L\
		+(msg->getDataTimeStampArraySize() * SIMTIME_L)\
		+(msg->getParentAddressArraySize() * TRANSPORTADDRESS_L)\
		+(msg->getChildAddressArraySize() * TRANSPORTADDRESS_L)\
		+(msg->getChildDataSeqArraySize() * INT_L))
#define ATSJOINMESSAGE_L(msg) (ATSMESSAGE_L(msg)+INT_L)
#define ATSJOINRESPONSEMESSAGE_L(msg) (ATSMESSAGE_L(msg)+INT_L)
#define ATSINSERTMESSAGE_L(msg) (ATSMESSAGE_L(msg)+BOOL_L+INT_L+TRANSPORTADDRESS_L+INT_L)
#define ATSINSERTRESPONSEMESSAGE_L(msg) (ATSMESSAGE_L(msg)+BOOL_L+INT_L)
#define ATSJOINSUCCESSMESSAGE_L(msg) (ATSMESSAGE_L(msg))
#define ATSSTATISTICMESSAGE_L(msg) (ATSMESSAGE_L(msg)+INT_L+INT_L+SIMTIME_L)



}}
enum ATSCommand{
    ATS_NULL = 0;
    ATS_QUERY = 1;
    ATS_QUERY_RESPONSE = 2;
    ATS_JOINEVAL = 3;
    ATS_JOINEVAL_RESPONSE = 4;
    ATS_JOIN = 5;
    ATS_JOIN_RESPONSE = 6;
    ATS_INSERT = 7;
    ATS_INSERT_RESPONSE = 8;
    ATS_JOIN_SUCCESS = 9;
    ATS_STATISTIC = 10;
};

class noncobject TransportAddress;
class BaseOverlayMessage;

packet ATSMessage extends BaseOverlayMessage{
    //消息类型
    int command = ATS_NULL @enum(ATSCommand);
    //消息发送源节点
    TransportAddress sourceAddress;
    //发送时间戳
    double sendTime;
}
 packet ATSQueryMessage extends ATSMessage{
     command = ATS_QUERY;
 }
 
 packet ATSQueryResponseMessage extends ATSMessage{
     command = ATS_QUERY_RESPONSE;
     TransportAddress memberAddress[];
     unsigned int freeDegree;
 }
 
 packet ATSJoinEvalMessage extends ATSMessage{
     command = ATS_JOINEVAL;
 }
 
 packet ATSJoinEvalResponseMessage extends ATSMessage{
     command = ATS_JOINEVAL_RESPONSE;
     unsigned int freeDegree;
     double dataTimeStamp[];
     TransportAddress parentAddress[];
     TransportAddress childAddress[];
     unsigned int childDataSeq[];
 }
 
 packet ATSJoinMessage extends ATSMessage{
     command = ATS_JOIN;
     unsigned int dataSeq;
 }
 
 packet ATSJoinResponseMessage extends ATSMessage{
     command = ATS_JOIN_RESPONSE;
     unsigned int dataSeq;
 }
 
 packet ATSInsertMessage extends ATSMessage{
     command = ATS_INSERT;
     bool beChildNode;
     unsigned int dataSeq;
     TransportAddress selectedNodeAddress;
     unsigned int selectedDataSeq;
 }
 
 packet ATSInsertResponseMessage extends ATSMessage{
     command = ATS_INSERT_RESPONSE;
     bool beChildNode;
     unsigned int dataSeq;
 }
 
 packet ATSJoinSuccessMessage extends ATSMessage{
     command = ATS_JOIN_SUCCESS;
 }
 
 packet ATSStatisticMessage extends ATSMessage{
     command = ATS_STATISTIC;
     double createTime;
     unsigned int dataSeq;
     unsigned int hop;
 }
     