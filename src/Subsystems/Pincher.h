//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __PINCHER_H__
#define __PINCHER_H__

#include <WPILib.h>

class Pincher
{
public:
	Pincher(unsigned int leftIntake,
			unsigned int rightIntake,
			unsigned int extendMotorA,
			unsigned int extendMotorB,
			unsigned int encoderA,
			unsigned int encoderB);
	virtual ~Pincher();
	void handle();
	void UpdateSetPoint(float setpoint);
	void ManualControl(float intake, float pincher);
	float GetSetPoint();
	float GetPosition();

	void GrabMode();
	void PositionMode();
	void Spin(bool mode);

	float GetWattage();

	void EnablePID();
	void DisablePID();
	void EnablePositionPID();

	void Reset();

private:
	float m_IntakeSpeed;
	float m_PincherSpeed;

	CANTalon *m_LeftIntake;
	CANTalon *m_RightIntake;
	CANTalon *m_PincherA;
	CANTalon *m_PincherB;
	Encoder *m_Encoder;

	bool m_PIDEnabled;
	bool m_AtPositionTarget;

	bool m_CurrentPIDEnabled;
	bool m_SpinMode;

	float m_SetPoint;
	float m_PIDOutput;
	float m_PID_P;
	float m_PID_D;
	float m_PID_P_Previous;
};

#endif /* __PINCHER_H__ */
