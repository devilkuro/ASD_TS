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

/**
 * @file ATSLink.h
 * @author Fanjing
 * @data 2013-4-24
 * @brief ATSLink class header
 * @details This file defines a class of the link between two ATS peers.
 */

#ifndef ATSLINK_H_
#define ATSLINK_H_

#include "TransportAddress.h"

enum ATSLinkState {
	//ATSLinkState
	ATS_LINK_INIT = 0,
	//ATSLinkState
	ATS_LINK_SELECTED = 1,
	//ATSLinkState
	ATS_LINK_CONNECTED = 2
};

class ATSLink {
private:
	//the address of the target node.
	TransportAddress targetAddress;
	//the address of the owner.
	TransportAddress selfAddress;
	//the data sequence of this link.
	unsigned int dataSeq;
	//the delay between two ends of this link.
	double lag;

	ATSLinkState state;
public:

	ATSLink();
	virtual ~ATSLink();

	unsigned int getDataSeq() const;
	void setDataSeq(unsigned int dataSeq);

	double getLag() const;
	void setLag(double lag);

	TransportAddress getTargetAddress() const;
	void setTargetAddress(TransportAddress targetAddress);

	TransportAddress getLinkOwnerAddress() const;
	void setSelfAddress(TransportAddress selfAddress);

	ATSLinkState getState() const;
	void setState(ATSLinkState state);
};

#endif /* ATSLINK_H_ */
