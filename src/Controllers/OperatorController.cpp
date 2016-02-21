#include "OperatorController.h"
#include "Subsystems/BallHandler.h"

OperatorController::OperatorController(CowControlBoard *controlboard)
	:
	m_CB(controlboard)
{
	m_IntakeLatch = new CowLib::CowLatch();
	m_ShootLatch = new CowLib::CowLatch();
	m_SpoolShooterLatch = new CowLib::CowLatch();
}

void OperatorController::handle(CowRobot *bot)
{
	//printf("Controlling...\n");
	bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
						m_CB->GetSteeringX(),
						m_CB->GetSteeringButton(FAST_TURN));
	float armJoystick = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(1), 0.2) * 4;

	bot->GetArm()->SetPosition(bot->GetArm()->GetSetpoint() +
								(armJoystick));

	//Batter shot
	if(m_CB->GetOperatorButton(2))
	{
		bot->GetArm()->SetPosition(CONSTANT("BATTER_POSITION"));
	}

	//Batter shot
	if(m_CB->GetOperatorButton(7))
	{
		bot->GetArm()->SetPosition(CONSTANT("EDGE_FIELD"));
	}

	if(m_CB->GetSteeringButton(3))
	{
		bot->GetArm()->SetPosition(CONSTANT("SHOVEL_THE_FRIES"));
	}

	//Batter shot
	if(m_CB->GetSteeringButton(2))
	{
		bot->GetArm()->SetPosition(CONSTANT("INTAKE_POSITION"));
	}



	// Intake
	if(m_IntakeLatch->Latch(m_CB->GetOperatorButton(5)))
	{
		std::cout << "Setting state on intake button " << std::endl;

		bot->GetBallHandler()->SetState(INTAKE);
	}
	else if(!m_CB->GetOperatorButton(5))
	{
		m_IntakeLatch->ResetLatch();
	}

	if(m_ShootLatch->Latch(m_CB->GetOperatorButton(9)))
	{
		std::cout << "Setting state on shoot button " << std::endl;

		bot->GetBallHandler()->SetState(SHOOT);
	}
	else if(!m_CB->GetOperatorButton(9))
	{
		m_ShootLatch->ResetLatch();
	}

	// Turn on Shooter
	if(m_SpoolShooterLatch->Latch((bot->GetBallHandler()->GetState() >= BALL_AND_WAIT) && (m_CB->GetOperatorButton(10))))
	{
		//bot->GetShooter()->SetManualSpeed(1);
		bot->GetBallHandler()->SetState(SPOOL_SHOOTER);
	}
	else if(!m_CB->GetOperatorButton(10) && bot->GetBallHandler()->GetState() == SHOOT)
	{
		bot->GetBallHandler()->SetState(NO_BALL_AND_WAIT);
		m_SpoolShooterLatch->ResetLatch();
	}

}

