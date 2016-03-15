/*
 * Intake.h
 *
 *  Created on: Feb 17, 2016
 *      Author: kchau
 */

#ifndef SRC_SUBSYSTEMS_INTAKE_H_
#define SRC_SUBSYSTEMS_INTAKE_H_

#include <WPILib.h>

class Intake {
private:
	CANTalon* m_MotorA;
	CANTalon* m_MotorB;
	float m_Speed;
	Intake();
	bool m_AutoIntake;
	uint8_t m_BackoffCounts;
public:
	Intake(uint8_t motorA, uint8_t motorB);
	void SetManualSpeed(float speed);
	void AutoIntakeAndDrop();
	bool IsInAutoMode();
	double GetWatts();
	void Handle();
	void Reset();
	virtual ~Intake();
};

#endif /* SRC_SUBSYSTEMS_INTAKE_H_ */
