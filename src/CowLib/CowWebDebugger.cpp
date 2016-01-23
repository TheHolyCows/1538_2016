/*
 * CowWebDebugger.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: kchau
 */
#include <iostream>
#include "CowWebDebugger.h"

namespace CowLib {

CowWebDebugger::CowWebDebugger() {
	// TODO Auto-generated constructor stub
	m_Thread = new std::thread(CowWebDebugger::Handle);
}

CowWebDebugger::~CowWebDebugger() {
	// TODO Auto-generated destructor stub
	m_Thread->detach();
	delete m_Thread;
}

void CowWebDebugger::Handle()
{
	while(true)
	{
		//std::cout << "Test from CowWebDebugger" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

} /* namespace CowLib */
