/*
 * Intake.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: kchau
 */

#include <Subsystems/Intake.h>

Intake::Intake(uint8_t motorA, uint8_t motorB)
	:
	m_MotorA(0),
	m_MotorB(0),
	m_Speed(0),
	m_AutoIntake(false),
	m_BackoffCounts(0)
{
	m_MotorA = new CANTalon(motorA);
	m_MotorB = new CANTalon(motorB);
}

void Intake::SetManualSpeed(float speed)
{
	m_Speed = speed;
}

void Intake::AutoIntakeAndDrop()
{
	m_AutoIntake = true;
}

bool Intake::IsInAutoMode()
{
	return m_AutoIntake;
}

void Intake::Handle()
{
	if(m_MotorA && m_MotorB)
	{
		m_MotorA->Set(-m_Speed);
		m_MotorB->Set(-m_Speed);
	}
}

double Intake::GetWatts()
{
	float amps = (m_MotorA->GetOutputCurrent() +
					m_MotorB->GetOutputCurrent())/2.0;
	float volts = (m_MotorA->GetOutputVoltage() +
					m_MotorB->GetOutputVoltage()) / 2.0;
	return (amps * volts);
}

Intake::~Intake() {
	// TODO Auto-generated destructor stub
}

