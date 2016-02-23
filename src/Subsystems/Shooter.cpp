/*
 * Shooter.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: kchau
 */

#include <Subsystems/Shooter.h>
#include "../CowConstants.h"
#include <cmath>


Shooter::Shooter(uint8_t motorA, uint8_t motorB, Encoder* encoderA, Encoder* encoderB)
:
	m_MotorA(0),
	m_MotorB(0),
	m_Speed(0),
	m_EncoderA(encoderA),
	m_EncoderB(encoderB),
	m_PIDEnabled(false)
{
	m_MotorA = new CANTalon(motorA);
	m_MotorB = new CANTalon(motorB);
	m_PID_A = new CowLib::CowPID(CONSTANT("SHOOTER_A_P"), CONSTANT("SHOOTER_A_I"), CONSTANT("SHOOTER_A_D"), CONSTANT("SHOOTER_A_F"));
	m_PID_B = new CowLib::CowPID(CONSTANT("SHOOTER_B_P"), CONSTANT("SHOOTER_B_I"), CONSTANT("SHOOTER_B_D"), CONSTANT("SHOOTER_B_F"));

}

void Shooter::SetManualSpeed(float speed)
{
	m_Speed = speed;
}

void Shooter::SetAutoSpeed(float speed)
{
	m_PID_A->SetSetpoint(speed);
	m_PID_B->SetSetpoint(speed);
}

void Shooter::SetPIDState(bool state)
{
	m_PIDEnabled = state;
}

bool Shooter::HasShotBall()
{
	if(m_PID_A->GetSetpoint() > 0)
	{
		if(fabs(m_PID_A->GetError()) > 500 && m_PIDEnabled)
		{
			return true;
		}
	}
	return false;

}

void Shooter::ResetConstants()
{
	m_PID_A->UpdateConstants(CONSTANT("SHOOTER_A_P"), CONSTANT("SHOOTER_A_I"), CONSTANT("SHOOTER_A_D"), CONSTANT("SHOOTER_A_F"));
	m_PID_B->UpdateConstants(CONSTANT("SHOOTER_B_P"), CONSTANT("SHOOTER_B_I"), CONSTANT("SHOOTER_B_D"), CONSTANT("SHOOTER_B_F"));
}

void Shooter::Handle()
{
	//(rate/360)rps
	double encoderARate = (m_EncoderA->GetRate() / 360.0) * 60.0;
	double encoderBRate = (m_EncoderB->GetRate() / 360.0) * 60.0;

	std::cout << "S1: " << encoderARate << " S2: " << encoderBRate << std::endl;

	double motorAPID = m_PID_A->Calculate(encoderARate);
	double motorBPID = m_PID_B->Calculate(encoderBRate);

	if(m_MotorA && m_MotorB)
	{
		if(m_PIDEnabled)
		{
			m_MotorA->Set(motorAPID);
			m_MotorB->Set(motorBPID);
		}
		else
		{
			m_MotorA->Set(m_Speed);
			m_MotorB->Set(m_Speed);
		}
	}
}

Shooter::~Shooter() {
	// TODO Auto-generated destructor stub
}

