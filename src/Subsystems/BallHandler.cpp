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
	m_StartTimeShooter(0),
	m_StartTimeIntake(0)
{

}

void BallHandler::SetState(e_BallHandleState state)
{
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

void BallHandler::Handle()
{
	switch(m_State)
   {
	  case NO_BALL_AND_WAIT:
	  {
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
		  double current = m_Intake->GetCurrent();
		  double elapsedTime = Timer::GetFPGATimestamp() - m_StartTimeIntake;
		  std::cout << "Current: " << current << std::endl;
		  if(current >= CONSTANT("INTAKE_CURRENT") && elapsedTime > 0.5)
		  {
			  SetState(INTAKE_MOAR);
			  m_StartTimeIntake = Timer::GetFPGATimestamp();
		  }
		 break;
	  }
	  case INTAKE_MOAR:
	  {
		  double elapsedTime = Timer::GetFPGATimestamp() - m_StartTimeIntake;
		  if(elapsedTime > CONSTANT("INTAKE_MOAR_TIME"))
		  {
			  SetState(STAGE);
		  }
		  break;
	  }
	  case STAGE:
	  {
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
		 m_Shooter->SetManualSpeed(0);
		 m_Intake->SetManualSpeed(0);
		 m_CenteringIntake->SetManualSpeed(0);

		 break;
	  }
	  case SPOOL_SHOOTER:
	  {
		  // start shooter
		  m_Shooter->SetManualSpeed(1);
		  break;
	  }
	  case SHOOT:
	  {
		  // run all ie make ball go out
		 m_Intake->SetManualSpeed(1);
		 m_CenteringIntake->SetManualSpeed(1);

		 double elapsedTime = Timer::GetFPGATimestamp() - m_StartTimeShooter;

		 if(elapsedTime >= 0.25)
		 {
		//	 m_State = NO_BALL_AND_WAIT;
		 }

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
