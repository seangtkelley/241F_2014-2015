#pragma config(Sensor, in1,    armP,           sensorPotentiometer)
#pragma config(Sensor, in2,    dial,           sensorPotentiometer)
#pragma config(Sensor, dgtl1,  er,             sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  el,             sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  limitswitch,    sensorTouch)
#pragma config(Sensor, dgtl6,  pn,             sensorDigitalOut)
#pragma config(Motor,  port2,           FR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           BR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           FL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           BL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           TRarm,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           TLarm,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           BRarm,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           BLarm,         tmotorVex393_MC29, openLoop, reversed)


task main()
{
int ticks=10;
	SensorValue[el]=0;
	while(abs(SensorValue[el])<ticks)
	{
		motor[FL]=118;
		motor[BL]=118;
		motor[FR]=-118;
		motor[BR]=-118;
	}

}
