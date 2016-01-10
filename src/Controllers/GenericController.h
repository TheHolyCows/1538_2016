//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __GENERIC_CONTROLLER_H__
#define __GENERIC_CONTROLLER_H__

#include <WPILib.h>

class CowRobot;

class GenericController
{	
public:
	virtual ~GenericController() {};
	virtual void handle(CowRobot *bot) = 0;
};

#endif
