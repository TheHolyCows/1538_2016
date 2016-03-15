#include "AutoModes.h"
#include <WPILib.h>

AutoModes *AutoModes::m_SingletonInstance = NULL;

AutoModes *AutoModes::GetInstance()
{
	if(m_SingletonInstance == NULL)
	{
		m_SingletonInstance = new AutoModes();
	}
	return m_SingletonInstance;
}

AutoModes::AutoModes()
{	
	// Set up our selection order

	m_Modes["Nothing"];
	m_Modes["Nothing"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0));


	m_Modes["SpyBot"];
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -40.36, 0, 2));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -35, -5, 0.5));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -5, -10, 0.5));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_TURN, 0, -90, 1));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 216, -90, 2));







	m_Iterator = m_Modes.begin();
}

std::deque<RobotCommand> AutoModes::GetCommandList()
{
	return m_Iterator->second;
}

const char *AutoModes::GetName()
{
	return m_Iterator->first;
}

void AutoModes::NextMode()
{
	++m_Iterator;
	if(m_Iterator == m_Modes.end())
	{
		m_Iterator = m_Modes.begin();
	}
	std::string str(GetName());
	std::string temp = "Auto mode: " + str;
	DriverStation::GetInstance().ReportError(temp);
}
