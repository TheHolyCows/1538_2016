/*
 * Arm.cpp
 *
 *  Created on: Feb 14, 2016
 *      Author: kchau
 */

#include <Subsystems/Arm.h>

Arm::Arm(uint8_t motorA, uint8_t motorB)
	:
	m_MotorA(NULL),
	m_MotorB(NULL),
	m_Speed(0)
{
	m_MotorA = new CANTalon(motorA);
	m_MotorB = new CANTalon(motorB);
}

void Arm::SetManualSpeed(float speed)
{
	m_Speed = speed;
}

void Arm::Handle()
{
	if(m_MotorA && m_MotorB)
	{
		m_MotorA->Set(m_Speed);
		m_MotorB->Set(m_Speed);
	}
}

Arm::~Arm() {
	// TODO Auto-generated destructor stub
}
