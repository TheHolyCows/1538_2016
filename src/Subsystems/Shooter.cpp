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
	m_PIDEnabled(false),
	m_EncoderASpeed(0),
	m_EncoderBSpeed(0)
{
	m_MotorA = new CANTalon(motorA);
	m_MotorB = new CANTalon(motorB);
	m_PID_A_Rate = new CowLib::CowPID(CONSTANT("SHOOTER_A_P"), CONSTANT("SHOOTER_A_I"), CONSTANT("SHOOTER_A_D"), CONSTANT("SHOOTER_A_F"));
	m_PID_B_Rate = new CowLib::CowPID(CONSTANT("SHOOTER_B_P"), CONSTANT("SHOOTER_B_I"), CONSTANT("SHOOTER_B_D"), CONSTANT("SHOOTER_B_F"));

	m_LPF_A = new CowLib::CowLPF(CONSTANT("SHOOTER_A_BETA"));
	m_LPF_B = new CowLib::CowLPF(CONSTANT("SHOOTER_B_BETA"));
}

void Shooter::SetManualSpeed(float speed)
{
	m_Speed = speed;
}

void Shooter::SetAutoSpeed(float speedA, float speedB)
{
	m_PID_A_Rate->SetSetpoint(-speedA);
	m_PID_B_Rate->SetSetpoint(speedB);
}

void Shooter::SetPIDState(bool state)
{
	m_PIDEnabled = state;
}

bool Shooter::IsOnTarget()
{
	bool targeted = false;
	if(m_PID_A_Rate->OnTarget(CONSTANT("SHOOTER_A_TOLERANCE")) &&
			m_PID_B_Rate->OnTarget(CONSTANT("SHOOTER_B_TOLERANCE")))
	{
		targeted = true;
	}
	return targeted;
}

bool Shooter::HasShotBall()
{
	bool hasShot = false;
	if(m_PIDEnabled &&
			m_PID_A_Rate->GetSetpoint() != 0 &&
			m_PID_B_Rate->GetSetpoint() != 0 )
	{
		if(fabs(m_PID_A_Rate->GetError()) > 500)
		{
			hasShot = true;
		}
		if(fabs(m_PID_B_Rate->GetError()) > 500)
		{
			hasShot = true;
		}
	}
	return hasShot;

}

double Shooter::GetMotorASpeed()
{
	return m_EncoderASpeed;
}

double Shooter::GetMotorBSpeed()
{
	return m_EncoderBSpeed;
}


void Shooter::ResetConstants()
{
	m_PID_A_Rate->UpdateConstants(CONSTANT("SHOOTER_A_P"), CONSTANT("SHOOTER_A_I"), CONSTANT("SHOOTER_A_D"), 0);
	m_PID_B_Rate->UpdateConstants(CONSTANT("SHOOTER_B_P"), CONSTANT("SHOOTER_B_I"), CONSTANT("SHOOTER_B_D"), 0);

	m_LPF_A->UpdateBeta(CONSTANT("SHOOTER_A_BETA"));
	m_LPF_B->UpdateBeta(CONSTANT("SHOOTER_B_BETA"));

}

void Shooter::Handle()
{
	//(rate/360)rps
	m_EncoderASpeed = (m_EncoderA->GetRate() / 360.0) * 60.0;
	m_EncoderBSpeed = (m_EncoderB->GetRate() / 360.0) * 60.0;

	double robotVoltage = DriverStation::GetInstance().GetBatteryVoltage();

	double motorAPID_Rate = m_PID_A_Rate->Calculate(m_EncoderASpeed);
	double motorBPID_Rate = m_PID_B_Rate->Calculate(m_EncoderBSpeed);

	double motorAPID_Voltage = m_PID_A_Rate->GetSetpoint() * (CONSTANT("SHOOTER_MAX_VLT") / robotVoltage) * CONSTANT("SHOOTER_A_F");
	double motorBPID_Voltage = m_PID_B_Rate->GetSetpoint() * (CONSTANT("SHOOTER_MAX_VLT") / robotVoltage) * CONSTANT("SHOOTER_B_F");


	if(m_MotorA && m_MotorB)
	{
		if(m_PIDEnabled)
		{
			std::cout << "S1: " << m_EncoderASpeed << " S2: " << m_EncoderBSpeed << "VA: " << motorAPID_Voltage << " VB: " << motorBPID_Voltage << " RV: " << robotVoltage << std::endl;

			m_MotorA->Set(motorAPID_Rate + motorAPID_Voltage);
			m_MotorB->Set(motorBPID_Rate + motorBPID_Voltage);
		}
		else
		{
			m_MotorA->Set(m_Speed);
			m_MotorB->Set(m_Speed);
		}
	}
}

void Shooter::Reset()
{
	m_PIDEnabled = false;
	m_Speed = 0;
	m_EncoderASpeed = 0;
	m_EncoderBSpeed = 0;
}

Shooter::~Shooter() {
	// TODO Auto-generated destructor stub
}

