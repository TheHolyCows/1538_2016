/*
 * CowPTO.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: Helen
 */

#include <CowPTO.h>

CowPTO::CowPTO(Solenoid *solenoidLeft, Solenoid *solenoidRight) :
	m_State(LOCK),
	m_SolenoidLeft(solenoidLeft),
	m_SolenoidRight(solenoidRight),
	m_StartNeutralTime(0)
{
	// TODO Auto-generated constructor stub

}

CowPTO::~CowPTO()
{
	// TODO Auto-generated destructor stub
}



void CowPTO::SetState(e_PTO_State state)
{
	m_State = state;
	if(state == ENTER_NEUTRAL)
	{
		m_StartNeutralTime = Timer::GetFPGATimestamp();
	}
}

void CowPTO::Handle()
{
	switch(m_State)
	{
		case PTO_NONE:
		{
			// do nothing
			break;
		}
		case LOCK: // button 1
		{
			m_SolenoidLeft->Set(false);
			m_SolenoidRight->Set(false);
			break;
		}
		case ENTER_NEUTRAL: // button 3
		{
			m_SolenoidLeft->Set(true);
			m_SolenoidRight->Set(true);

			double elapsedTime = Timer::GetFPGATimestamp() - m_StartNeutralTime;
			if(elapsedTime >= 0.100)
			{
				SetState(NEUTRAL);
			}
			break;
		}
		case NEUTRAL: //
		{
			m_SolenoidLeft->Set(false);
			m_SolenoidRight->Set(true);
			break;
		}
		case ENGAGE:// button 4
		{
			m_SolenoidLeft->Set(true);
			m_SolenoidRight->Set(true);
			break;
		}
		default:
		{
			// should never get here either
			break;
		}
	}
}
