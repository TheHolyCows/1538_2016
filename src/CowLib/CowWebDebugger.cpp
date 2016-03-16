/*
 * CowWebDebugger.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: kchau
 */
#include <iostream>
#include "CowWebDebugger.h"
#include <time.h>
#include <WPILib.h>

namespace CowLib
{

CowWebDebugger* CowWebDebugger::m_Instance = 0;

std::mutex CowWebDebugger::m_Mutex;
std::ofstream CowWebDebugger::m_OutputFile;
std::queue<std::pair<std::string, double>> CowWebDebugger::m_BufferQueue;

CowWebDebugger::CowWebDebugger()
{
	// TODO Auto-generated constructor stub
	m_Thread = new std::thread(CowWebDebugger::Handle);
	time_t rawTime;
	struct tm *timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	char buffer[80];
	strftime(buffer, 80, "DebugLog_%h_%d_%j_%H%M.txt", timeInfo);
	m_OutputFile.open(buffer);
	std::cout << "Opened file for debugging" << std::endl;
}

CowWebDebugger::~CowWebDebugger()
{
	// TODO Auto-generated destructor stub
	m_OutputFile.close();
	m_Thread->detach();
	delete m_Thread;

}

CowWebDebugger* CowWebDebugger::GetInstance()
{
	if(m_Instance == 0)
	{
		m_Instance = new CowWebDebugger();
	}

	return m_Instance;
}

void CowWebDebugger::Handle()
{
	while(true)
	{
		//std::cout << "Test from CowWebDebugger" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		if(!m_BufferQueue.empty())
		{
			m_Mutex.lock();
			while(!m_BufferQueue.empty())
			{
				std::pair<std::string, double> toPrint = m_BufferQueue.front();

				std::string key = toPrint.first;
				double value = toPrint.second;
				m_OutputFile << Timer::GetFPGATimestamp() << " " << key << ": " << value << std::endl;
				m_BufferQueue.pop();
			}
			m_Mutex.unlock();
		}
	}
}

void CowWebDebugger::LogWarning(std::string key, double value)
{
	m_Mutex.lock();
	m_BufferQueue.push(std::pair<std::string, double>(key, value));
	m_Mutex.unlock();
}

} /* namespace CowLib */
