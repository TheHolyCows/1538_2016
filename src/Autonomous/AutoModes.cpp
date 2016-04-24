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


	//Wait for arm unlock
	m_Modes["SpyBot-Lowbar"];
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, CONSTANT("STARTING_POSITION"), 0.25));

	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_SPOOL_SHOOTER, 0, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 0.125));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -56.75, 20, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1.25));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_TURN, 0, -10, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 0.75));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -16.875, -10, CONSTANT("BATTER_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1.25));

	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_SHOOT, 0, -4.5, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.5));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_WAIT, 0, -4.5, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.25));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_TURN, 0, -45, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 0.75));

	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 52, -45, CONSTANT("BEFORE_LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 1));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 120.9375, -90, CONSTANT("BEFORE_LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 1));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 295, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 2.75));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 160, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 2.75));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 285, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 2.75));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_TURN, 0, -110, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("AUTO_INTAKE_POSITION"), 0.75));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_INTAKE, 0, -110, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 0.25));
	m_Modes["SpyBot-Lowbar"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 10, -110, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 1.5));

	m_Modes["SpyBot-Stationary"];
	m_Modes["SpyBot-Stationary"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, 0, 0.25));
	m_Modes["SpyBot-Stationary"].push_back(RobotCommand(CMD_SPOOL_SHOOTER, 0, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 0.125));
	m_Modes["SpyBot-Stationary"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -56.75, 20, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1.25));
	m_Modes["SpyBot-Stationary"].push_back(RobotCommand(CMD_TURN, 0, -10, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 0.75));
	m_Modes["SpyBot-Stationary"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -16.875, -10, CONSTANT("BATTER_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1.25));
	m_Modes["SpyBot-Stationary"].push_back(RobotCommand(CMD_SHOOT, 0, -4.5, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.5));


	m_Modes["StaticTerrain"];
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, 0, 0.25));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -24, 0, CONSTANT("BEFORE_LOW_BAR_MAX_SPEED"), CONSTANT("RESTING_POSITION"), 1));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_WAIT, -24, 0, 0, CONSTANT("RESTING_POSITION"), 0.25));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -200, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("RESTING_POSITION"), 2.5));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_ADD_ANGLE_OFFSET, 200, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 0.01));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_SPOOL_SHOOTER, 0, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 0.125));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_TURN, 0, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1.25));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1.5));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_SHOOT, 0, 0, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.5));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_WAIT, 0, 0, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.25));
	m_Modes["StaticTerrain"].push_back(RobotCommand(CMD_WAIT, 0, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 0.75));

	m_Modes["CDF"];
	m_Modes["CDF"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, 0, 0.25));
	m_Modes["CDF"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 42, 0, CONSTANT("BEFORE_LOW_BAR_MAX_SPEED"), CONSTANT("SHOVEL_THE_FRIES"), 1.875));
	m_Modes["CDF"].push_back(RobotCommand(CMD_WAIT, 42, 0, 0, CONSTANT("INTAKE_POSITION"), 1));
	m_Modes["CDF"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 200, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 2));
	m_Modes["CDF"].push_back(RobotCommand(CMD_ADD_ANGLE_OFFSET, 200, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 0.01));
	m_Modes["CDF"].push_back(RobotCommand(CMD_TURN, 0, 180, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1.25));
	m_Modes["CDF"].push_back(RobotCommand(CMD_SPOOL_SHOOTER, 0, 180, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 0.125));
	m_Modes["CDF"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 180, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1));
	m_Modes["CDF"].push_back(RobotCommand(CMD_SHOOT, 0, 180, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.5));
	m_Modes["CDF"].push_back(RobotCommand(CMD_WAIT, 0, 180, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.25));
	m_Modes["CDF"].push_back(RobotCommand(CMD_WAIT, 0, 180, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 0.75));
//182 hits right

//	m_Modes["2ball"];
//	m_Modes["2ball"].push_back(RobotCommand(CMD_SPOOL_SHOOTER, 0, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 0.125));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -56.75, 20, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1.25));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_TURN, 0, -10, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 0.75));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -16.875, -10, CONSTANT("BATTER_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 1));
//
//	m_Modes["2ball"].push_back(RobotCommand(CMD_SHOOT, 0, -4.5, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.5));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_WAIT, 0, -4.5, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.25));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_TURN, 0, -6.5, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("EDGE_FIELD"), 0.75));
//
//	m_Modes["2ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 30.9375, -6.5, CONSTANT("BATTER_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.5));
//
//	m_Modes["2ball"].push_back(RobotCommand(CMD_TURN, 0, -90, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.75));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 120.9375, -90, CONSTANT("BEFORE_LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 1.5));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 265, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 5));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_TURN, 0, -180, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.75));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 24, -180, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 5));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_TURN, 0, -90, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.75));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_INTAKE, 4, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 5));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 5));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_TURN, 0, -180, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.75));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -24, -180, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 5));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_TURN, 0, -90, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.75));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -120, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("AUTO_INTAKE_POSITION"), 5));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -265, -90, CONSTANT("LOW_BAR_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 5));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_SPOOL_SHOOTER, 0, 0, CONSTANT("DRIVE_MAX_SPEED"), CONSTANT("INTAKE_POSITION"), 0.125));
//
//	m_Modes["2ball"].push_back(RobotCommand(CMD_TURN, 0, -4.5, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.75));
//	m_Modes["2ball"].push_back(RobotCommand(CMD_SHOOT, 0, -4.5, CONSTANT("DRIVE_MAX_SPEED"),CONSTANT("EDGE_FIELD"), 0.5));
//






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
