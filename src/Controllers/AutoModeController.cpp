#include "AutoModeController.h"

AutoModeController::AutoModeController()
	:
	m_Timer(new Timer()),
	m_CurrentCommand(RobotCommand())
{
	m_Timer->Start();
	reset();
}

void AutoModeController::SetCommandList(deque<RobotCommand> list)
{
	m_CommandList = list;
}

void AutoModeController::reset()
{
	CowConstants::GetInstance();

	m_CommandList.clear();
	m_CurrentCommand = RobotCommand();
}


void AutoModeController::handle(CowRobot *bot)
{
	bool result = false;
	
	// Run the command
	switch(m_CurrentCommand.m_Command)
	{
		case CMD_NULL:
		{
			doNothing(bot);
			
			result = true;
			break;
		}
		case CMD_WAIT:
		{
			bot->DriveWithHeading(m_CurrentCommand.m_Heading, 0);
			bot->GetArm()->SetPosition(m_CurrentCommand.m_Arm);
			doNothing(bot);
			break;
		}
		case CMD_TURN:
		{
			result = bot->TurnToHeading(m_CurrentCommand.m_Heading);
			bot->GetArm()->SetPosition(m_CurrentCommand.m_Arm);

			break;
		}
		case CMD_HOLD_DISTANCE:
		{
			bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount, m_CurrentCommand.m_Speed);
			bot->GetArm()->SetPosition(m_CurrentCommand.m_Arm);

			result = false;
			break;
		}
		case CMD_DRIVE_DISTANCE:
		{
			result = bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount,  m_CurrentCommand.m_Speed );
			bot->GetArm()->SetPosition(m_CurrentCommand.m_Arm);

			break;
		}
		case CMD_INTAKE:
		{
			bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount,m_CurrentCommand.m_Speed);
			bot->GetArm()->SetPosition(m_CurrentCommand.m_Arm);
			bot->GetBallHandler()->SetState(INTAKE);

			e_BallHandleState ballState = bot->GetBallHandler()->GetState();
			if(ballState == INTAKE_MOAR ||
			   ballState == STAGE ||
			   ballState == BALL_AND_WAIT)
			{
				result = true;
			}
			else if(ballState == NO_BALL_AND_WAIT)
			{
				bot->GetBallHandler()->SetState(INTAKE);
			}
			break;
		}
		case CMD_SPOOL_SHOOTER:
		{
			bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount,  m_CurrentCommand.m_Speed);
			bot->GetArm()->SetPosition(m_CurrentCommand.m_Arm);

			e_ShooterState shooterState = bot->GetBallHandler()->GetShooterState();

			if(shooterState == MANUAL_CONTROL)
			{
				bot->GetBallHandler()->SetShooterState(SPOOL_PID_CONTROL);
			}

			result = true;

			break;
		}
		case CMD_SHOOT:
		{
			bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount,  m_CurrentCommand.m_Speed);
			bot->GetArm()->SetPosition(m_CurrentCommand.m_Arm);

			e_BallHandleState ballState = bot->GetBallHandler()->GetState();
			e_ShooterState shooterState = bot->GetBallHandler()->GetShooterState();

			if(ballState == BALL_AND_WAIT && shooterState == SPOOL_PID_CONTROL)
			{
				bot->GetBallHandler()->SetState(SHOOT);
			}
			else if(ballState == NO_BALL_AND_WAIT && shooterState == MANUAL_CONTROL)
			{
				result = true;
			}

			break;
		}
		case CMD_RESET_DRIVE_ENCODER:
		{
			break;
		}
		case CMD_ADD_ANGLE_OFFSET:
		{
			std::deque<RobotCommand>::iterator iterator = m_CommandList.begin();

			for(; iterator != m_CommandList.end(); ++iterator)
			{
				iterator->m_Heading += bot->GetAutoOffsetAngle();
			}
			break;
		}
		default:
		{
			doNothing(bot);
			result = true;
			break;
		}
	}
	
	// Check if this command is done
	if(result == true || m_CurrentCommand.m_Command == CMD_NULL || m_Timer->Get() > m_CurrentCommand.m_Timeout)
	{
		// This command is done, go get the next one
		if(m_CommandList.size() > 0 )
		{
			if(m_CurrentCommand.m_Command == CMD_TURN)
			{
				bot->GetEncoder()->Reset();
			}
			m_CurrentCommand = m_CommandList.front();
			m_CommandList.pop_front();
			//bot->GetEncoder()->Reset();
			
			if(!m_CurrentCommand.m_Command == CMD_NULL)
			{
				printf("Time elapsed: %f\n", m_Timer->Get());
			}
		}
		else
		{
			//we're done clean up
			m_CurrentCommand = RobotCommand();
		}
		m_Timer->Reset();
	}
}

// Drive Functions
void AutoModeController::doNothing(CowRobot *bot)
{
	bot->DriveLeftRight(0, 0);
	bot->GetArm()->SetPosition(m_CurrentCommand.m_Arm);

}
