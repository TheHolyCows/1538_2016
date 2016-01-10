//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_ROBOT_H__
#define __COW_ROBOT_H__

#include <WPILib.h>
#include "Controllers/GenericController.h"
#include "Subsystems/Pincher.h"
#include "Subsystems/Spool.h"
#include "CowLib/CowLib.h"
#include "CowControlBoard.h"
#include "CounterBase.h"
#include "CowConstants.h"
#include "CowLib/CowAlphaNum.h"


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
	
	AnalogGyro *m_Gyro;
	Encoder *m_DriveEncoder;
	
	Pincher *m_Pincher;
	Spool *m_VerticalLift;

	//Spool *m_HorizontalLift;

	Solenoid *m_CanBurglarA;
	Solenoid *m_CanBurglarB;


	PowerDistributionPanel *m_PowerDistributionPanel;

	CowLib::CowAlphaNum *m_LEDDisplay;

	DigitalInput* m_GrabSwitch;
	bool m_AutoGrabOnce;
	float m_AutoGrabReleaseTime;
	float m_PreviousPincherSP;

	float m_LeftDriveValue;
	float m_RightDriveValue;

	double m_PreviousGyroError;
	double m_PreviousDriveError;

	bool m_CanBurglarValue;
		
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
	
	void SetCanBurglar(bool val);

	CowLib::CowAlphaNum *GetDisplay()
	{
		return m_LEDDisplay;
	}

	PowerDistributionPanel *GetPowerDistributionPanel()
	{
		return m_PowerDistributionPanel;
	}

	Gyro *GetGyro()
	{
		return m_Gyro;
	}

	Encoder *GetEncoder()
	{
		return m_DriveEncoder;
	}

	Spool *GetVerticalLift()
	{
		return m_VerticalLift;
	}

//	Spool *GetHorizontalLift()
//	{
//		return m_HorizontalLift;
//	}

	Pincher *GetPincher()
	{
		return m_Pincher;
	}

	void handle();
};

#endif
