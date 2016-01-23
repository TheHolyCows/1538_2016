/*
 * CowWebDebugger.h
 *
 *  Created on: Jan 21, 2016
 *      Author: kchau
 */

#ifndef SRC_COWWEBDEBUGGER_H_
#define SRC_COWWEBDEBUGGER_H_

#include <thread>


namespace CowLib {

class CowWebDebugger {
private:
	std::thread *m_Thread;
	static void Handle();
public:
	CowWebDebugger();
	virtual ~CowWebDebugger();
};

} /* namespace CowLib */

#endif /* SRC_COWWEBDEBUGGER_H_ */
