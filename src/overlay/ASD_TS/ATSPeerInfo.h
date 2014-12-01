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

#ifndef ATSPEERINFO_H_
#define ATSPEERINFO_H_

#include <vector>

#include "TransportAddress.h"
#include "ATSLink.h"

class ATSPeerInfo
{
private:
	TransportAddress address;
	unsigned int freeResource;
	double lag;
	//Only used by Server Node
	bool isJoined;

public:
    std::vector<ATSLink*> parentlinklist;
    std::vector<ATSLink*> childlinklist;
    std::vector<double> dataTimeStamp;         //数据到达该节点的时间戳
    std::vector<unsigned int> ChildNum_dataSeq;//存储孩子节点数量

public:
	ATSPeerInfo();
	virtual ~ATSPeerInfo();

	unsigned int getFreeResource() const;
    void setFreeResource(unsigned int freeResource);
    TransportAddress getAddress() const;
    void setAddress(TransportAddress address);
    double getLag() const;
    void setLag(double lag);
    bool getIsJoined() const;
    void setIsJoined(bool isJoined);

    double getJoinScoreByDataSeq(unsigned int dataSeq);
    double getSwitchScoreByDataSeq(unsigned int dataSeq1, unsigned int dataSeq2,unsigned int parentChildNum1,unsigned int parentChildNum2);
    double getInsertScoreByDataSeq(unsigned int dataSeq);
    double getDataRatioByDataSeq(unsigned int dataSeq);
    double getDataScoreByDataSeq(unsigned int dataSeq);

    TransportAddress getChildAddressByDataSeq(unsigned int dataSeq);
    unsigned int getChildIndexByDataSeq(unsigned int dataSeq);

};

#endif /* ATSPEERINFO_H_ */
