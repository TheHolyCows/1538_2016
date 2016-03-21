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
   EXHAUST,
   STALL_REVERSE,
   INTAKE_MOAR,
   STAGE,
   BALL_AND_WAIT,
   SHOOT_STAGE,
   SHOOT

} e_BallHandleState;

typedef enum
{
   SHOOTER_NONE = 0,
   MANUAL_CONTROL,
   SPOOL_PID_CONTROL

} e_ShooterState;

class BallHandler
{
public:
   BallHandler(CenteringIntake* centeringIntake, Intake* intake, Shooter* shooter);
   ~BallHandler();
   void Handle();
   e_BallHandleState GetState();
   e_ShooterState GetShooterState();
   void SetState(e_BallHandleState state);
   void SetShooterState(e_ShooterState state);

private:
   CenteringIntake* m_CenteringIntake;
   Intake* m_Intake;
   Shooter* m_Shooter;
   e_BallHandleState m_State;
   e_ShooterState m_ShooterState;
   double m_StartTimeShooter;
   double m_StartTimeIntake;
   double m_StartTimeExhaust;
};

#endif /* SRC_SUBSYSTEMS_BALLHANDLER_H_ */
