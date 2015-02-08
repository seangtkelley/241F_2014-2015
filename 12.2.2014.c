#pragma config(Sensor, in1,    armP,           sensorPotentiometer)
#pragma config(Sensor, in2,    dial,           sensorPotentiometer)
#pragma config(Sensor, dgtl1,  touchupl,       sensorTouch)
#pragma config(Sensor, dgtl2,  touchdownl,     sensorTouch)
#pragma config(Sensor, dgtl3,  ,               sensorTouch)
#pragma config(Sensor, dgtl4,  ,               sensorTouch)
#pragma config(Sensor, dgtl5,  encoderRight,   sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  encoderLeft,    sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  encoderIntake,  sensorQuadEncoder)
#pragma config(Motor,  port1,            ,             tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           BL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           FL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           BR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           FR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightArm,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftArm,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           intake1,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           intake2,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,           ,             tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Pre-Autonomous
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
 bStopTasksBetweenModes = true;
}





/////////////////////////////////////////////////////////////////////////////////////////
//
//                                  Functions
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
//----------------------------------------------------------------------------------------
//
//                                    INDEX
//
// drive: gives the controller control of the wheels.
// clearmotor: sets all drivemotors to 0.
// forward: Move forward by a certain amount of ticks.
// forwards: Move forward by a duration of time.
// backward: Move backward a certain amount of ticks.
// backwards:Move backward a duration of time.
// correctturn: Put a certain amount of degrees and the robot gets the most efficiant way to turn done in ticks.
// turnright: turn right by ticks.
// turnleft: turn left by ticks.
// turnr:turn right for a duration of time.
// turnl:turn left for a duration of time.
// raisearm: raise arm a certain amount of ticks.
// lowlowerarm: lower arm for a duration of time.
// increment: Move the arm to a specified level.
// taketower: for a SPECIFIC location, get a skyrise piece and move back to that location.
// lock: engage the pneumatic lock.
// release: release the pneumatic lock.
//
//
/////////////////////////////////////////////////////////////////////////////////////////





void drive(bool half, bool switchdirection)
{

		if(switchdirection==true)
		{
			if (half==false)//Check if drive toggles half speed.
			{
				motor[BR] = -vexRT[Ch3]; //give drive direct control.
				motor[FR] = -vexRT[Ch3];
				motor[BL] = -vexRT[Ch2];
				motor[FL] = -vexRT[Ch2];
			}
			else if(half ==true)
			{
				motor[BR] = -vexRT[Ch3]/3;//give drive control but all motor maxes are a third of their orignal max.
				motor[FR] = -vexRT[Ch3]/3;
				motor[BL] = -vexRT[Ch2]/3;
				motor[FL] = -vexRT[Ch2]/3;
			}
		}
		else
		{
			if (half==false)//Check if drive toggles half speed.
			{
				motor[BR] = vexRT[Ch2]; //give drive direct control.
				motor[FR] = vexRT[Ch2];
				motor[BL] = vexRT[Ch3];
				motor[FL] = vexRT[Ch3];
			}
			else if(half ==true)
			{
				motor[BR] = vexRT[Ch2]/3;//give drive control but all motor maxes are a third of their orignal max.
				motor[FR] = vexRT[Ch2]/3;
				motor[BL] = vexRT[Ch3]/3;
				motor[FL] = vexRT[Ch3]/3;
			}
		}




}


void clearmotor()
{
	motor[FR]=0;
	motor[FL]=0;
	motor[BR]=0;
	motor[BL]=0;
}

void forward(int ticks)
{
		ticks=ticks+100;
		nMotorEncoder[encoderLeft]=0;
    while(SensorValue(encoderLeft)<ticks)
    {
      motor[FL]=118;
    	motor[FR]=118;
    	motor[BL]=118;
    	motor[BR]=118;
    }
  motor[FL]=0;
	motor[FR]=0;
	motor[BL]=0;
	motor[BR]=0;
}

void forwards(int s)
{
      motor[FL]=118;
    	motor[FR]=118;
    	motor[BL]=118;
    	motor[BR]=118;
    	wait(s);
    	motor[FL]=0;
    	motor[FR]=0;
    	motor[BL]=0;
    	motor[BR]=0;
}

void backward(int ticks)
{
		ticks=ticks+100;
    nMotorEncoder[encoderLeft] = 0;
    int enctick=SensorValue(encoderLeft);
    while(enctick>-ticks)
    {
    motor[FL]=-118;
		motor[FR]=-118;
		motor[BL]=-118;
		motor[BR]=-118;
    }
	motor[FL]=0;
	motor[FR]=0;
	motor[BL]=0;
	motor[BR]=0;
}


void backwards(int s)
{
      motor[FL]=-118;
    	motor[FR]=-118;
    	motor[BL]=-118;
    	motor[BR]=-118;
    	wait(s);
    	motor[FL]=0;
    	motor[FR]=0;
    	motor[BL]=0;
    	motor[BR]=0;
}





//Need to caluclate the number of degreesper tick!!!
void correctturn(int degrees) //add sensor ticks per degrees
{
	//CONVERT DEGREES TO TICKS!!!
		int ticks=degrees*3.44;
    int i=SensorValue( encoderLeft );//named encoder

    //CHANGE THE 1 LATERRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    if(1<180)
    {
        while (i < ticks)
        {
            motor[FL]=118;
            motor[BL]=118;
            motor[FR]=-118;
            motor[BR]=-118; //<- need to check how long is 1 tick.
        }
    }
    else
    {
        //subtract amount of ticks in 180 degrees
        int ticks= 1-ticks;
        while (i < ticks)
        {
            motor[FL]=-118;
            motor[BL]=-118;
            motor[FR]=118;
            motor[BR]=118;
        }
    }
}
void turnright(int ticks)
{
	SensorValue[encoderLeft]=0;
	while(SensorValue[encoderLeft]<ticks)
	{
		motor[FL]=118;
		motor[BL]=118;
		motor[FR]=-118;
		motor[BR]=-118;
	}
}

