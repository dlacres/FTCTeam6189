#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     rtWheelMotor,  tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     ltWheelMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     sweeper,       tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    score,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    ir,                   tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define FORWARD 0
#define IR 1
#define POSITION_1 2
#define POSITION_2 3
#define POSITION_3 4
#define FORWARD_2 5
#define STOP 6
#define POSITION_2_PH_1 7
#define POSITION_2_PH_2 8
#define POSITION_2_PH_3 9
#define POSITION_2_PH_4 10
#define POSITION_3_PH_1 11
#define POSITION_3_PH_2 12
#define POSITION_3_PH_3 13
#define POSITION_3_PH_4 14
#define POSITION_1_PH_1 15

int sm = FORWARD;

#define ENCODER_SET 0
#define MOVE 1

int sm2 = ENCODER_SET;

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "i_forward.c"
#include "i_score.c"
#include "i_clamp.c"
#include "i_turn.c"

void initializeRobot()
{
servo(dump)=100;
servo(clamp)=0;
servo[score]=120;

forward_initizalize();


  return;
}

task main()
{

  initializeRobot();

  waitForStart();

  while(true)
  {
    switch(sm)
		{

		case FORWARD:
		servo[score]=230;
		writeDebugStreamLine("%d",SensorValue[IR]);
		if (forward(50,4000)==true)
		{
		wait1Msec(1000);
		sm=IR;
		}

		break;

		case IR:

		writeDebugStreamLine("%d",SensorValue[IR]);

		if (SensorValue[IR]==3)
		{
		sm=POSITION_1;
		}

		if (SensorValue[IR]==5||SensorValue[IR]==4)
		{
		sm=POSITION_2;
		}

		if (SensorValue[IR]==7||SensorValue[IR]==6)
		{
		sm=POSITION_3;
		}

		break;

		case POSITION_1:

		if(forward(25,250)==true)
		{
		sm=POSITION_1_PH_1;
		}

		break;

			case POSITION_1_PH_1:

		if(Turnright(25,70)==true)
		{
		sm=FORWARD_2;
		}

		break;

		case POSITION_2:

	if (backward(50,500)==true)
	{
	sm=POSITION_2_PH_1;
	}

		break;

		case POSITION_3:

	if (backward(50,500)==true)
	{
	sm=POSITION_3_PH_1;
	}


		break;

		case FORWARD_2:

		if(forward(50,3000)==true)
		{
		sm=STOP;

		}

		break;

		case STOP:

		motor[rtWheelMotor]=0;
		motor[ltWheelMotor]=0;

		break;

		case POSITION_2_PH_1:

		if(Turnright(25,80)==true)
		{
			sm=POSITION_2_PH_2;
		}

		break;


		case POSITION_2_PH_2:

		if(forward(50,1000)==true)
		{
			sm=POSITION_2_PH_3;
		}

		break;

		case POSITION_2_PH_3:

		if(Turnleft(25,50)==true)
		{
			sm=POSITION_2_PH_4;
		}

		break;

		case POSITION_2_PH_4:

		if(forward(50,4000)==true)
		{
			sm=STOP;
		}

		break;


		case POSITION_3_PH_1:

		if(Turnright(25,70)==true)
		{
			sm=POSITION_3_PH_2;
		}

		break;

		case POSITION_3_PH_2:

		if(forward(50,2850)==true)
		{
			sm=POSITION_3_PH_3;
		}

		break;

		case POSITION_3_PH_3:


		if(Turnleft(25,70)==true)
		{
			sm=POSITION_3_PH_4;
		}

		break;

		case POSITION_3_PH_4:

		if(forward(50,4000)==true)
		{
			sm=STOP;
		}

		break;

		}
	wait1Msec(50);
	}
}
