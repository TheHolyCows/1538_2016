/*
 * Shooter.h
 *
 *  Created on: Feb 17, 2016
 *      Author: kchau
 */

#ifndef SRC_SUBSYSTEMS_SHOOTER_H_
#define SRC_SUBSYSTEMS_SHOOTER_H_

#include <WPILib.h>

class Shooter {
private:
	CANTalon* m_MotorA;
	CANTalon* m_MotorB;
	float m_Speed;
	Shooter();
public:
	Shooter(uint8_t motorA, uint8_t motorB);
	void SetManualSpeed(float speed);
	void Handle();
	virtual ~Shooter();
};

#endif /* SRC_SUBSYSTEMS_SHOOTER_H_ */
