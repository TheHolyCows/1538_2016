/*
 * CowPTO.h
 *
 *  Created on: Feb 20, 2016
 *      Author: Helen
 */

#ifndef SRC_COWPTO_H_
#define SRC_COWPTO_H_

#include <WPILib.h>

typedef enum
{
	PTO_NONE = 0,
	LOCK,
	ENGAGE,
} e_PTO_State;

class CowPTO
{
public:
	virtual ~CowPTO();
	CowPTO(Solenoid *solenoidLeft);
	bool JimmyMode();
	bool HangRequested();
	void Handle();
	void SetState(e_PTO_State state);
private:
	e_PTO_State m_State;
	Solenoid *m_SolenoidLeft;	//
	double m_StartNeutralTime;
	bool m_JimmyMode;
};

#endif /* SRC_COWPTO_H_ */
