/*
 * Arm.cpp
 *
 *  Created on: Feb 14, 2016
 *      Author: kchau
 */

#include <Subsystems/Arm.h>
#include "../CowConstants.h"


Arm::Arm(uint8_t motorA, uint8_t motorB, Encoder* encoder)
	:
	m_MotorA(NULL),
	m_MotorB(NULL),
	m_Encoder(encoder),
	m_PID(NULL),
	m_Speed(0),
	m_Setpoint(0)
{
	m_MotorA = new CANTalon(motorA);
	m_MotorB = new CANTalon(motorB);

	m_MotorA->SetVoltageRampRate(CONSTANT("ARM_RAMP_RATE"));
	m_MotorB->SetVoltageRampRate(CONSTANT("ARM_RAMP_RATE"));

	m_PID = new CowLib::CowPID(CONSTANT("ARM_P"), CONSTANT("ARM_I"), CONSTANT("ARM_D"), 0);
	m_PID->SetSetpoint(0);
}

void Arm::SetManualSpeed(float speed)
{
	//m_Speed = speed;
}

void Arm::SetPosition(float position)
{
	m_Setpoint = position;
	m_PID->SetSetpoint(m_Setpoint);
}

float Arm::GetSetpoint()
{
	return m_Setpoint;
}

void Arm::Handle()
{
	if(m_MotorA && m_MotorB)
	{

		std::cout << std::dec << "Arm Position: "
				  << m_Encoder->Get()
				  << " "
				  << m_Encoder->GetRaw()
				  << std::endl;

		if(GetSetpoint() > m_Encoder->GetRaw())
		{
			m_PID->UpdatePConstant(CONSTANT("ARM_P") * CONSTANT("ARM_DOWN_PROFILE"));
		}
		else
		{
			m_PID->UpdatePConstant(CONSTANT("ARM_P"));
		}

		m_Speed = m_PID->Calculate(m_Encoder->GetRaw());
		m_Speed = CowLib::LimitMix(m_Speed, CONSTANT("ARM_MAX_SPEED"));

		if(m_PID->OnTarget(CONSTANT("ARM_TOLERANCE")))
		{
			m_PID->ResetIntegrator();
		}
		m_MotorA->Set(m_Speed);
		m_MotorB->Set(m_Speed);
	}
}

void Arm::ResetConstants()
{
	m_PID->UpdateConstants(CONSTANT("ARM_P"), CONSTANT("ARM_I"), CONSTANT("ARM_D"), 0);

	m_MotorA->SetVoltageRampRate(CONSTANT("ARM_RAMP_RATE"));
	m_MotorB->SetVoltageRampRate(CONSTANT("ARM_RAMP_RATE"));
}

void Arm::Reset()
{
	m_Speed = 0;
	//m_Setpoint = 0;
}

Arm::~Arm() {
	// TODO Auto-generated destructor stub
}
