/*
 * Shooter.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: kchau
 */

#include <Subsystems/Shooter.h>

Shooter::Shooter(uint8_t motorA, uint8_t motorB)
:
	m_MotorA(0),
	m_MotorB(0),
	m_Speed(0)
{
	m_MotorA = new CANTalon(motorA);
	m_MotorB = new CANTalon(motorB);
}

void Shooter::SetManualSpeed(float speed)
{
	m_Speed = speed;
}

void Shooter::Handle()
{
	if(m_MotorA && m_MotorB)
	{
		m_MotorA->Set(m_Speed);
		m_MotorB->Set(m_Speed);
	}
}

Shooter::~Shooter() {
	// TODO Auto-generated destructor stub
}

