/*
 * BallHandler.h
 *
 *  Created on: Feb 18, 2016
 *      Author: Helen
 */

#ifndef SRC_SUBSYSTEMS_BALLHANDLER_H_
#define SRC_SUBSYSTEMS_BALLHANDLER_H_

#include <Subsystems/CenteringIntake.h>
#include <Subsystems/Intake.h>
#include <Subsystems/Shooter.h>

typedef enum
{
   NONE = 0,
   NO_BALL_AND_WAIT,
   INTAKE,
   INTAKE_MOAR,
   STAGE,
   BALL_AND_WAIT,
   SPOOL_SHOOTER,
   SHOOT

} e_BallHandleState;

class BallHandler
{
public:
   BallHandler(CenteringIntake* centeringIntake, Intake* intake, Shooter* shooter);
   ~BallHandler();
   void Handle();
   e_BallHandleState GetState();
   void SetState(e_BallHandleState state);
private:
   e_BallHandleState m_State;
   CenteringIntake* m_CenteringIntake;
   Intake* m_Intake;
   Shooter* m_Shooter;
   double m_StartTimeShooter;
   double m_StartTimeIntake;
};

#endif /* SRC_SUBSYSTEMS_BALLHANDLER_H_ */
