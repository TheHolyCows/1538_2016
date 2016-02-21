/*
 * CowLatch.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: kchau
 */

#include <CowLib/CowLatch.h>

namespace CowLib {

CowLatch::CowLatch()
:
		m_State(false),
		m_Latched(false)
{
	// TODO Auto-generated constructor stub

}


//if(!m_CB->GetOperatorButton(10))
//{
//	if(!setPinchOnce)
//	{
//		bot->GetPincher()->UpdateSetPoint(CONSTANT("PINCHER_OPEN"));
//		bot->GetPincher()->EnablePositionPID();
//		setPinchOnce = true;
//	}
//	bot->GetPincher()->PositionMode();
//}
//else
//{
//	bot->GetPincher()->GrabMode();
//	setPinchOnce = false;
//}


//Returns true if state has changed
bool CowLatch::Latch(bool value)
{
	bool stateChanged = false;
	if(!m_Latched && value)
	{
		m_State = value;
		m_Latched = true;
		stateChanged = true;
	}

	return stateChanged;
}

void CowLatch::ResetLatch()
{
	m_State = false;
	m_Latched = false;
}



CowLatch::~CowLatch() {
	// TODO Auto-generated destructor stub
}

} /* namespace CowLib */
