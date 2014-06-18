#pragma config(Motor,  port1,           FrontRightDrive,    tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port2,           FrontLeftDrive,     tmotorVex393, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port3,           BackRightDrive,     tmotorVex393, openLoop, encoder, encoderPort, I2C_3, 1000)
#pragma config(Motor,  port4,           BackLeftDrive,      tmotorVex393, openLoop, encoder, encoderPort, I2C_4, 1000)
#pragma config(Motor,  port5,           LeftArm,       tmotorVex393, openLoop, encoder, encoderPort, I2C_5, 1000)
#pragma config(Motor,  port6,           RightArm,      tmotorVex393, openLoop, encoder, encoderPort, I2C_6, 1000)
#pragma config(Motor,  port7,           LeftIntake,   tmotorVex393, openLoop, encoder, encoderPort, I2C_5, 1000)
#pragma config(Motor,  port8,           RightIntake,  tmotorVex393, openLoop, encoder, encoderPort, I2C_6, 1000)

/*

	***************************************************
	File for testing the main robot code
	***************************************************

*/

//Competition Control and Duration Settings
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"


/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton(){
	bStopTasksBetweenModes = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Autonomous Functions
//
// This task is used to control the robot during the autonomous phase of a VEX Competition.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous(){

}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control the robot during the user control phase of a VEX Competition.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol(){
	// Create "deadzone" variables for drivetrain
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 10;

	while (true){
		if(bVEXNETActive){

			// ARM (PARTNER JOYSTICK)
			motor[RightArm] = 127 * vexRT[Btn5DXmtr2] - 127 * vexRT[Btn5UXmtr2];
			motor[LeftArm] = 127 * vexRT[Btn5DXmtr2] - 127 * vexRT[Btn5UXmtr2];

			// INTAKE (PARTNER JOYSTICK)
			motor[RightIntake] = 127 * vexRT[Btn6UXmtr2] - 127 * vexRT[Btn6DXmtr2];
			motor[LeftIntake] = 127 * vexRT[Btn6UXmtr2] - 127 * vexRT[Btn6DXmtr2];

    	// MECANUM DRIVETRAIN (MAIN JOYSTICK)
			/*
				CONTROL DIAGRAM

									 Ch3
								 FORWARD													 Ch2
										|																|
					Ch4				|											Ch1				|
				STRAFE------|------STRAFE				ROTATE------|------ROTATE
					  				|																|
										|																|
								 BACKWARD

			*/

			// Handle "deadzone" for Y1/Ch3
			if (abs(vexRT[Ch3]) > threshold) {
				Y1 = vexRT[Ch3];
			} else {
				Y1 = 0;
			}

			// Handle "deadzone" for X1/Ch4
			if(abs(vexRT[Ch4]) > threshold) {
				X1 = vexRT[Ch4];
			} else {
				X1 = 0;
			}

			// Handle "deadzone" for X2/Ch1
			if(abs(vexRT[Ch1]) > threshold) {
				X2 = vexRT[Ch1];
			} else {
				X2 = 0;
			}

			// Apply X and Y values to motors
			motor[FrontRightDrive] = Y1 - X2 - X1;
			motor[BackRightDrive] =  Y1 - X2 + X1;
			motor[FrontLeftDrive] = Y1 + X2 + X1;
			motor[BackLeftDrive] =  Y1 + X2 - X1;

		}
	}
}
