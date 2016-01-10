//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __AUTO_MODE_CONTROLLER_H__
#define __AUTO_MODE_CONTROLLER_H__

#include <deque>
#include "../CowConstants.h"

using namespace std;

typedef enum
{
	CMD_NULL = 0,
	CMD_TURN,
	CMD_TURN_WITH_TOTE,
	CMD_DRIVE_DISTANCE,
	CMD_HOLD_DISTANCE,
	CMD_WAIT
} e_RobotCommand;

typedef enum
{
	PINCH = 0,
	GRAB
} e_PincherMode;

class RobotCommand
{
public:
	
	e_RobotCommand m_Command;
	double m_EncoderCount;
	double m_Heading;
	double m_VerticalPosition;
	e_PincherMode m_PincherMode;
	double m_PincherPosition;
	double m_IntakeSpeed;
	bool m_CanBurglar;
	double m_Timeout;
	
	RobotCommand() :
		m_Command(CMD_NULL),
		m_EncoderCount(0),
		m_Heading(0),
		m_VerticalPosition(0),
		m_PincherMode(PINCH),
		m_PincherPosition(0),
		m_IntakeSpeed(0),
		m_CanBurglar(false),
		m_Timeout(0)
	{
	}
	
	RobotCommand(e_RobotCommand cmd, double encoder,
				double heading, double verticalPos, e_PincherMode pinchMode, double pincherPos, double intakeSpeed, bool canBurglar, double timeout) :
		m_Command(cmd),
		m_EncoderCount(encoder),
		m_Heading(heading),
		m_VerticalPosition(verticalPos),
		m_PincherMode(pinchMode),
		m_PincherPosition(pincherPos),
		m_IntakeSpeed(intakeSpeed),
		m_CanBurglar(canBurglar),
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

