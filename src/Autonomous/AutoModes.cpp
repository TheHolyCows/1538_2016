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

	m_Modes["Can Burglar!"];
	m_Modes["Can Burglar!"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, PINCH, 0, 0, true, 0.545));
	m_Modes["Can Burglar!"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 100, 0, 0, PINCH, 0, 0, true, 2));
	m_Modes["Can Burglar!"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, PINCH, 0, 0, false, 1));
	m_Modes["Can Burglar!"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 24, 0, 0, PINCH, 0, 0, false, 2));

	m_Modes["Nothing"];
	m_Modes["Nothing"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, PINCH, CONSTANT("PINCHER_CAN"), 0, false, 1));


	m_Modes["Two Can"];
	m_Modes["Two Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, PINCH, CONSTANT("PINCHER_CAN"), 0, false, 0.1875));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.1875));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.125));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_TURN, 0, 90, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.5));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 70, 90, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.45));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 30, 100, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.45));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 30, 120, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.45));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 60, 150, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.45));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_WAIT, 0, 150, 0, GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.375));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_WAIT, 0, 150, 0, PINCH, 0, 0, false, 0.375));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 150, 0, PINCH, 0, 0, false, 0.5));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_TURN, 0, 0, 0, PINCH, 0, 0, false, 0.5));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 36, 0, 0, PINCH, 0, -1, false, 1.5));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, PINCH, CONSTANT("PINCHER_CAN"), -1, false, 0.625));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), -1, false, 0.625));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -90, 0, CONSTANT("VERTICAL_BASE_TOTE"), PINCH, CONSTANT("PINCHER_CAN"), -1, false, 1.5));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.375));
	m_Modes["Two Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, PINCH, 0, 0, false, 0.375));


	m_Modes["Three Can"];
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, PINCH, CONSTANT("PINCHER_CAN"), 0, false, 0.1875));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.1875));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.125));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_TURN, 0, 90, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.5));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 70, 90, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.45));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 30, 100, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.45));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 30, 120, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.45));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 60, 150, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.45));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, 150, 0, GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.375));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, 150, 0, PINCH, 0, 0, false, 0.375));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -40, 150, 0, PINCH, 0, 0, false, 0.5));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_TURN, 0, 0, 0, PINCH, 0, 0, false, 0.5));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 45, 0, 0, PINCH, CONSTANT("PINCHER_CAN"), -1, false, 0.625));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), -1, false, 0.375));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), -0.5, false, 0.375));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_TURN, 0, -180, CONSTANT("VERTICAL_BASE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), -0.5, false, 1));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 65, -180, CONSTANT("VERTICAL_BASE_TOTE"),  GRAB, CONSTANT("PINCHER_CAN"), 0, false, 1));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, -180, 0, GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.375));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, -180, 0, PINCH, 0, 0, false, 0.375));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -72, -180, 0, PINCH, 0, 0, false, 1));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_TURN, 0, -90, 0, PINCH, 0, 0, false, 1));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 130, -90, 0, PINCH, CONSTANT("PINCHER_CAN"), -1, false, 1.5));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_TURN, 0, -180, CONSTANT("VERTICAL_BASE_TOTE") - 3, GRAB, CONSTANT("PINCHER_CAN"), -0.5, false, 1));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 60, -180, CONSTANT("VERTICAL_BASE_TOTE") - 3, GRAB, CONSTANT("PINCHER_CAN"), -0.5, false, 1));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), 0, false, 0.375));
	m_Modes["Three Can"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, PINCH, 0, 0, false, 0.375));

//	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 45, 230, 0, PINCH, 0, 0, 0.75));
//	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 60, 270, 0, PINCH, 0, 0, 0.75));

//	m_Modes["Three Can"].push_back(RobotCommand(CMD_TURN, 0, 270, 0, PINCH, 0, -0.5, 1));
//	m_Modes["Three Can"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 110, 270, 0, PINCH, 0, 0, 2));






	m_Modes["Two Tote"];

	m_Modes["Two Tote"].push_back(RobotCommand(CMD_TURN, 0, -45, 0, PINCH, 0, 0, false, 0.375));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 12, -45, 0, PINCH, CONSTANT("PINCHER_CAN"), -1, false, 0.75));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -12, -45, 0, GRAB, CONSTANT("PINCHER_CAN"), -1, false, 0.75));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_TURN, 0, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), -1, false, 0.375));

	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 130, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), -0.2, false, 1.875));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -45, 0, 0, PINCH, 0, 0, false, 1));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_TURN, 0, -45, 0, PINCH, 0, 0, false, 0.375));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 22, -45, 0, PINCH, CONSTANT("PINCHER_CAN"), -1, false, 0.75));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, -45, 0, GRAB, CONSTANT("PINCHER_CAN"), -1, false, 0.75));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_TURN, 0, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), -0.2, false, 0.75));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 48.5, 0, CONSTANT("VERTICAL_ONE_TOTE"), GRAB, CONSTANT("PINCHER_CAN"), -0.2, false, 0.75));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_WAIT, 48.5, 0, CONSTANT("VERTICAL_ONE_TOTE"), PINCH, 0, 0, false, 0.6));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -5, 0, 0, PINCH, 0, 0, false, 0.5));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 10, 0, 0, PINCH, 0, 0, false, 0.5));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, PINCH, CONSTANT("PINCHER_CAN"), -1, false, 0.1875));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 80, 0, 0, GRAB, CONSTANT("PINCHER_CAN"), -0.2, false, 0.50));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_TURN_WITH_TOTE, 0, 90, 0, GRAB, CONSTANT("PINCHER_CAN"), -0.2, false, 1));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 90, 90, 0, GRAB, CONSTANT("PINCHER_CAN"), -0.2, false, 0.6));
	m_Modes["Two Tote"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -70, 90, 0, PINCH, 0, 0, false, 0.6));


//	m_Modes["Default"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -170, 90, 0, PINCH, 0, 0, 1));
//	m_Modes["Default"].push_back(RobotCommand(CMD_TURN, 0, 0, 0, PINCH, 0, 0, 0.75));
//	m_Modes["Default"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -10, 0, 0, PINCH, 0, 0, 0.25));
//	m_Modes["Default"].push_back(RobotCommand(CMD_TURN, 0, -45, 0, PINCH, 0, 0, 0.75));









//	m_Modes["Default"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, 0.75));

	//dont run this for now
//	m_Modes["Default"].push_back(RobotCommand(CMD_TURN, 0, -45, 0, 0.75));
//	m_Modes["Default"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 12, -45, 0, 0.75));
//	m_Modes["Default"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -12, -45, 0, 0.75));
//	m_Modes["Default"].push_back(RobotCommand(CMD_TURN, 0, 90, CONSTANT("VERTICAL_TWO_TOTE"), 0.75));
//	m_Modes["Default"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 90, 90, CONSTANT("VERTICAL_TWO_TOTE"), 1.5));
//
//	m_Modes["Default"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, 5));
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
