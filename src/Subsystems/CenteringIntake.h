/*
 * CenteringIntake.h
 *
 *  Created on: Feb 17, 2016
 *      Author: kchau
 */

#ifndef SRC_SUBSYSTEMS_CENTERINGINTAKE_H_
#define SRC_SUBSYSTEMS_CENTERINGINTAKE_H_

#include <WPILib.h>

class CenteringIntake {
private:
	CANTalon* m_LeftMotor;
	CANTalon* m_RightMotor;
	float m_Speed;
	CenteringIntake();
public:
	CenteringIntake(uint8_t leftMotor, uint8_t rightMotor);
	void SetManualSpeed(float speed);
	void Handle();
	double GetWattsLeft();
	double GetWattsRight();
	virtual ~CenteringIntake();
};

#endif /* SRC_SUBSYSTEMS_CENTERINGINTAKE_H_ */
