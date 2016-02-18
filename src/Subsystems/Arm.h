/*
 * Arm.h
 *
 *  Created on: Feb 14, 2016
 *      Author: kchau
 */

#ifndef SRC_SUBSYSTEMS_ARM_H_
#define SRC_SUBSYSTEMS_ARM_H_

#include <WPILib.h>

class Arm {
private:
	CANTalon* m_MotorA;
	CANTalon* m_MotorB;
	float m_Speed;
	Arm();
public:
	Arm(uint8_t motorA, uint8_t motorB);
	virtual ~Arm();
	void SetManualSpeed(float speed);
	void Handle();
};

#endif /* SRC_SUBSYSTEMS_ARM_H_ */
