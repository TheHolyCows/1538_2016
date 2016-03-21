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
	m_Modes["Nothing"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, 0, 0));


	m_Modes["SpyBot"];
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_SPOOL_SHOOTER, 0, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 0.125));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -40.36, 20, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1.25));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_TURN, 0, -10, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 0.75));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -12, -10, CONSTANT("BATTER_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1));

	m_Modes["SpyBot"].push_back(RobotCommand(CMD_SHOOT, 0, -4.5, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.5));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_WAIT, 0, -4.5, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.25));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_TURN, 0, -6.5, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 0.75));

	m_Modes["SpyBot"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 22, -6.5, CONSTANT("BATTER_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.5));

	m_Modes["SpyBot"].push_back(RobotCommand(CMD_TURN, 0, -90, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 1));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 86, -90, CONSTANT("BEFORE_LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 1.5));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 195, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 5));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 86, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 10));
	m_Modes["SpyBot"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 195, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 5));








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
