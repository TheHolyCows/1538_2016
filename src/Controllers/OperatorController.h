//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __OPERATOR_CONTROLLER_H__
#define __OPERATOR_CONTROLLER_H__

#include <math.h>
#include <WPILib.h>
#include "../CowRobot.h"
#include "../CowControlBoard.h"
#include "../CowLib/CowLib.h"
#include "../Declarations.h"
#include "../CowConstants.h"
#include "../CowLib/CowLatch.h"

class OperatorController : public GenericController
{	
private:
	OperatorController();
	CowControlBoard *m_CB;

	CowLib::CowLatch *m_IntakeLatch;
	CowLib::CowLatch *m_ShootLatch;
	CowLib::CowLatch *m_SpoolShooterLatch;

public:
	OperatorController(CowControlBoard *controlboard);
	void handle(CowRobot *bot);
};

#endif
