#include "CowBase.h"
#include <string.h>

CowBase::CowBase()
	:
	m_ControlBoard(new CowControlBoard()),
	m_OpController(new OperatorController(m_ControlBoard)),
	m_AutoController(new AutoModeController()),
	m_Constants(CowConstants::GetInstance())
{	
	CowConstants::GetInstance()->RestoreData();
	m_Bot = new CowRobot();

	m_Display = new CowDisplay(m_Bot);

	//SetPeriod(HZ(ROBOT_HZ));
	//GetWatchdog().SetEnabled(false);
	printf("Done constructing CowBase!\n");
}

CowBase::~CowBase()
{
	delete m_ControlBoard;
	delete m_OpController;
	delete m_AutoController;
	delete m_Display;
}

void CowBase::RobotInit()
{
	m_Bot->Reset();
}

void CowBase::DisabledInit()
{
	CowConstants::GetInstance()->RestoreData();
}

void CowBase::AutonomousInit()
{
	m_AutoController->SetCommandList(AutoModes::GetInstance()->GetCommandList());
	m_Bot->SetController(m_AutoController);
	m_Bot->Reset();
}
void CowBase::TeleopInit()
{
	m_Bot->SetController(m_OpController);
}

void CowBase::DisabledContinuous()
{
	//taskDelay(WAIT_FOREVER);
}

void CowBase::AutonomousContinuous()
{
	//taskDelay(WAIT_FOREVER);
}

void CowBase::TeleopContinuous()
{
	//taskDelay(WAIT_FOREVER);
}

void CowBase::DisabledPeriodic()
{
	//m_Bot->GyroHandleCalibration();
	if(m_Display)
	{
		m_Display->DisplayPeriodic();
	}
	if(m_ControlBoard->GetAutoSelectButton())
	{
		m_Constants->RestoreData();

		if(m_ControlBoard->GetDriveButton(1))
		{
			//m_Bot->Reset();
			AutoModes::GetInstance()->NextMode();
		}
	}
	
//	m_Bot->PrintToDS();
}
void CowBase::AutonomousPeriodic()
{
	m_Bot->handle();
}
void CowBase::TeleopPeriodic()
{
	m_Bot->handle();
}

START_ROBOT_CLASS(CowBase);
