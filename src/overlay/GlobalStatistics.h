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

#ifndef __FANJING_GLOBALSTATISTICS_H_
#define __FANJING_GLOBALSTATISTICS_H_

#include <map>
#include <list>
#include <string>
#include <stdarg.h>
#include "ctime"
#include <fstream>
#include <iostream>
#include <sstream>
#include "GlobalStatisticsUnit.h"

namespace Fanjing {
typedef std::list<GlobalStatisticsUnit*> GlobalStatisticsList;
typedef std::map<string, GlobalStatisticsList*> GlobalStatisticsMap;
/**
 *
 * usage:
 *  gs.changeName(name)<<value0<<value1<<...<<valueN<<gs.endl;
 *  or
 *  gs.changeName(name);
 *  gs.get()<<value0;
 *  gs.get()<<value1;
 *  ...
 *  gs.get()<<valueN;
 *  gs.get()<<gs.endl;
 */

class GlobalStatistics {
public:
    static GlobalStatistics * request();
    static void release();
public:
	typedef void* gs_eofType;
public:
	GlobalStatistics& operator<<(gs_eofType& e);
	GlobalStatistics& operator<<(double num);
	GlobalStatistics& operator<<(int num);
	GlobalStatistics& operator<<(string str);
	GlobalStatistics& changeName(string name);
    GlobalStatistics& get();

	void output(string name);
	void eof();
	void clean();
	virtual void initialize();
	virtual void finish();
public:
	static gs_eofType endl;
	GlobalStatisticsMap globalStatisticsMap;
	std::list<GlobalStatisticsUnit::DataUnit> unitData;
	string m_name;
private:
	static GlobalStatistics* ptr_singleton;
    GlobalStatistics();
    virtual ~GlobalStatistics();
};


}  // namespace Fanjing
#endif
