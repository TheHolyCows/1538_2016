//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_ROBOT_H__
#define __COW_ROBOT_H__

#include <WPILib.h>
#include "Controllers/GenericController.h"
#include "CowLib/CowLib.h"
#include "CowControlBoard.h"
#include "CounterBase.h"
#include "CowConstants.h"
#include "CowLib/CowAlphaNum.h"
#include "CowLib/CowWebDebugger.h"
#include "CowGyro.h"
#include "Subsystems/Arm.h"
#include "Subsystems/CenteringIntake.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Shooter.h"

class CowRobot
{
public:
private:
	int m_DSUpdateCount;
	
	GenericController *m_Controller;
	
	// Drive Motors
	CANTalon *m_LeftDriveA;
	CANTalon *m_LeftDriveB;
	CANTalon *m_LeftDriveC;

	CANTalon *m_RightDriveA;
	CANTalon *m_RightDriveB;
	CANTalon *m_RightDriveC;
	
	CowLib::CowGyro *m_Gyro;
	Encoder *m_DriveEncoder;
	Encoder *m_QEI2;
	Encoder *m_QEI3;
	Encoder *m_QEI4;
	Encoder *m_QEI5;

	Arm* m_Arm;
	CenteringIntake* m_CenteringIntake;
	Intake*	m_Intake;
	Shooter* m_Shooter;

	PowerDistributionPanel *m_PowerDistributionPanel;

	CowLib::CowAlphaNum *m_LEDDisplay;
	CowLib::CowWebDebugger *m_WebServer;

	float m_LeftDriveValue;
	float m_RightDriveValue;

	double m_PreviousGyroError;
	double m_PreviousDriveError;

	void SetLeftMotors(float val);
	void SetRightMotors(float val);

public:
	CowRobot();
	void Reset();
	void GyroHandleCalibration();
	void GyroFinalizeCalibration();
	void SetController(GenericController *controller);
	void PrintToDS();
	double GetDriveDistance();
	bool DriveDistanceWithHeading(double heading, double distance);
	bool DriveWithHeading(double heading, double speed);
	bool DriveWithHeading(double heading, double speed, double maxSpeed);
	void DriveSpeedTurn(float speed, float turn, bool quickTurn);
	void DriveLeftRight(float leftDriveValue, float rightDriveValue);
	void QuickTurn(float turn);
	
	CowLib::CowAlphaNum *GetDisplay()
	{
		return m_LEDDisplay;
	}

	PowerDistributionPanel *GetPowerDistributionPanel()
	{
		return m_PowerDistributionPanel;
	}

	CowLib::CowGyro *GetGyro()
	{
		return CowLib::CowGyro::GetInstance();
	}

	Encoder *GetEncoder()
	{
		return m_DriveEncoder;
	}

	Arm *GetArm()
	{
		return m_Arm;
	}

	CenteringIntake *GetCenteringIntake()
	{
		return m_CenteringIntake;
	}

	Intake *GetIntake()
	{
		return m_Intake;
	}

	Shooter *GetShooter()
	{
		return m_Shooter;
	}




	void handle();
};

#endif
