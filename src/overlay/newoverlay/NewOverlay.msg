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
#include <NodeHandle.h>
#include <CommonMessages_m.h>
#define TRANSPORTADDRESS_L (IPADDR_L + UDPPORT_L)

static const int NEWCOMMAND_L = 8;
static const int INT_L = 32;
static const int SIMTIME_L = 32;
static const int BOOL_L = 8;
static const int DOUBLE_L = 64;
static const int SHORT_L = 16;

#define NEWMESSAGE_L(msg) (BASEOVERLAY_L(msg) + NEWCOMMAND_L + TRANSPORTADDRESS_L + SIMTIME_L)
#define NEWQUERYMESSAGE_L(msg) (NEWMESSAGE_L(msg))
#define NEWQUERYRESPONSEMESSAGE_L(msg) (NEWMESSAGE_L(msg)\
		+(msg->getMembersArraySize() * TRANSPORTADDRESS_L))
#define NEWJOINEVALMESSAGE_L(msg) (NEWMESSAGE_L(msg))
#define NEWJOINEVALRESPONSEMESSAGE_L(msg) (NEWMESSAGE_L(msg)+INT_L\
		+(msg->getDataTimeStampArraySize() * SIMTIME_L)\
		+(msg->getParentNodeArraySize() * TRANSPORTADDRESS_L)\
		+(msg->getChildNodeArraySize() * TRANSPORTADDRESS_L)\
		+(msg->getChildDataSeqArraySize() * INT_L))
#define NEWJOINMESSAGE_L(msg) (NEWMESSAGE_L(msg)+INT_L)
#define NEWJOINRESPONSEMESSAGE_L(msg) (NEWMESSAGE_L(msg)+INT_L)
#define NEWINSERTQUERYMESSAGE_L(msg) (NEWMESSAGE_L(msg)+INT_L)
#define NEWINSERTQUERYRESPONSEMESSAGE_L(msg) (NEWMESSAGE_L(msg)+INT_L\
		+(msg->getChildNodeArraySize() * TRANSPORTADDRESS_L))
#define NEWINSERTEVALMESSAGE_L(msg) (NEWMESSAGE_L(msg)+INT_L)
#define NEWINSERTEVALRESPONSEMESSAGE_L(msg) (NEWMESSAGE_L(msg)+INT_L)
#define NEWINSERTMESSAGE_L(msg) (NEWMESSAGE_L(msg)+BOOL_L+INT_L+TRANSPORTADDRESS_L+INT_L)
#define NEWINSERTRESPONSEMESSAGE_L(msg) (NEWMESSAGE_L(msg)+BOOL_L+INT_L)
#define NEWJOINSUCCESSMESSAGE_L(msg) (NEWMESSAGE_L(msg))
#define NEWSTATISTICMESSAGE_L(msg) (NEWMESSAGE_L(msg)+INT_L+INT_L+SIMTIME_L)
}}

class BaseOverlayMessage;

class noncobject TransportAddress;

//消息类型
enum NEWCommand{
    NEW_QUERY = 0;
    NEW_QUERY_RESPONSE = 1;
    NEW_JOINEVAL = 2;
    NEW_JOINEVAL_RESPONSE = 3;
    NEW_JOIN = 4;
    NEW_JOIN_RESPONSE = 5;
    NEW_INSERT_QUERY = 6;
    NEW_INSERT_QUERY_RESPONSE = 7;
    NEW_INSERTEVAL = 8;
    NEW_INSERTEVAL_RESPONSE = 9;
    NEW_INSERT = 10;
    NEW_INSERT_RESPONSE = 11;
    NEW_JOIN_SUCCESS = 12;
    NEW_JOIN_STATISTIC = 13;
};
//基本消息类
message NewMessage extends BaseOverlayMessage{
    //消息类型
    int command enum(NEWCommand);
    //消息发送源节点
    TransportAddress srcNode;
    //发送时间戳
    simtime_t sentTime;
}

//节点加入查询请求消息
message NewQueryMessage extends NewMessage{
}
//节点接入查询结果返回消息
message NewQueryResponseMessage extends NewMessage{
    //返回查询得到的成员节点
    //int memberNum;
    TransportAddress members[];
    
    unsigned int freeDegree;
	//TransportAddress childNode[];
	//int childDataSeq[];
}

//节点加入评估请求消息
message NewJoinEvalMessage extends NewMessage{
}
//节点加入评估返回消息
message NewJoinEvalResponseMessage extends NewMessage{
    //被请求的节点剩余处理能力
    unsigned int freeDegree;
    
    //被请求节点的当前资源时间戳(越新表示越优越）
    simtime_t dataTimeStamp[];
    
    TransportAddress parentNode[];
    //int parentDataSeq[];
    //simtime_t parentDateTimeStamp[];
    //被请求节点当前数据流的输出情况(用于优化传输结构)
    TransportAddress childNode[];
    unsigned int childDataSeq[];
}

//节点加入请求消息
message NewJoinMessage extends NewMessage{
    //希望获取的数据流序列号
    unsigned int dataSeq;
}
//接受加入请求,并开始发送数据流
message NewJoinResponseMessage extends NewMessage{
    //发送的数据流序列号
    unsigned int dataSeq;
}

//插入查询请求
message NewInsertQueryMessage extends NewMessage{
    //需要进行插入操作的数据流序列号
    unsigned int dataSeq;
}
//插入查询返回消息
message NewInsertQueryResponseMessage extends NewMessage{
    //返回结果对应的数据流序列号
    unsigned int dataSeq;
    
    //可以进行插入操作的子节点
    TransportAddress childNode[];
}

//插入评估请求消息
message NewInsertEvalMessage extends NewMessage{
    //需要评估的数据序列号
    unsigned int dataSeq;
}
//返回插入评估的评估结果
message NewInsertEvalResponseMessage extends NewMessage{
    //需要评估的数据流序列号
    unsigned int dataSeq;
}

//插入请求
message NewInsertMessage extends NewMessage{
    bool isChildNode;
    //插入请求对应的数据流序列号
    unsigned int dataSeq;
    //选中的插入节点
    TransportAddress selectedNode;
    unsigned int selectedDataSeq;
}
//返回插入结果,并开始传输数据
message NewInsertResponseMessage extends NewMessage{
    //开始传播的数据流序列号
    bool isChildNode;
    unsigned int dataSeq;
}

message NewJoinSuccessMessage extends NewMessage{
}

message NewStatisticMessage extends NewMessage{
    unsigned int dataSeq;
    unsigned int jumpNum;
    simtime_t dataTimeStamp;
}
    
    
    
    
    
    
    
    
    