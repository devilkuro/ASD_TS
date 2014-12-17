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
		//		EV<< "JoinScore:" <<getDataScoreByDataSeq(dataSeq)/(dataTimeStamp[dataSeq]+lag)<<"\n";
		//        return getDataScoreByDataSeq(dataSeq)/(dataTimeStamp[dataSeq]+lag);
		EV<<"JoinScore:"<<(1+0)*(lag+dataTimeStamp[dataSeq])<<"\n";//改
		return 1/(1+0)*(lag+dataTimeStamp[dataSeq]);//加入时候无孩子节点（改）
	} else {
		EV<< "JoinScore:" <<0<<"\n";
		return 0;
	}
}

double ATSPeerInfo::getInsertScoreByDataSeq(unsigned int dataSeq,double lagTF) {
	if (freeResource > 0 || getDataScoreByDataSeq(dataSeq) > 0) {
		EV<< "InsertScore:" <<0<<"\n";
		return 0;
	} else {
		//EV<< "InsertScore:" <<0.2 / (dataTimeStamp[dataSeq] + lag)<<"\n";
		//return 0.2 / (dataTimeStamp[dataSeq] + lag);
		double lagF = parentlinklist[dataSeq]->getLag();
		double lagT = getLag();
		EV<< "InsertScore:" <<(1+ChildNum_dataSeq[dataSeq])*lag<<"\n";
		return 1/((1+ChildNum_dataSeq[dataSeq])*(lagTF+lagT-lagF)+(dataTimeStamp[dataSeq]-lagF+lagTF));//因为自己的插入给原先孩子节点带来新的延时（改）
	}
}

double ATSPeerInfo::getSwitchScoreByDataSeq(unsigned int dataSeq1,
		unsigned int dataSeq2, double lag1, double lag2, double lag3,
		double minlag1, double minlag2) {
	EV<<"enter getSwitchScore::"<<dataSeq1<<","<<dataSeq2<<endl;
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
		//        double result1 =  2/(dataTimeStamp[dataSeq1]+lag);
		//        double result2 =  2/(dataTimeStamp[dataSeq2]+lag);
		//    	EV<< "SwitchScore:" <<(result1+result2)/2<<"\n";
		//    	return (result1+result2)/2;

		//改
		if (lag1 == 0 || lag2 == 0 || lag3 == 0 || minlag1 == 0 || minlag2 == 0) {

			EV<< "lag1 == 0 || lag2 == 0 || lag3 == 0 || minlag1 == 0 || minlag2 == 0"<<endl;
			return 0;
		}
		unsigned int parentChildNum1 = ChildNum_dataSeq[dataSeq1];
		unsigned int parentChildNum2 = ChildNum_dataSeq[dataSeq2];

		double result1 = lag1 + minlag1 * parentChildNum1;
		double result2 = lag2 + lag3 * 2 + minlag2 * parentChildNum1;
		EV<<"switchdebugINFO:"
				<<"result1"<<","<<result1<<","
				<<"result2"<<","<<result2<<","
				<<"lag2"<<","<<lag2<<","
				<<"lag3"<<","<<lag3<<","
				<<"minlag2"<<","<<minlag2<<","
				<<"parentChildNum1"<<","<<parentChildNum1
				<<endl;
		EV<<2/(result2-result1)<<"2/(result2-result1)"<<endl;
		return 2/(result2-result1); //求倒数避免判定0,可能为负数
	} else {
		EV<< "SwitchScore:" <<0<<"\n";
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
			return childlinklist[i]->getTargetAddress();//节点转发seqK则返回转发地址
		}
	}
	EV<<"ATSPeerInfo::nonChild\n";
	return address;//若节点内不转发seqK则返回节点地址
}

unsigned int ATSPeerInfo::getChildIndexByDataSeq(unsigned int dataSeq) {
	for (unsigned int i = 0; i < childlinklist.size(); i++) {
		if (childlinklist[i]->getDataSeq() == dataSeq) {
			return i;
		}
	}
	EV<<"ATSPeerInfo::nonChild\n";
	return 0;
}
unsigned int ATSPeerInfo::getChildListSize() {
	return childlinklist.size();
}

ATSPeerInfo::ATSPeerInfo() {
	// TODO Auto-generated constructor stub

}

ATSPeerInfo::~ATSPeerInfo() {
	// TODO Auto-generated destructor stub
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

//double ATSPeerInfo::getNearestChildLag(unsigned int dataSeq)
//{
//	if(getChildAddressByDataSeq(dataSeq)!=address){
//		// 判定是否存在序号为dataSeq的子节点
//	double leastLag=childlinklist[0]->getLag();
//		for(unsigned int i=0;i<childlinklist.size();i++){
//			if(childlinklist[i]->getDataSeq()==dataSeq){
//				if(childlinklist[i]<leastLag)
//				leastLag=childlinklist[i]->getLag();
//			}
//			return leastLag;
//		}
//	}else{
//		return -1;
//	}
//}


