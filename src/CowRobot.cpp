#include "CowRobot.h"
#include "CowBase.h"

// TODO: A lot of the older functions in this file are clunky. Clean them up.

// TODO: Initializer list
// Constructor for CowRobot
CowRobot::CowRobot()
{	
	m_DSUpdateCount = 0;
		
	m_Controller = NULL;
	// Set up drive motors
	m_LeftDriveA = new CANTalon(DRIVE_LEFT_A);
	m_LeftDriveB = new CANTalon(DRIVE_LEFT_B);
	m_LeftDriveC = new CANTalon(DRIVE_LEFT_C);

	m_RightDriveA = new CANTalon(DRIVE_RIGHT_A);
	m_RightDriveB = new CANTalon(DRIVE_RIGHT_B);
	m_RightDriveC = new CANTalon(DRIVE_RIGHT_C);

	m_DriveEncoder = new Encoder(MXP_QEI_5_A, MXP_QEI_5_B, true, Encoder::k1X);
	m_DriveEncoder->SetDistancePerPulse(0.05235983333333); // 6*pi/360

	m_QEI2 = new Encoder(MXP_QEI_2_A, MXP_QEI_2_B, true, Encoder::k4X);
	m_QEI3 = new Encoder(MXP_QEI_3_A, MXP_QEI_3_B, true, Encoder::k1X);
	m_QEI4 = new Encoder(MXP_QEI_4_A, MXP_QEI_4_B, true, Encoder::k1X);
	//m_QEI5 = new Encoder(MXP_QEI_5_A, MXP_QEI_5_B, true, Encoder::k1X);

	m_Arm = new Arm(ARM_A, ARM_B, m_QEI2);
	m_CenteringIntake = new CenteringIntake(LEFT_CENTER, RIGHT_CENTER);
	m_Intake = new Intake(INTAKE_A, INTAKE_B);
	m_Shooter = new Shooter(SHOOTER_A, SHOOTER_B, m_QEI4, m_QEI3);
	m_BallHandler = new BallHandler(m_CenteringIntake, m_Intake, m_Shooter);

	m_SolenoidLeft = new Solenoid(SOLENOID_LEFT);
	m_SolenoidRight = new Solenoid(SOLENOID_RIGHT);
	m_CowPTO = new CowPTO(m_SolenoidLeft, m_SolenoidRight);

	m_LEDDisplay = new CowLib::CowAlphaNum(0x70);

	m_Gyro = CowLib::CowGyro::GetInstance();
	//m_Gyro->Reset();
	m_PowerDistributionPanel = new PowerDistributionPanel();
	m_WebServer = new CowLib::CowWebDebugger();

	m_LeftDriveValue = 0;
	m_RightDriveValue = 0;
	
	m_PreviousGyroError = 0;
	m_PreviousDriveError = 0;

	m_JimmyCounts = 0;
}

void CowRobot::Reset()
{
	m_Arm->ResetConstants();
	m_Shooter->ResetConstants();

	m_Arm->Reset();
	m_CenteringIntake->Reset();
	m_Intake->Reset();
	m_Shooter->Reset();

	m_DriveEncoder->Reset();

	m_PreviousGyroError = 0;
	m_PreviousDriveError = 0;

	m_JimmyCounts = 0;

	m_LeftDriveValue = 0;
	m_RightDriveValue = 0;
}

void CowRobot::SetController(GenericController *controller)
{
	m_Controller = controller;
}

void CowRobot::PrintToDS()
{
	if(m_DSUpdateCount % 10 == 0)
	{
		m_DSUpdateCount = 0;

//		CowLib::PrintToLCD("K:%s\nA:%s\nP:%f\nG:%f\nE:%f\nI:F%f_R%f",
//						   kinectArms,
//						   AutoModes::GetInstance()->GetName(),
//						   m_Winch->GetAverageVoltage(),
//						   m_Gyro->GetAngle(),
//						   m_DriveEncoder->GetDistance(),
//						   m_FrontIR->GetVoltage(), m_RearIR->GetVoltage());
	}
}

/// Used to handle the recurring logic funtions inside the robot.
/// Please call this once per update cycle.
void CowRobot::handle()
{	
	if(m_Controller == NULL)
	{
		printf("No controller for CowRobot!!\n");
		return;
	}

	//printf("Handling...\n");
	m_Controller->handle(this);
	
	m_Arm->Handle();
	m_CenteringIntake->Handle();
	m_Intake->Handle();
	m_Shooter->Handle();
	m_BallHandler->Handle();

	m_CowPTO->Handle();

	// Default drive
	float tmpLeftMotor = m_LeftDriveValue;
	float tmpRightMotor = m_RightDriveValue;
	
	if(m_CowPTO->JimmyMode())
	{
		if(m_JimmyCounts % 5 == 0)
		{
			m_JimmyCounts = 0;

			tmpLeftMotor = 0.5;
			tmpRightMotor = 0.5;
		}
		else
		{
			tmpLeftMotor = -0.5;
			tmpRightMotor = -0.5;
		}
	}

	if(m_CowPTO->HangRequested())
	{
		bool statusHang = DriveDistance(CONSTANT("PTO_DRIVE_DISTANCE"));

		if(statusHang)
		{
			m_CowPTO->SetState(LOCK);
		}
	}

	SetLeftMotors(tmpLeftMotor);
	SetRightMotors(tmpRightMotor);
//	if(m_DSUpdateCount % 10 == 0)
//	{
//		//5 is drive
//		//4 s1
//		//3 s2
//		//2 arm
//		//1 unused
//
//		//std::cout << "Gyro: " <<  m_Gyro->GetAngle() << std::endl;
//		std::cout << std::dec
//				  << m_DriveEncoder->Get() << " "
//				  << m_Gyro->GetAngle() << std::endl;
//	}

	m_DSUpdateCount++;
	m_JimmyCounts++;

}

