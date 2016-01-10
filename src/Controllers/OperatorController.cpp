#include "OperatorController.h"

OperatorController::OperatorController(CowControlBoard *controlboard)
	:
	m_CB(controlboard)
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
}

