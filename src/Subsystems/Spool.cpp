#include "Spool.h"
#include <iostream>
#include "../CowConstants.h"


Spool::Spool(std::string name, uint8_t motorAID, uint8_t motorBID, uint8_t encA, uint8_t encB, bool reversePID)
	:
	m_Name(name),
	m_MotorA(new CANTalon(motorAID)),
	m_MotorB(new CANTalon(motorBID)),
	m_Encoder(new Encoder(encA, encB, true, Encoder::k1X)),
	m_PIDEnabled(true),
	m_SetPoint(0),
	m_PIDOutput(0),
	m_PID_P(0),
	m_PID_D(0),
	m_PID_P_Previous(0),
	m_ManualSpeed(0),
	m_ReversePID(reversePID)
{
	m_Encoder->SetDistancePerPulse(0.01745327777778);
}

Spool::Spool(std::string name, uint8_t motorAID, uint8_t encA, uint8_t encB, bool reversePID)
	:
	m_Name(name),
	m_MotorA(new CANTalon(motorAID)),
	m_MotorB(NULL),
	m_Encoder(new Encoder(encA, encB, true, Encoder::k1X)),
	m_PIDEnabled(true),
	m_SetPoint(0),
	m_PIDOutput(0),
	m_PID_P(0),
	m_PID_D(0),
	m_PID_P_Previous(0),
	m_ManualSpeed(0),
	m_ReversePID(reversePID)
{
	m_Encoder->SetDistancePerPulse(0.01745327777778);
}

Spool::~Spool()
{
	if(m_MotorA)
	{
		delete m_MotorA;
	}

	if(m_MotorB)
	{
		delete m_MotorB;
	}

	if(m_Encoder)
	{
		delete m_Encoder;
	}
}

void Spool::handle()
{
	std::string PID_P_CONSTANT = m_Name + "_PID_P";
	std::string PID_D_CONSTANT = m_Name + "_PID_D";
	std::string RESET_CURRENT_CONSTANT = m_Name + "_RESET_CURRENT";

	//PID Calculations

	m_PID_P = m_SetPoint - m_Encoder->GetDistance();
	m_PID_D = m_PID_P - m_PID_P_Previous;
	m_PID_P_Previous = m_PID_P;

	//Let gravity take the wheel
	if(m_SetPoint > m_Encoder->GetDistance())
	{
		m_PID_P *= 0.38;
	}

	m_PIDOutput = (m_PID_P * CONSTANT(PID_P_CONSTANT.c_str()) + (m_PID_D * CONSTANT(PID_D_CONSTANT.c_str())));


	if(m_Encoder->GetDistance() > -3)
	{
		float avgCurrent = m_MotorA->GetOutputCurrent();
		float avgVoltage = m_MotorA->GetOutputVoltage();
		if(m_MotorB)
		{
			avgCurrent += m_MotorB->GetOutputCurrent();
			avgVoltage += m_MotorB->GetOutputVoltage();
			avgCurrent /= 2.0;
			avgVoltage /= 2.0;
		}

		if(avgCurrent > CONSTANT(RESET_CURRENT_CONSTANT.c_str()) &&
		   avgVoltage < 0.0)
		{
			m_Encoder->Reset();
			//m_SetPoint = 0;
			std::cout << "RESET ENCODER FOR " << m_Name << std::endl;
		}

		//std::cout << m_Name << " OUTPUTCURRENT:      C:" << avgCurrent << " V: " << avgVoltage << std::endl;
	}

	if(m_ReversePID)
	{
		m_PIDOutput = -m_PIDOutput;
	}

	if(m_PIDEnabled)
	{
		m_MotorA->Set(m_PIDOutput);

		if(m_MotorB)
		{
			m_MotorB->Set(m_PIDOutput);
		}
	}
	else
	{
		m_MotorA->Set(m_ManualSpeed);
		if(m_MotorB)
		{
			m_MotorB->Set(m_ManualSpeed);
		}
	}
}

void Spool::UpdateSetPoint(float setpoint)
{
	if(setpoint <= CONSTANT("VERTICAL_MAX"))
	{
		setpoint = CONSTANT("VERTICAL_MAX");
	}
	else if(setpoint >= 0)
	{
		setpoint = 0;
	}

	m_SetPoint = setpoint;
}

void Spool::UpdateManualSpeeds(float speeds)
{
	m_ManualSpeed = speeds;
}

void Spool::EnablePID()
{
	m_PIDEnabled = true;
}

void Spool::DisablePID()
{
	m_PIDEnabled = false;
}

float Spool::GetPosition()
{
	return m_SetPoint;
}

void Spool::Reset()
{
	m_Encoder->Reset();
}
