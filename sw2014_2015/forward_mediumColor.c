#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     Color,          sensorI2CHiTechnicColor)
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

#define FORWARD_1 0
#define FORWARD_2 1
#define AUTO_SCORE 2
#define GRAB 3
#define TURN 4
#define BACKWARD 5
#define STOP 6
#define BACKWARD_2 7
#define DELAY 8

int sm = FORWARD_1;


#define ENCODER_SET 1
#define MOVE 2

int sm2 = ENCODER_SET;

int count =0;

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

#pragma DebuggerWindows("JoystickGame")

task main()
{

  initializeRobot();

  waitForStart();

  while(true)
  {
    switch(sm)
		{


		case FORWARD_1:

		writeDebugStreamLine("right=%d", nMotorEncoder[rtWheelMotor]);
		writeDebugStreamLine("left=%d", nMotorEncoder[ltWheelMotor]);
		writeDebugStreamLine("sm=%d", sm);

		  if( forward(20,8500)==true)
		  {
		  sm=FORWARD_2;
			}

		break;

				case FORWARD_2:

		writeDebugStreamLine("right=%d", nMotorEncoder[rtWheelMotor]);
		writeDebugStreamLine("left=%d", nMotorEncoder[ltWheelMotor]);
		writeDebugStreamLine("sm=%d", sm);

		  if( forward(20,2100)==true)
		  {
		  sm=AUTO_SCORE;
			}

		break;


  	case AUTO_SCORE:

  	Auto_Score();
  	if(Auto_Score())
		{
			sm=GRAB;
		}

		break;

		case GRAB:

			servo[clamp]=100;

			wait1Msec(1000);

			sm=TURN;


		break;

		case TURN:

			if(Turnright(25,20)==true)
			{
			sm=BACKWARD;
			sm2=ENCODER_SET;
			}

		break;

		case BACKWARD:

		backward(15,12000);

		if(SensorValue[Color]==9||SensorValue[Color]==2)
		{
		sm=STOP;
		}

		break;

		case STOP:

		motor[rtWheelMotor]=0;
		motor[ltWheelMotor]=0;
		servo[clamp]=140;

		break;


				case BACKWARD_2:

		if(backward(25,1000)==true)
		{
		sm=STOP;
		}

		break;


  	}
	}
	wait1Msec(50);
}