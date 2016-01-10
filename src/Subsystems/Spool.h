//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __SPOOL_H__
#define __SPOOL_H__

#include <WPILib.h>
#include <string>

class Spool
{
public:
	Spool(std::string name, uint8_t motorAID, uint8_t motorBID, uint8_t encA, uint8_t encB, bool reversePID);
	Spool(std::string name, uint8_t motorAID, uint8_t encA, uint8_t encB, bool reversePID);

	virtual ~Spool();
	void handle();
	void UpdateSetPoint(float setpoint);
	void UpdateManualSpeeds(float speed);
	float GetPosition();

	void EnablePID();
	void DisablePID();

	void Reset();

private:
	std::string m_Name;

	CANTalon *m_MotorA;
	CANTalon *m_MotorB;
	Encoder *m_Encoder;

	bool m_PIDEnabled;
	float m_SetPoint;

	float m_PIDOutput;
	float m_PID_P;
	float m_PID_D;
	float m_PID_P_Previous;

	float m_ManualSpeed;
	bool m_ReversePID;

};

#endif /* __SPOOL_H__ */
