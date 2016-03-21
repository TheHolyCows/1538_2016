//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __AUTO_MODE_CONTROLLER_H__
#define __AUTO_MODE_CONTROLLER_H__

#include <deque>
#include "../CowConstants.h"
#include "../Subsystems/BallHandler.h"

using namespace std;

typedef enum
{
	CMD_NULL = 0,
	CMD_TURN,
	CMD_DRIVE_DISTANCE,
	CMD_HOLD_DISTANCE,
	CMD_INTAKE,
	CMD_SPOOL_SHOOTER,
	CMD_SHOOT,
	CMD_RESET_DRIVE_ENCODER,
	CMD_WAIT
} e_RobotCommand;

class RobotCommand
{
public:
	
	e_RobotCommand m_Command;
	double m_EncoderCount;
	double m_Heading;
	double m_Speed;
	double m_Arm;
	double m_Timeout;
	
	RobotCommand() :
		m_Command(CMD_NULL),
		m_EncoderCount(0),
		m_Heading(0),
		m_Speed(0),
		m_Arm(0),
		m_Timeout(0)
	{
	}
	
	RobotCommand(e_RobotCommand cmd, double encoder, double heading, double speed, double arm, double timeout) :
		m_Command(cmd),
		m_EncoderCount(encoder),
		m_Heading(heading),
		m_Speed(speed),
		m_Arm(arm),
		m_Timeout(timeout)
	{
	}
};

#include "../CowRobot.h"
#include "../CowLib/CowLib.h"

class AutoModeController : public GenericController
{
private:
	Timer *m_Timer; //TODO: standardize timing
	deque<RobotCommand> m_CommandList;
	RobotCommand m_CurrentCommand;
	
	void doNothing(CowRobot *bot);

public:
	AutoModeController();
	void SetCommandList(deque<RobotCommand> list);

	void handle(CowRobot *bot);
	void reset();
};

#endif

