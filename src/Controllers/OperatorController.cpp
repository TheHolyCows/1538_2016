#include "OperatorController.h"

OperatorController::OperatorController(CowControlBoard *controlboard)
	:
	m_CB(controlboard),
	setPinchOnce(false)
{
}

void OperatorController::handle(CowRobot *bot)
{
	//printf("Controlling...\n");
	if(m_CB->GetDriveButton(1))
	{
		bot->DriveDistanceWithHeading(0, 12);
	}
	else
	{
		bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
							m_CB->GetSteeringX(),
							m_CB->GetSteeringButton(FAST_TURN));
	}

	if(m_CB->GetSteeringButton(1))
	{
		bot->GetPincher()->ManualControl(1, 0);
		bot->GetPincher()->EnablePositionPID();
	}
	else if(m_CB->GetSteeringButton(3))
	{
		bot->GetPincher()->ManualControl(-1, 0);
		bot->GetPincher()->EnablePositionPID();
	}

	if(!m_CB->GetSteeringButton(1) && !m_CB->GetSteeringButton(3))
	{
		bot->GetPincher()->ManualControl(0, 0);
	}

	if(m_CB->GetOperatorButton(8))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_ONE_TOTE"));
	}
	else if(m_CB->GetOperatorButton(6))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_TWO_TOTE"));
	}
	else if(m_CB->GetOperatorButton(7))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_THREE_TOTE"));
	}
	else if(m_CB->GetOperatorButton(2))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_FOUR_TOTE"));
	}
	else if(m_CB->GetOperatorButton(5))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_THREE_CAN"));
	}
	if(m_CB->GetSteeringButton(2))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_BASE_TOTE"));
	}

	float vLiftJoystick = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(1), 0.2) * 1.5;
//	float hLiftJoystick = CowLib::Deadband(m_CB->GetOperatorGamepadAxis(0), 0.4) * 1.5;

	bot->GetVerticalLift()->UpdateSetPoint(bot->GetVerticalLift()->GetPosition() + vLiftJoystick);
	//bot->GetHorizontalLift()->UpdateSetPoint(bot->GetHorizontalLift()->GetPosition() + hLiftJoystick);

	if(m_CB->GetOperatorButton(3))
	{
		bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_OPEN"));
		bot->GetPincher()->EnablePositionPID();
	}
	else if(m_CB->GetOperatorButton(4))
	{
		bot->GetVerticalLift()->UpdateSetPoint(0);
		bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_CAN"));
		bot->GetPincher()->EnablePositionPID();

	}
	else if(m_CB->GetOperatorButton(9))
	{
		bot->GetVerticalLift()->UpdateSetPoint(CONSTANT("VERTICAL_HUMAN_PLAYER"));
		bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_CAN"));
		bot->GetPincher()->ManualControl(-1, 0);
		bot->GetPincher()->EnablePositionPID();
	}
	else if(m_CB->GetOperatorButton(10))
	{
		bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_CAN"));
		bot->GetPincher()->EnablePositionPID();
	}

	if(m_CB->GetOperatorButton(1))
	{
		bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_RIGHTING"));
		bot->GetPincher()->EnablePositionPID();

//		bot->GetPincher()->Spin(true);
//		bot->GetPincher()->ManualControl(-1, 0);
	}
//	else
//	{
		bot->GetPincher()->Spin(false);
	//}

	if(!m_CB->GetOperatorButton(10))
	{
		if(!setPinchOnce)
		{
			bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_OPEN"));
			bot->GetPincher()->EnablePositionPID();
			setPinchOnce = true;
		}
		bot->GetPincher()->PositionMode();
	}
	else
	{
		bot->GetPincher()->GrabMode();
		setPinchOnce = false;
	}

}

