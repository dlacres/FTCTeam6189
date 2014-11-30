#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rtWheelMotor,  tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     ltWheelMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    hook,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
// As a driver I use the right joystick to drive
//  Feature: Lookup is a table lookup routine that can shape the output joystick
//  To use, remove the comments.


#include "JoystickDriver.c"
//#include "i_lookup.c"

#pragma DebuggerWindows("joystickSimple");

int jstickX;
int jstickY;

task main()
{
	while(true)
	{
  	getJoystickSettings(joystick);

		//jstickX = Lookup1(joystick.joy1_x2);
		//jstickY = Lookup1(joystick.joy1_y2);

		// ------- Control the drive motors ----------//
		//motor[ltMotor]=(jstickY + jstickX);
		//motor[rtMotor]=(jstickY - jstickX);

		motor[rtWheelMotor]=(joystick.joy1_y2-joystick.joy1_x2)/2;
		motor[ltWheelMotor]=(joystick.joy1_y2+joystick.joy1_x2)/2;

		writeDebugStreamLine("%d", nMotorEncoder[rtWheelMotor]);

		wait1Msec(50);

		/*if (joy1Btn(1))
		{
			servo[hook]=20;
		}
	
		else
		{
			servo[hook]=160;
		}*/
	}
}