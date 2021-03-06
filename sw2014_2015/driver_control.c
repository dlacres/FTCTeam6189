#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     rtWheelMotor,  tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     ltWheelMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     tracks,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    score,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    sweeper,              tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// As a driver I use the right joystick to drive
//  Feature: Lookup is a table lookup routine that can shape the output joystick
//  To use, remove the comments.
//
#include "JoystickDriver.c"
#include "i_clamp.c"
#include "i_dump.c"
#include "i_arm.c"
#pragma DebuggerWindows("JoystickGame")
#include "i_lookup.c"
#include "i_deadZone.c"
#include "i_sweeper.c"

int hi =5;
int jstickX;
int jstickY;
int gyroBias=0;

void initializeRobot()
{


	RaiseArmInit();

	servo(dump)=100;
	servo(clamp)=180;
	servo(score)=190;
	servo(sweeper)=127;

	for (int i=0; i<5; i++){
		gyroBias = SensorValue[Gyro]+gyroBias;
		wait1Msec(50);
	}
	gyroBias=gyroBias/5;


	return;
}
task main()
{
	initializeRobot();
	waitForStart();

	while(true)
	{
		writeDebugStreamLine("%d",(jstickY + jstickX));
		getJoystickSettings(joystick);

		/////////Joystick 1//////////

		jstickX = Lookup1(joystick.joy1_x2) - DeadZone((SensorValue[Gyro]-gyroBias)/2,5); // Gyro
		jstickY = Lookup1(joystick.joy1_y2);

		// ------- Control the drive motors ----------//

		motor[ltWheelMotor]=(jstickY + jstickX);
		motor[rtWheelMotor]=(jstickY - jstickX);

		if(joy1Btn(6)&&joy1Btn(5))
		{
		nMotorEncoder[lift]=0;
		}

		////////Joystick 2//////////

		motor[tracks]=joystick.joy2_y2;

			if(joy2Btn(6)&&joy2Btn(5))
			{
			motor[lift]=DeadZone((joystick.joy2_y1)/2,5);
			writeDebugStreamLine("%d", hi);
			}


			else if( nMotorEncoder[lift]<13950 && joystick.joy2_y1 >= 0)
			{
				motor[lift]=DeadZone((joystick.joy2_y1)/2,5);
				writeDebugStreamLine("%d,%d 1", nMotorEncoder[lift],joystick.joy2_y1);
			}
			else if( nMotorEncoder[lift]>0 && joystick.joy2_y1 <= 0)
			{
				motor[lift]=DeadZone((joystick.joy2_y1)/2,5);
				writeDebugStreamLine("%d,%d 2", nMotorEncoder[lift],joystick.joy2_y1);
			}
			else
			{
				motor[lift]=0;
				writeDebugStreamLine("%d,%d 3", nMotorEncoder[lift],joystick.joy2_y1);
  		}



		if(joy2Btn(7))
		{
			Clampgoal(true);
		}
		else
		{
			Clampgoal(false);
		}

		if(joy2Btn(8))
		{
			DumpBucket(true);
		}
		else
		{
			DumpBucket(false);
		}

		if(joy2Btn(1))
		{

		SweeperControl(true);
		}

		if(joy2Btn(2))
		{

		SweeperControl(false);
		}

		wait1Msec(50);
	}
}