double CowRobot::GetDriveDistance()
{
	return m_DriveEncoder->GetDistance();
}

bool CowRobot::DriveDistance(double distance)
{
	double PID_P = CONSTANT("DRIVE_P");
	double PID_D = CONSTANT("DRIVE_D");
	double error = distance - m_DriveEncoder->GetDistance();
	double dError = error - m_PreviousDriveError;
	double output = PID_P*error + PID_D*dError;

	double speed = CONSTANT("PTO_DRIVE_SPEED");
	DriveLeftRight(speed-output, speed+output);


	m_PreviousDriveError = error;

	return (fabs(error) < 4 && CowLib::UnitsPerSecond(fabs(dError)) < 1);
}

bool CowRobot::DriveDistanceWithHeading(double heading, double distance)
{
	double PID_P = CONSTANT("DRIVE_P");
	double PID_D = CONSTANT("DRIVE_D");
	double error = distance - m_DriveEncoder->GetDistance();
	double dError = error - m_PreviousDriveError;
	double output = PID_P*error + PID_D*dError;
	
	bool headingResult = DriveWithHeading(heading,
			CowLib::LimitMix(output, CONSTANT("DRIVE_MAX_SPEED")));
	
	m_PreviousDriveError = error;
	
	return (fabs(error) < 4 && CowLib::UnitsPerSecond(fabs(dError)) < 1 && headingResult);
}

bool CowRobot::DriveWithHeading(double heading, double speed)
{
	double PID_P = CONSTANT("TURN_P");
	double PID_D = CONSTANT("TURN_D");
	double error = heading - m_Gyro->GetAngle();
	double dError = error - m_PreviousGyroError;
	double output = PID_P*error + PID_D*dError;
				
	DriveLeftRight(speed-output, speed+output);
	
	m_PreviousGyroError = error;
	
	return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
}

bool CowRobot::DriveWithHeading(double heading, double speed, double maxSpeed)
{
	speed *= -1;
	double PID_P = CONSTANT("TURN_P");
	double PID_D = CONSTANT("TURN_D");
	double error = heading - m_Gyro->GetAngle();
	double dError = error - m_PreviousGyroError;
	double output = PID_P*error + PID_D*dError;
	output = CowLib::LimitMix(output, maxSpeed);

	DriveLeftRight(speed-output, speed+output);

	m_PreviousGyroError = error;

	return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
}


// Allows skid steer robot to be driven using tank drive style inputs
// @param leftDriveValue
// @param rightDriveValue
void CowRobot::DriveLeftRight(float leftDriveValue, float rightDriveValue)
{
	m_LeftDriveValue = leftDriveValue;
	m_RightDriveValue = rightDriveValue;
}

void CowRobot::DriveSpeedTurn(float speed, float turn, bool quickTurn)
{
	// Linear degredation of steeering based off of velocity
	//velocity *= 0.003;
	float temp_vel = speed;
	float sensitivity = 0;

	if (temp_vel < 0)
		temp_vel = -temp_vel;

	//printf("Velocity: %f, stick: %f\r\n", velocity, temp_vel);
	
	if(speed < 0.10 && speed > -0.10)
		speed = 0;
	if (((turn < 0.10) && (turn > -0.10)) || ((speed == 0) && !quickTurn))
		turn = 0;

	if(quickTurn)
	{
		if(speed == 0.0)
		{
			sensitivity = 1;
		}
		else
		{
			sensitivity = 0.75;
		}

	}
	else
	{
		sensitivity = 0.22;
	}

	turn *= sensitivity;
	turn = -turn;
	

	float left_power = CowLib::LimitMix(speed + turn);
	float right_power = CowLib::LimitMix(speed - turn);

	DriveLeftRight(left_power, right_power);
}

// Allows robot to spin in place
// @param turnRate
void CowRobot::QuickTurn(float turnRate)
{
	// when provided with + turn, quick turn right

	float left = -1 * turnRate;
	float right = turnRate;

	DriveLeftRight(left, right);
}

// sets the left side motors
void CowRobot::SetLeftMotors(float val)
{
	if (val > 1.0)
		val = 1.0;
	if (val < -1.0)
		val = -1.0;

	m_LeftDriveA->Set(val);
	m_LeftDriveB->Set(val);
	m_LeftDriveC->Set(-val);

}

// sets the left side motors
void CowRobot::SetRightMotors(float val)
{
	if (val > 1.0)
		val = 1.0;
	if (val < -1.0)
		val = -1.0;

	m_RightDriveA->Set(val);
	m_RightDriveB->Set(-val);
	m_RightDriveC->Set(-val);
}
