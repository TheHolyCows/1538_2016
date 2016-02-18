#include "OperatorController.h"

OperatorController::OperatorController(CowControlBoard *controlboard)
	:
	m_CB(controlboard)
{
}

void OperatorController::handle(CowRobot *bot)
{
	//printf("Controlling...\n");
	bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
						m_CB->GetSteeringX(),
						m_CB->GetSteeringButton(FAST_TURN));
	float armJoystick = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(1), 0.2) * 1.5;

	bot->GetArm()->SetManualSpeed(armJoystick);

	if(m_CB->GetOperatorButton(5))
	{
		bot->GetIntake()->SetManualSpeed(1);
		bot->GetCenteringIntake()->SetManualSpeed(1);
	}
	else
	{
		if(!bot->GetIntake()->IsInAutoMode())
		{
			bot->GetIntake()->SetManualSpeed(0);
		}
		bot->GetCenteringIntake()->SetManualSpeed(0);
	}

	if(m_CB->GetOperatorButton(10))
	{
		bot->GetShooter()->SetManualSpeed(1);
	}
	else if(m_CB->GetOperatorButton(9))
	{
		bot->GetShooter()->SetManualSpeed(-0.5);
		bot->GetIntake()->SetManualSpeed(-1);
	}
	else
	{
		bot->GetShooter()->SetManualSpeed(0);
	}

}

