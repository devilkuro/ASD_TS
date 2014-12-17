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

#include "ATSLink.h"

unsigned int ATSLink::getDataSeq() const {
	return dataSeq;
}

double ATSLink::getLag() const {
	return lag;
}

TransportAddress ATSLink::getTargetAddress() const {
	return targetAddress;
}

ATSLinkState ATSLink::getState() const {
    return state;
}
void ATSLink::setDataSeq(unsigned int dataSeq) {
	this->dataSeq = dataSeq;
}

void ATSLink::setLag(double lag) {
	this->lag = lag;
}

void ATSLink::setTargetAddress(TransportAddress targetAddress) {
	this->targetAddress = targetAddress;
}

TransportAddress ATSLink::getLinkOwnerAddress() const
{
	return targetAddress;
}

void ATSLink::setSelfAddress(TransportAddress selfAddress)
{
	this->selfAddress=selfAddress;
}

void ATSLink::setState(ATSLinkState state){
    this->state = state;
}
ATSLink::ATSLink() {
	// TODO Auto-generated constructor stub
    refreshFlag = false;
}

ATSLink::~ATSLink() {
	// TODO Auto-generated destructor stub
}
