/*
 * Arm.h
 *
 *  Created on: Feb 14, 2016
 *      Author: kchau
 */

#ifndef SRC_SUBSYSTEMS_ARM_H_
#define SRC_SUBSYSTEMS_ARM_H_

#include <WPILib.h>
#include "../CowLib/CowPID.h"

class Arm {
private:
	CANTalon* m_MotorA;
	CANTalon* m_MotorB;
	CANTalon* m_Flashlight;
	Encoder* m_Encoder;
	CowLib::CowPID* m_PID;
	Solenoid* m_UnlockSolenoid;
	Solenoid* m_LockSolenoid;

	bool m_LockedState;
	bool m_StartUnlock;
	float m_Speed;
	float m_Setpoint;

	bool m_OffsetPosition;
	float m_UserOffsetPosition;
	double m_UnlockTime;
	Arm();
public:
	Arm(uint8_t motorA, uint8_t motorB, Encoder* encoder);
	virtual ~Arm();
	void AddUserOffset(float offset);
	void SetManualSpeed(float speed);
	void SetPosition(float position);
	float GetSetpoint();
	void SetLockState(bool state);
	bool GetLockState();
	void UseOffsetPosition();
	void Handle();
	void ResetConstants();
	void Reset();
};

#endif /* SRC_SUBSYSTEMS_ARM_H_ */
