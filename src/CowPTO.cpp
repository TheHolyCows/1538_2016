/*
 * CowPTO.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: Helen
 */

#include <CowPTO.h>

CowPTO::CowPTO(Solenoid *solenoidLeft) :
	m_State(LOCK),
	m_SolenoidLeft(solenoidLeft)
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

}

bool CowPTO::JimmyMode()
{
	return m_JimmyMode;
}

bool CowPTO::HangRequested()
{
	bool value = false;
	if(m_State == ENGAGE)
	{
		value = true;
	}

	return value;
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
			break;
		}

		case ENGAGE:// button 4
		{
			m_SolenoidLeft->Set(true);
			break;
		}
		default:
		{
			// should never get here either
			break;
		}
	}
}
