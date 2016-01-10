//==================================================
// Copyright (C) 2015 Team 1538 / The Holy Cows
//==================================================

#ifndef __DECLARATIONS_H__
#define __DECLARATIONS_H__

#define ROBOT_HZ						400

#define COWCONSTANTS_DEFAULT_FILE		"/home/lvuser/constants.ini"

// Number of accumulation periods to be summed
#define COWGYRO_RING_SIZE				5
// Length of an accumulation period in seconds
#define COWGYRO_ACCUMULATION_PERIOD		1.0

#define GYRO_SENSITIVITY				0.007

// CAN IDs
#define DRIVE_LEFT_A					1
#define DRIVE_LEFT_B					2
#define DRIVE_LEFT_C					3
#define DRIVE_RIGHT_A					4
#define DRIVE_RIGHT_B					5
#define DRIVE_RIGHT_C					6
#define UNUSED_CAN						7
#define PINCHER_A						8
#define PINCHER_B						9
#define LEFT_INTAKE						10
#define RIGHT_INTAKE					11
#define HSPOOL_A						12
#define VSPOOL_A						13
#define VSPOOL_B						14
#define CANBURGLAR_A					7
#define CANBURGLAR_B					4


#define MXP_DRIVE_A						12
#define MXP_DRIVE_B						13
#define MXP_GRABBER_A					14
#define MXP_GRABBER_B					15
#define MXP_HSPOOL_A					16
#define MXP_HSPOOL_B					17
#define MXP_VSPOOL_A					18
#define MXP_VSPOOL_B					19

#define MXP_GRAB_SWITCH					16

// Analog inputs
#define ANALOG_GYRO						0

// Digital outputs	
#define RELAY_COMPRESSOR				1

// Digital inputs
#define DIGITAL_PRESSURE_SWITCH			1

#endif
