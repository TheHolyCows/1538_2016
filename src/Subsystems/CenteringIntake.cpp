/*
 * CenteringIntake.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: kchau
 */
#include <WPILib.h>
#include <Subsystems/CenteringIntake.h>

CenteringIntake::CenteringIntake(uint8_t leftMotor, uint8_t rightMotor)
 :
	m_LeftMotor(NULL),
	m_RightMotor(NULL),
	m_Speed(0)
{
	// TODO Auto-generated constructor stub
	m_LeftMotor = new CANTalon(leftMotor);
	m_RightMotor = new CANTalon(rightMotor);
}

void CenteringIntake::SetManualSpeed(float speed)
{
	m_Speed = speed;
}

void CenteringIntake::Handle()
{
	if(m_LeftMotor && m_RightMotor)
	{
		m_LeftMotor->Set(m_Speed);
		m_RightMotor->Set(-m_Speed);
	}
}

CenteringIntake::~CenteringIntake() {
	// TODO Auto-generated destructor stub
}

