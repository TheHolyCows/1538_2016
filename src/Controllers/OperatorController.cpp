#include "OperatorController.h"
#include "Subsystems/BallHandler.h"

OperatorController::OperatorController(CowControlBoard *controlboard)
	:
	m_CB(controlboard)
{
	m_IntakeLatch = new CowLib::CowLatch();
	m_ExhaustLatch = new CowLib::CowLatch();
	m_ShootLatch = new CowLib::CowLatch();
	m_SpoolShooterLatch = new CowLib::CowLatch();
	m_PtoLockLatch = new CowLib::CowLatch();
	m_PtoNeutralLatch = new CowLib::CowLatch();
	m_PtoEngageLatch = new CowLib::CowLatch();
	m_ArmLockLatch = new CowLib::CowLatch();
	m_HangLatch = new CowLib::CowLatch();

	m_ArmOffsetIncLatch = new CowLib::CowLatch();
	m_ArmOffsetDecLatch = new CowLib::CowLatch();
	m_HangerDeployed = false;
}

void OperatorController::handle(CowRobot *bot)
{
	//printf("Controlling...\n");
	if(m_CB->GetDriveButton(1))
	{
		bot->GetArm()->SetPosition(CONSTANT("STARTING_POSITION"));
	}

	bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
						m_CB->GetSteeringX(),
						m_CB->GetSteeringButton(FAST_TURN));

	float armJoystick = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(1), 0.2) * 4;

	bot->GetArm()->SetPosition(bot->GetArm()->GetSetpoint() +
								(armJoystick));

	//Batter shot
	if(m_CB->GetOperatorButton(9))
	{
		bot->GetArm()->SetPosition(CONSTANT("BATTER_POSITION"));
	}

	if(m_CB->GetSteeringButton(4))
	{
		bot->GetArm()->SetPosition(CONSTANT("RESTING_POSITION"));
		//bot->GetArm()->RestArm();
	}

	//Batter shot
	if(m_CB->GetOperatorButton(8))
	{
		bot->GetArm()->SetPosition(CONSTANT("EDGE_FIELD"));
	}

	//10 is mid field

	if(m_CB->GetSteeringButton(3))
	{
		bot->GetArm()->SetPosition(CONSTANT("SHOVEL_THE_FRIES"));
	}

	//Batter shot
	if(m_CB->GetSteeringButton(2))
	{
		bot->GetArm()->SetPosition(CONSTANT("INTAKE_POSITION"));
	}

	if(m_HangLatch->Latch(!m_CB->GetOperatorButton(6)))
	{
		std::cout << "Setting state to HANG DEPLOY" << std::endl;
		m_HangerDeployed = true;
		bot->GetArm()->SetPosition(CONSTANT("HANGING_POSITION"));
	}
	else if(m_CB->GetOperatorButton(6))
	{
		if(m_HangerDeployed)
		{
			bot->GetArm()->SetPosition(CONSTANT("BATTER_POSITION"));
		}
		m_HangLatch->ResetLatch();
	}

	if(m_HangerDeployed)
	{
		bot->DeployHangar(true);
	}


	// Intake
	if(m_IntakeLatch->Latch(m_CB->GetOperatorButton(4)))
	{
		std::cout << "Setting state to INTAKE" << std::endl;

		bot->GetBallHandler()->SetState(INTAKE);
	}
	else if(!m_CB->GetOperatorButton(4))
	{
		m_IntakeLatch->ResetLatch();
	}

	if(m_ShootLatch->Latch(m_CB->GetOperatorButton(5)))
	{
		std::cout << "Setting state to SHOOT_STAGE" << std::endl;
		std::cout << "ASP: " << bot->GetArm()->GetSetpoint() << std::endl;
		bot->GetBallHandler()->SetState(SHOOT_STAGE);
	}
	else if(!m_CB->GetOperatorButton(5))
	{
		m_ShootLatch->ResetLatch();
	}

	if(m_ExhaustLatch->Latch(m_CB->GetOperatorButton(7)))
	{
		//bot->GetShooter()->SetManualSpeed(1);
		std::cout << "Setting state to EXHAUST" << std::endl;
		bot->GetBallHandler()->SetState(EXHAUST);
		bot->GetBallHandler()->SetShooterState(MANUAL_CONTROL);
	}
	else if(!m_CB->GetOperatorButton(7))
	{
		m_ExhaustLatch->ResetLatch();
	}

	// Turn on Shooter
	if(m_SpoolShooterLatch->Latch(!m_CB->GetOperatorButton(1)))
	{
		std::cout << "Setting state to SPOOL_PID_CONTROL" << std::endl;
		if(m_HangerDeployed)
		{
			bot->GetBallHandler()->SetShooterState(HANG_SPOOL_PID_CONTROL);
		}
		else
		{
			bot->GetBallHandler()->SetShooterState(SPOOL_PID_CONTROL);
		}
	}
	else if(m_CB->GetOperatorButton(1))
	{
		m_SpoolShooterLatch->ResetLatch();
	}

	if(m_CB->GetSteeringButton(8) && m_HangerDeployed)
	{
		bot->GetCowPTO()->SetState(ENGAGE);
	}
	else
	{
		bot->GetCowPTO()->SetState(LOCK);

	}


	if(m_ArmLockLatch->Latch(m_CB->GetOperatorButton(3)))
	{
		bool armLockState = bot->GetArm()->GetLockState();

		bot->GetArm()->SetLockState(!armLockState);
	}
	else if(!m_CB->GetOperatorButton(3))
	{
		m_ArmLockLatch->ResetLatch();
	}

	if(m_ArmOffsetIncLatch->Latch(m_CB->GetSteeringButton(10)))
	{
		//Increment Offset
		bot->GetArm()->AddUserOffset(-15);
	}
	else if(!m_CB->GetSteeringButton(10))
	{
		m_ArmOffsetIncLatch->ResetLatch();
	}

	if(m_ArmOffsetDecLatch->Latch(m_CB->GetSteeringButton(12)))
	{
		//Decrement Offset
		bot->GetArm()->AddUserOffset(15);
	}
	else if(!m_CB->GetSteeringButton(12))
	{
		m_ArmOffsetDecLatch->ResetLatch();
	}
}

