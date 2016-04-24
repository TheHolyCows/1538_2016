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
	m_Flashlight(NULL),
	m_Encoder(encoder),
	m_PID(NULL),
	m_UnlockSolenoid(NULL),
	m_LockSolenoid(NULL),
	m_LockedState(false),
	m_StartUnlock(false),
	m_Speed(0),
	m_Setpoint(0),
	m_OffsetPosition(false),
	m_UserOffsetPosition(0),
	m_UnlockTime(0)
{
	m_MotorA = new CANTalon(motorA);
	m_MotorB = new CANTalon(motorB);
	m_Flashlight = new CANTalon(FLASHLIGHT);
	m_Flashlight->SetControlMode(CANTalon::kVoltage);
	//m_Flashlight->SetVoltageCompensationRampRate(24.0);


	m_MotorA->SetVoltageRampRate(CONSTANT("ARM_RAMP_RATE"));
	m_MotorB->SetVoltageRampRate(CONSTANT("ARM_RAMP_RATE"));

	m_PID = new CowLib::CowPID(CONSTANT("ARM_P"), CONSTANT("ARM_I"), CONSTANT("ARM_D"), 0);
	m_PID->SetSetpoint(0);

	m_LockSolenoid = new Solenoid(SOLENOID_LOCK);
	m_UnlockSolenoid = new Solenoid(SOLENOID_UNLOCK);
}

void Arm::AddUserOffset(float offset)
{
	m_UserOffsetPosition += offset;
	std::cout << "User offset now: " << m_UserOffsetPosition << std::endl;
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

void Arm::SetLockState(bool state)
{
	if(state)
	{
		m_LockedState = true;
		m_UnlockTime = 0;
	}
	else
	{
		m_StartUnlock = true;
		m_UnlockTime = Timer::GetFPGATimestamp();
	}
}

bool Arm::GetLockState()
{
	return m_LockedState;
}

void Arm::UseOffsetPosition()
{
	m_OffsetPosition = true;
}

void Arm::Handle()
{
	if(m_MotorA && m_MotorB)
	{
		if(m_StartUnlock)
		{
			m_UnlockSolenoid->Set(true);
			m_LockSolenoid->Set(false);

			m_Speed = 0;

			if((Timer::GetFPGATimestamp() - m_UnlockTime) > 0.25 && m_LockedState)
			{
				m_LockedState = false;
				m_StartUnlock = false;
			}
		}

		if(GetSetpoint() == CONSTANT("BATTER_POSITION") ||
			GetSetpoint() == CONSTANT("EDGE_FIELD"))
		{
			m_Flashlight->Set(CONSTANT("LIGHT_VOLTAGE"));
		}
		else
		{
			m_Flashlight->Set(0);
		}

		double encoderPosition = m_Encoder->GetRaw();

		if(m_OffsetPosition)
		{
			encoderPosition += CONSTANT("STARTING_POSITION");
		}

		encoderPosition += m_UserOffsetPosition;

//		std::cout << std::dec << "Arm Position: "
//				  << encoderPosition
//				  << std::endl;

		if(GetSetpoint() > encoderPosition)
		{
			m_PID->UpdatePConstant(CONSTANT("ARM_P") * CONSTANT("ARM_DOWN_PROFILE"));
		}
		else
		{
			m_PID->UpdatePConstant(CONSTANT("ARM_P"));
		}

		m_Speed = m_PID->Calculate(encoderPosition);
		m_Speed = CowLib::LimitMix(m_Speed, CONSTANT("ARM_MAX_SPEED"));

		if(m_PID->OnTarget(CONSTANT("ARM_TOLERANCE")))
		{
			m_PID->ResetIntegrator();
		}


		if(m_LockedState)
		{
			m_UnlockSolenoid->Set(false);
			m_LockSolenoid->Set(true);
			m_Speed = 0;
		}
		else
		{
			m_UnlockSolenoid->Set(true);
			m_LockSolenoid->Set(false);
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
	m_LockedState = false;
	//m_Setpoint = 0;
}

Arm::~Arm() {
	// TODO Auto-generated destructor stub
}
