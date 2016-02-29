#include "OperatorController.h"
#include "Subsystems/BallHandler.h"

OperatorController::OperatorController(CowControlBoard *controlboard)
	:
	m_CB(controlboard)
{
	m_IntakeLatch = new CowLib::CowLatch();
	m_ShootLatch = new CowLib::CowLatch();
	m_SpoolShooterLatch = new CowLib::CowLatch();
	m_PtoLockLatch = new CowLib::CowLatch();
	m_PtoNeutralLatch = new CowLib::CowLatch();
	m_PtoEngageLatch = new CowLib::CowLatch();
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

		bot->GetBallHandler()->SetState(SHOOT_STAGE);
	}
	else if(!m_CB->GetOperatorButton(9))
	{
		m_ShootLatch->ResetLatch();
	}

	if(m_CB->GetOperatorButton(3))
	{
		//bot->GetShooter()->SetManualSpeed(1);
		bot->GetBallHandler()->SetState(EXHAUST);
	}

	// Turn on Shooter
	if(m_SpoolShooterLatch->Latch(m_CB->GetOperatorButton(10)))
	{
		//bot->GetShooter()->SetManualSpeed(1);
		bot->GetBallHandler()->SetShooterState(SPOOL_PID_CONTROL);
	}
	else if(!m_CB->GetOperatorButton(10))
	{
		m_SpoolShooterLatch->ResetLatch();
	}

	// Buttons to test PTO states

	// PTO Lock state
	if(m_PtoLockLatch->Latch(m_CB->GetOperatorButton(1)))
	{
		std::cout << "Setting state to PTO LOCK" << std::endl;

		bot->GetCowPTO()->SetState(LOCK);
	}
	else if(!m_CB->GetOperatorButton(1))
	{
		m_PtoLockLatch->ResetLatch();
	}

	if(m_PtoNeutralLatch->Latch(m_CB->GetOperatorButton(3)))
	{
		std::cout << "Setting state to PTO NEUTRAL" << std::endl;

		bot->GetCowPTO()->SetState(ENTER_NEUTRAL);
	}
	else if(!m_CB->GetOperatorButton(3))
	{
		m_PtoNeutralLatch->ResetLatch();
	}

	if(m_PtoEngageLatch->Latch(m_CB->GetOperatorButton(4)))
	{
		std::cout << "Setting state to PTO ENGAGE" << std::endl;

		bot->GetCowPTO()->SetState(ENGAGE);
	}
	else if(!m_CB->GetOperatorButton(4))
	{
		m_PtoEngageLatch->ResetLatch();
	}
}

