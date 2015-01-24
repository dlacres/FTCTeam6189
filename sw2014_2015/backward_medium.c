#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     rtWheelMotor,  tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     ltWheelMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     sweeper,       tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    score,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//



#define BACKWARD_1 0
#define TURN_1 1
#define AUTO_SCORE 2
#define GRAB 3
#define TURN_2 4
#define BACKWARD_2 5
#define STOP 6

int sm = BACKWARD_1;


#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "i_forward.c"
#include "i_score.c"
#include "i_clamp.c"
#include "i_turn.c"

void initializeRobot()
{
servo(dump)=195;
servo(clamp)=0;
servo[score]=60;

forward_initialize();

  return;
}

#pragma DebuggerWindows("JoystickGame")

task main()
{
  initializeRobot();

  waitForStart();

  while(true)
  {
  		switch(sm)
		{
		case BACKWARD_1:

		 backward(50,8500);

		  sm=TURN_1;

		break;

		case TURN_1:

		Turnleft(25,180);

		forward(10,2500);

		sm=AUTO_SCORE;

		break;

  	case AUTO_SCORE:

  	Auto_Score();
  	if(Auto_Score())
		{
		sm=GRAB;
		}

		case GRAB:

			servo[clamp]=70;

		wait1Msec(1000);

		sm=TURN_2;

		break;

		case TURN_2:

		Turnleft(25,5);

		sm=BACKWARD_2;


		break;

		case BACKWARD_2:

		backward(25,16000);

		sm=STOP;


		break;

		case STOP:

		motor[rtWheelMotor]=0;
		motor[ltWheelMotor]=0;

		break;
  	}
	}
}