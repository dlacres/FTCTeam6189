#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     ir,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,          IrMotor,       tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rtWheelMotor,  tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     ltWheelMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     sweeper,       tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    score,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "i_forward.c"
#include "i_turn.c"

#define FORWARD 0
#define READ_IR 1
#define DRIVE_POSITION1 2
#define DRIVE_POSITION2 3
#define DRIVE_POSITION3 4
#define STOP 5
#define IR_0 6
#define MOVE_SERVO 7


int sm=MOVE_SERVO;
bool forward_true;
bool turn_true;


task main()
{
forward_initizalize();
servo[score]=200;
	while(true)
	{

		writeDebugStreamLine("sm=%d, encoder=%d, ir=%d, motor=%d",sm,nMotorEncoder[ltWheelMotor],SensorValue[ir], nMotorEncoder[IrMotor]);

		switch(sm)
		{
		case FORWARD:
		 forward_true=forward(25,4250);
		  if(forward_true==true)
		  {
		  sm=MOVE_SERVO;
			}
		break;

	case READ_IR:

	if(nMotorEncoder[IrMotor]==156)
		{
		sm=DRIVE_POSITION1;
		}

	if(nMotorEncoder[IrMotor]==228)
		{
		sm=DRIVE_POSITION2;
		}

	if(nMotorEncoder[IrMotor]==252)//244
		{
		sm=DRIVE_POSITION3;
		}

		/*	if(SensorValue[IR]==0)
		{
		//sm=IR_0;
		}*/

	break;

	case DRIVE_POSITION1:
		turn_true=Turnleft(25,90);
		if(turn_true==true)
		{
		sm=STOP;
		}
		break;

	case DRIVE_POSITION2:
		turn_true=Turnright(25,90);
		if(turn_true==true)
		{
		sm=STOP;
		}
		break;

	case DRIVE_POSITION3:
		turn_true=Turnleft(25,180);
		if(turn_true==true)
		{
		sm=STOP;
		}
		break;

		case STOP:
		motor[rtWheelMotor]=0;
		motor[ltWheelMotor]=0;
		break;

		case IR_0:
		sm=READ_IR;
		break;

		case MOVE_SERVO:

		motor[IrMotor]=10;

		if(SensorValue[ir]<5&&SensorValue[ir]!=0)
		{
		motor[IrMotor]=0;
		sm=READ_IR;
		}

		break;
		}
		wait1Msec(50);
	}
}
