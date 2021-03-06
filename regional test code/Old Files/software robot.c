#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     gyro,           sensorNone)
#pragma config(Sensor, S3,     epod,           sensorSONAR)
#pragma config(Sensor, S4,     Color,          sensorI2CHiTechnicColor)
#pragma config(Motor,  motorA,          leftsweeper,   tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          light,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rightmotor,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftmotor,     tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

#include "joystickShaper.c"

#include "i_limit.c"
#include "i_flipperArm_driver.c"
void initializeRobot()
{

}

//if
task main()
{
	initializeRobot();

  waitForStart();

	int jstickX = 0;
	int jstickY = 0;
	while(true)
	{


		getJoystickSettings(joystick);

		jstickX = jsShape(joystick.joy1_x2)*1/2;// makes driving less touchy... hopefully
		jstickY = jsShape(joystick.joy1_y2)*1/2;// same here

    motor[leftmotor] = (-jstickY - jstickX)*3/2; // uses revised values to make driving on one joystick
   	motor[rightmotor] = (-jstickY + jstickX)*3/2;// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//    motor[leftmotor] = (-jstickY +jstickX); // uses revised values to make driving on one joystick
//   	motor[rightmotor] = (-jstickY -jstickX);// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//		writeDebugStreamLine("Color=%d,light=%d",SensorValue[S4],motor[light]);
//		writeDebugStreamLine("rspd = %d",motor[rightmotor] );
//		writeDebugStreamLine("lspd = %d",motor[leftmotor] );// max power is 50
		writeDebugStreamLine("JY = %d",jstickY );// max power is 50
		writeDebugStreamLine("JX = %d",jstickX );// max power is 50

        wait1Msec(20);
  }

 motor[rightmotor] = 0;
 motor[leftmotor] = 0;

}