void turnleft(int ticks)
{
	SensorValue[encoderRight]=0;
	while(SensorValue[encoderRight]<ticks)
	{
		motor[FL]=-118;
		motor[BL]=-118;
		motor[FR]=118;
		motor[BR]=118;
	}
}


void turnr(float seconds)
{
	motor[FL]=118;
	motor[BL]=118;
	motor[FR]=-118;
	motor[BR]=-118;
	wait(seconds);
	clearmotor();
}
void turnl(float seconds)
{
	motor[FL]=-118;
	motor[BL]=-118;
	motor[FR]=118;
	motor[BR]=118;
	wait(seconds);
	clearmotor();
}


void raisearm(int ticks)
{
	while(SensorValue[armP]<ticks)
	{
		motor[leftArm]=118;
		motor[rightArm]=118;
	}
	motor[leftArm]=0;
	motor[rightArm]=0;
}

void lowerarm(float seconds)
{
      motor[leftArm]= -118;
			motor[rightArm]= -118;
   		wait(seconds);
    	motor[leftArm]= -0;
			motor[rightArm]= -0;
}


/*
void lowerarm(int ticks)
{
	while(sensorValue[armP]>ticks)
	{
		motor[FLarm]=-118;
		motor[FRarm]=-118;
		motor[BLarm]=-118;
		motor[BRarm]=-118;
	}
	motor[FLarm]=0;
	motor[FRarm]=0;
	motor[BLarm]=0;
	motor[BRarm]=0;
}
*/

void increment(int lev) //raising the arm to certain levels
{
		int level[]={1500,1685,1965,2235,2615,3030,1270};
    if(SensorValue[armP]<level[lev])
    {
        raisearm(level[lev]);
    }
}

void taketower()
{
				int level[]={1322,1685,1965,2235,2615,3030,1270};
        backward(10);
        increment(level[6]);
        forward(25);
        backward(100);
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


void autonomous()  //Programs are chosen by the value of the dial potentiometer.
{

		int position=SensorValue[dial];

		SensorValue(encoderLeft)=0;
		SensorValue(encoderRight)=0;



//11111111111111111111111111111111111111111111111111111111111111111111111111
//Blue side block
		if (position>=0&&position<550)
		{

		}



//2222222222222222222222222222222222222222222222222222222222222222222222222
//Blue side skyrise
		else if (position>=550&&position<1850)
		{

		}


//33333333333333333333333333333333333333333333333333333333333333333333333333
//Red side cube
    else if(position>=1850&&position<3350)
    {

	  }


//444444444444444444444444444444444444444444444444444444444444444444444444444
	  //Red side skyrise
	  else if(position>=3350&&position<5000)
	  {

		}
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	bool half=false;
	bool switchdirection=true;
	int buttonToggleState8r = 0;
  int buttonPressed8r = 0;
	int buttonToggleState7l = 0;
  int buttonPressed7l = 0;
  int buttonToggleState7U = 0;
  int buttonPressed7U = 0;
	while (true)
{


//Toggle half speed---------------------------------------------------------------
		if( vexRT[ Btn7L ] == 1 )
  {
      if( ! buttonPressed7l )
      {
      	// change the toggle state
      	buttonToggleState7l = 1 - buttonToggleState7l;

        // Note the button is pressed
        buttonPressed7l = 1;
      }
  }
  else
  {
	  // the button is not pressed
	   buttonPressed7l = 0;
	}
  // Now do something with our toggle flag
  if( buttonToggleState7l )
  {
      half=true;
  }
  else
  {
      half=false;
	}


//Switch Direction------------------------------------------------------
		if( vexRT[ Btn7U ] == 1 )
  {
      if( ! buttonPressed7U )
      {
      	// change the toggle state
      	buttonToggleState7U = 1 - buttonToggleState7U;

        // Note the button is pressed
        buttonPressed7U = 1;
      }
  }
  else
  {
	  // the button is not pressed
	   buttonPressed7U = 0;
	}
  // Now do something with our toggle flag
  if( buttonToggleState7U )
  {
      switchdirection=true;
  }
  else
  {
      switchdirection=false;
	}



	/* Toggle pneumatics------------------------------------------------
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
      lock();
  }
  else
  {
      release();
	}
	*/


	//DRIVE-----------------------------------------------------


		drive(half, switchdirection);
		motor[leftArm] = 0;
  	motor[rightArm] = 0;


  	//ARM MOTION----------------------------
		while(vexRT[Btn6D] == true)
		{
			if(SensorValue[touchdownl]==1)
			{
						motor[leftArm] = 0;
						motor[rightArm]=0;
						drive(half,switchdirection);
			}
			else
			{
				motor[leftArm] = 118;
	  		motor[rightArm] = 118;
  			drive(half,switchdirection);
  		}
		}


		while(vexRT[Btn5D] == true)
		{
			if(SensorValue[touchupl]==1)
			{
						motor[leftArm] = 0;
						motor[rightArm] = 0;
						drive(half,switchdirection);
			}
			else
			{
				motor[leftArm] = -118;
	  		motor[rightArm] = -118;
	  		drive(half,switchdirection);
  		}

		}




		//INTAKE MOTION-------------------------------------
		while(vexRT[Btn6U] == true)
		{
				motor[intake1] = 118;
	  		motor[intake2] = 118;
	  		drive(half,switchdirection);
		}
		while(vexRT[Btn5U] == true)
		{
				motor[intake1] = -118;
	  		motor[intake2] = -118;
	  		drive(half,switchdirection);
		}
	}
}
