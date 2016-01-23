/*
 * CowGyro.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: kchau
 */

#include <CowGyro.h>

namespace CowLib {

CowGyro::CowGyro() {
	m_Thread = new std::thread(CowGyro::Handle);
}

CowGyro::~CowGyro() {
	m_Thread->detach();
	delete m_Thread;
}

void CowGyro::Handle()
{
	while(true)
	{
		//std::cout << "Test from CowWebDebugger" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

float CowGyro::GetAngle()
{
	return 0;
}

} /* namespace CowLib */
