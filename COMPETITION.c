#pragma config(Sensor, in1,    armp,           sensorPotentiometer)
#pragma config(Sensor, in2,    dial,           sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, in4,    acc,            sensorAccelerometer)
#pragma config(Sensor, dgtl1,  pnintake,       sensorDigitalOut)
#pragma config(Sensor, dgtl2,  pnsky,          sensorDigitalOut)
#pragma config(Motor,  port2,           BL,            tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           ML,            tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           FL,            tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           BR,            tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           MR,            tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           FR,            tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightArm,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftArm,       tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "functions.c"

int skyriseHeight = 1950;
int firstPos = 600;
int secondPos = 1000;
int thirdPos = 1520;
int fourthPos = 2250;
int fifthPos = 3000;


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Pre-Autonomous
//
/////////////////////////////////////////////////////////////////////////////////////////


void pre_auton()
{
/*
 bStopTasksBetweenModes = true;

 startTask(printGyroToLCD);
*/
}







/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous
//
//
//	1st position:Blue Cube score
//	2nd position:Blue Skyrise score
//	3rd position:Red Cube score
//	4th position:Red Skyrise score
//
//
/////////////////////////////////////////////////////////////////////////////////////////


task autonomous(){  //Programs are chosen by the value of the dial potentiometer.
		//DO NOT COPY THE TOP!!!


	int position=SensorValue[dial];
	//11111111111111111111111111111111111111111111111111111111111111111111111111
	//Blue side block || Put block on post turn around grab two and put them somewhere
	if (position>=firstPos&&position<secondPos)
	{
	}


	//2222222222222222222222222262222222222222222222222222222222222222222222222
	//Blue side skyrise
	else if (position>=secondPos&&position<thirdPos)
	{
	}


	//33333333333333333333333333333333333333333333333333333333333333333333333333
	//Red side cube
	else if(position>=thirdPos&&position<fourthPos)
	{
	}


	//444444444444444444444444444444444444444444444444444444444444444444444444444
	//Red side skyrise
	else if(position>=fourthPos&&position<fifthPos)
	{
	}


	//55555555555555555555555555555555555555555555555555555555555555
	//Raise arm up
	else if(position>=fifthPos)
	{
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol(){
	bool half=false;
	int buttonToggleState8r = 0;//half speed
  int buttonPressed8r = 0;
  int buttonToggleState8d = 0;//Raise Arm
  int buttonPressed8D = 0;
  int buttonToggleState7d = 0;//lower Arm
  int buttonPressed7d = 0;
	int buttonToggleState7l = 0;//pneumatics
  int buttonPressed7l = 0;

	//startTask(armcontrol);
	while (true) {
		if(bVEXNETActive){

			//Toggle half speed---------------------------------------------------------------
			if( vexRT[ Btn7L ] == 1 ) {
	      if( ! buttonPressed7l ) {

	      	// change the toggle state
	      	buttonToggleState7l = 1 - buttonToggleState7l;

	        // Note the button is pressed
	        buttonPressed7l = 1;
	      }
	  	} else {

		    // the button is not pressed
		    buttonPressed7l = 0;
		  }

		  // Now do something with our toggle flag
	    if( buttonToggleState7l ) {
	      half=true;
	    } else {
	      half=false;
		  }

	   //Toggle pneumatics------------------------------------------------
		  if( vexRT[ Btn8R ] == 1 )
	    {
	      if( ! buttonPressed8r )
	      {
	      	// change the toggle state
	      	buttonToggleState8r = 1 - buttonToggleState8r;

	        // Note the button is pressed
	        buttonPressed8r = 1;
	      }
	    }
	    else
	    {
		    // the button is not pressed
		    buttonPressed8r = 0;
		  }
	    // Now do something with our toggle flag
	    if( buttonToggleState8r )
	    {
	      SensorValue[pnintake]=1;
	    }
	    else
	    {
	      SensorValue[pnintake]=0;
		  }


			//DRIVE-----------------------------------------------------
			if (half==false){ //Check if drive toggles half speed.
				//give drive direct control.
				motor[BR] = vexRT[Ch2];
				motor[FR] = vexRT[Ch2];
				motor[BL] = vexRT[Ch3];
				motor[FL] = vexRT[Ch3];
			} else if(half ==true) {
				//give drive control but all motor maxes are a third of their orignal max.
				motor[BR] = vexRT[Ch2]/3;
				motor[FR] = vexRT[Ch2]/3;
				motor[BL] = vexRT[Ch3]/3;
				motor[FL] = vexRT[Ch3]/3;
			}


	  	//ARM MOTION----------------------------
			if(vexRT[Btn5D] == true){
      	/*if(nMotorEncoder(rightArm) > nMotorEncoder(leftArm)){
        	motor[rightArm] = 127/2;
        	motor[leftArm] = 127;
      	}else if(nMotorEncoder(rightArm) < nMotorEncoder(leftArm)){
        	motor[rightArm] = 127;
        	motor[leftArm] = 127/2;
      	}else{*/
        	motor[rightArm] = -126;
        	motor[leftArm] = -126;
      	//}
    	}else if(vexRT[Btn6D] == true){
      	/*if(nMotorEncoder(rightArm) > nMotorEncoder(leftArm)){
        	motor[rightArm] = -10;
        	motor[leftArm] = -20;
      	}else if(nMotorEncoder(rightArm) < nMotorEncoder(leftArm)){
        	motor[rightArm] = -20;
        	motor[leftArm] = -10;
      	}else{*/
        	motor[rightArm] = 126;
        	motor[leftArm] = 126;
      	//}
    	}else{
      	motor[rightArm] = 0;
      	motor[leftArm] = 0;
    	}
			wait1Msec(10);
		}
	}
}
