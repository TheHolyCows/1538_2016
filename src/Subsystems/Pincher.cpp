#include "Pincher.h"
#include "../CowConstants.h"

Pincher::Pincher(unsigned int leftIntake,
		unsigned int rightIntake,
		unsigned int pincherMotorA,
		unsigned int pincherMotorB,
		unsigned int encoderA,
		unsigned int encoderB)
:
		m_IntakeSpeed(0),
		m_PincherSpeed(0),
		m_LeftIntake(new CANTalon(leftIntake)),
		m_RightIntake(new CANTalon(rightIntake)),
		m_PincherA(new CANTalon(pincherMotorA)),
		m_PincherB(new CANTalon(pincherMotorB)),
		m_Encoder(new Encoder(encoderA, encoderB, true, Encoder::k1X)),
		m_PIDEnabled(true),
		m_AtPositionTarget(false),
		m_CurrentPIDEnabled(false),
		m_SpinMode(false),

		m_SetPoint(0),
		m_PIDOutput(0),
		m_PID_P(0),
		m_PID_D(0),
		m_PID_P_Previous(0)
{

}

Pincher::~Pincher()
{
	delete m_LeftIntake;
	delete m_RightIntake;
	delete m_PincherA;
	delete m_PincherB;
	delete m_Encoder;
}

void Pincher::Reset()
{
	m_Encoder->Reset();
}

void Pincher::handle()
{
	if(m_PIDEnabled)
	{
		if(!m_CurrentPIDEnabled)
		{
			m_PID_P = m_SetPoint - m_Encoder->Get();
			m_PID_D = m_PID_P - m_PID_P_Previous;
			m_PIDOutput = (m_PID_P * CONSTANT("PINCHER_POS_P") + (m_PID_D * CONSTANT("PINCHER_POS_D")));
			m_PIDOutput = -m_PIDOutput;
			m_PID_P_Previous = m_PID_P;

//			if(fabs(m_PID_P) < 10)
//			{
//				m_AtPositionTarget = true;
//			}
//
//			if(!m_AtPositionTarget)
//			{
				if(m_IntakeSpeed != 0 && fabs(m_PID_P < 30))
				{
					m_PIDOutput = CowLib::LimitMix(m_PIDOutput, CONSTANT("PINCHER_MAX_INTAKE_CURRENT"));
				}
				m_PincherA->Set(m_PIDOutput);
				m_PincherB->Set(m_PIDOutput);
//			}
//			else
//			{
//				m_PincherA->Set(0);
//				m_PincherB->Set(0);
//			}
		}
		else
		{
			m_PID_P = m_SetPoint - GetWattage();
			m_PID_D = m_PID_P - m_PID_P_Previous;
			m_PIDOutput = (m_PID_P * CONSTANT("PINCHER_CUR_P") + (m_PID_D * CONSTANT("PINCHER_CUR_D")));
			m_PIDOutput = -m_PIDOutput;
			m_PID_P_Previous = m_PID_P;

			m_PincherA->Set(m_PIDOutput);
			m_PincherB->Set(m_PIDOutput);
		}
	}
	else
	{
		m_PincherA->Set(0);
		m_PincherB->Set(0);
	}
	if(m_SpinMode)
	{
		m_LeftIntake->Set(m_IntakeSpeed);
		m_RightIntake->Set(m_IntakeSpeed);
	}
	else
	{
		m_LeftIntake->Set(m_IntakeSpeed);
		m_RightIntake->Set(-m_IntakeSpeed);
	}

}

void Pincher::ManualControl(float intake, float pincher)
{
	m_IntakeSpeed = intake;
	m_PincherSpeed = pincher;
}

void Pincher::UpdateSetPoint(float setpoint)
{
	EnablePID();
	m_SetPoint = setpoint;
}

float Pincher::GetSetPoint()
{
	return m_SetPoint;
}

float Pincher::GetPosition()
{
	return m_Encoder->Get();
}

float Pincher::GetWattage()
{
	float avgCurrent = m_PincherA->GetOutputCurrent() + m_PincherB->GetOutputCurrent();
	avgCurrent /= 2.0;

	float avgVolts = m_PincherA->GetOutputVoltage() + m_PincherB->GetOutputVoltage();
	avgVolts /= 2.0;

	float avgPower = avgCurrent * avgVolts;
	return avgPower;
}

void Pincher::Spin(bool mode)
{
	m_SpinMode = mode;
}

void Pincher::GrabMode()
{
	m_CurrentPIDEnabled = true;
}

void Pincher::PositionMode()
{
	m_CurrentPIDEnabled = false;
}

void Pincher::EnablePID()
{
	m_PIDEnabled = true;
}

void Pincher::DisablePID()
{
	m_PIDEnabled = false;
}

void Pincher::EnablePositionPID()
{
	m_AtPositionTarget = false;
}
