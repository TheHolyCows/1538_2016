/*
 * BallHandler.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: Helen
 */

#include <Subsystems/BallHandler.h>
#include "../CowConstants.h"

BallHandler::BallHandler(CenteringIntake *centeringIntake, Intake *intake, Shooter *shooter) :
	m_CenteringIntake(centeringIntake),
	m_Intake(intake),
	m_Shooter(shooter),
	m_State(NO_BALL_AND_WAIT),
	m_ShooterState(MANUAL_CONTROL),
	m_StartTimeShooter(0),
	m_StartTimeIntake(0)
{

}

void BallHandler::SetState(e_BallHandleState state)
{
	if(state == SHOOT && m_ShooterState != SPOOL_PID_CONTROL)
	{
		return;
	}
   m_State = state;

   if((m_State == SHOOT) || (m_State == STAGE))
   {
	   m_StartTimeShooter = Timer::GetFPGATimestamp();
   }
   if((m_State == INTAKE))
   {
	   m_StartTimeIntake = Timer::GetFPGATimestamp();
   }
}

void BallHandler::SetShooterState(e_ShooterState state)
{
	m_ShooterState = state;
}

void BallHandler::Handle()
{
	switch(m_State)
   {
	  case NO_BALL_AND_WAIT:
	  {
		 SetShooterState(MANUAL_CONTROL);
		 m_Shooter->SetManualSpeed(0);
		 m_Intake->SetManualSpeed(0);
		 m_CenteringIntake->SetManualSpeed(0);

		 break;
	  }
	  case INTAKE:
	  {
		  std::cout << "Currently in Intake" << std::endl;
		  // run intake and centering intake
		  m_Intake->SetManualSpeed(1);
		  m_CenteringIntake->SetManualSpeed(1);

		  // check current so it could move to STAGE state
		  // call SetState(STAGE)
		  double watts = fabs(m_Intake->GetWatts());
		  double elapsedTime = Timer::GetFPGATimestamp() - m_StartTimeIntake;
		  std::cout << "Watts: " << watts << std::endl;
		  if(watts >= CONSTANT("INTAKE_WATTS") && elapsedTime > CONSTANT("INTAKE_STABLIZING_TIME"))
		  {
			  SetState(INTAKE_MOAR);
			  m_StartTimeIntake = Timer::GetFPGATimestamp();
		  }
		 break;
	  }
	  case INTAKE_MOAR:
	  {
		  m_CenteringIntake->SetManualSpeed(0);

		  double elapsedTime = Timer::GetFPGATimestamp() - m_StartTimeIntake;
		  if(elapsedTime > CONSTANT("INTAKE_MOAR_TIME"))
		  {
			  SetState(STAGE);
		  }
		  break;
	  }
	  case STAGE:
	  {
		  //SetShooterState(MANUAL_CONTROL);
		  m_Shooter->SetManualSpeed(-0.5);
		  m_Intake->SetManualSpeed(-1);
		  m_CenteringIntake->SetManualSpeed(1);

		  double elapsedTime = Timer::GetFPGATimestamp() - m_StartTimeShooter;

		  if(elapsedTime >= CONSTANT("STAGING_TIME"))
		  {
			  m_State = BALL_AND_WAIT;
		  }

		 break;
	  }
	  case BALL_AND_WAIT:
	  {
		 //SetShooterState(MANUAL_CONTROL);
		 m_Shooter->SetManualSpeed(0);
		 m_Intake->SetManualSpeed(0);
		 m_CenteringIntake->SetManualSpeed(0);

		 break;
	  }
	  case SHOOT:
	  {
		  // run all ie make ball go out
		 m_Intake->SetManualSpeed(1);
		 m_CenteringIntake->SetManualSpeed(0.2);

		 double elapsedTime = Timer::GetFPGATimestamp() - m_StartTimeShooter;

		 if(elapsedTime >= CONSTANT("AFTER_SHOOT_TIME") && m_Shooter->HasShotBall())
		 {
			 m_State = NO_BALL_AND_WAIT;
		 }

		 break;
	  }
	  default:
	  {
		 // SHOULD NEVER GO IN HERE
		 break;
	  }
   }

	switch(m_ShooterState)
   {
	  case MANUAL_CONTROL:
	  {
		 m_Shooter->SetPIDState(false);

		 break;
	  }
	  case SPOOL_PID_CONTROL:
	  {
		  m_Shooter->SetPIDState(true);
		  // start shooter
		  m_Shooter->SetAutoSpeed(CONSTANT("SHOOTER_RPM"));
		  break;
	  }
	  default:
	  {
		 // SHOULD NEVER GO IN HERE
		 break;
	  }
   }

}

e_BallHandleState BallHandler::GetState()
{
   return m_State;
}

BallHandler::~BallHandler()
{

}
