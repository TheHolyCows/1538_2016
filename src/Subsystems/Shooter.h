/*
 * Shooter.h
 *
 *  Created on: Feb 17, 2016
 *      Author: kchau
 */

#ifndef SRC_SUBSYSTEMS_SHOOTER_H_
#define SRC_SUBSYSTEMS_SHOOTER_H_

#include <WPILib.h>
#include "../CowLib/CowPID.h"

class Shooter {
private:
	CANTalon* m_MotorA;
	CANTalon* m_MotorB;
	float m_Speed;

	Encoder *m_EncoderA;
	Encoder *m_EncoderB;

	CowLib::CowPID* m_PID_A_Rate;
	CowLib::CowPID* m_PID_B_Rate;

	bool m_PIDEnabled;
	double m_EncoderASpeed;
	double m_EncoderBSpeed;
	Shooter();
public:
	Shooter(uint8_t motorA, uint8_t motorB, Encoder* encoderA, Encoder* encoderB);
	void SetManualSpeed(float speed);
	void SetAutoSpeed(float speedA, float speedB);
	void SetPIDState(bool state);
	double GetMotorASpeed();
	double GetMotorBSpeed();
	bool IsOnTarget();
	bool HasShotBall();
	void ResetConstants();
	void Reset();
	void Handle();
	virtual ~Shooter();
};

#endif /* SRC_SUBSYSTEMS_SHOOTER_H_ */
