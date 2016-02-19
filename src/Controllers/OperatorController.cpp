#include "OperatorController.h"
#include "Subsystems/BallHandler.h"

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

	// Intake
	if(m_CB->GetOperatorButton(5))
	{
		//bot->GetIntake()->SetManualSpeed(1);
		//bot->GetCenteringIntake()->SetManualSpeed(1);

		if(bot->GetBallHandler()->GetState() == SPOOL_SHOOTER)
		{
			bot->GetBallHandler()->SetState(SHOOT);
		}
		else
		{
			bot->GetBallHandler()->SetState(INTAKE);
		}
	}

	// Turn on Shooter
	if((bot->GetBallHandler()->GetState() >= BALL_AND_WAIT) && (m_CB->GetOperatorButton(10)))
	{
		//bot->GetShooter()->SetManualSpeed(1);
		bot->GetBallHandler()->SetState(SPOOL_SHOOTER);
	}
	else if(!m_CB->GetOperatorButton(10))
	{
		bot->GetBallHandler()->SetState(NO_BALL_AND_WAIT);
	}

}

