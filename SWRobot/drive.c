#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     rtMotor,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     ltMotor,       tmotorTetrix, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

//#include "i_limit.c"
//#include "i_flipperArm_driver.c"
#include "i_PID3.c"
#include "joystickShaper_orignal.c"

#pragma DebuggerWindows ("debugStream")// Bring up the debug stream window
int count=0;
int timeLeft=0; // A global variable that sticks around each frame
int dirOld=0;

// ------------------------Foreground Task -----------------------------//
// Run every second
#define FOREGROUND_MS 50
task main(){
  //---------------------------INIT-----------------------------------//
	Pid_Init1();
	Pid_Init2();
  //---------------------------END INIT-------------------------------//
	while(true){
		ClearTimer(T1);
		hogCPU(); //Prevent other tasks from running when this one is.
		//writeDebugStreamLine("Foreground\n"); //Let me know when the foreground runs
	  count=count+1; // Count the number of times the foreground runs.

	  //--------------------------FOREGROUND------------------------------------//

		int jstickX = 0;
		int jstickY = 0;

		getJoystickSettings(joystick);

		jstickX = jsShape(joystick.joy1_x2);
		jstickY = jsShape(joystick.joy1_y2);

		motor[ltMotor]=Pid1(-jstickY - jstickX);
		motor[rtMotor]=Pid2(-jstickY + jstickX);

	  //--------------------------END FOREGROUND--------------------------------//

//	 	if (count==1){
//	  	writeDebugStreamLine("SpdCmd[%f],Kp[%f],Ki[%f],Kd[%f]",spdCmd,Kp,Ki,Kd);
//	  	writeDebugStreamLine("Count,timeLeft,ErrorKp,lpError,distance,Speed,IntegralKi,output,failed");
//	  }
		writeDebugStreamLine("%3i,%3i",jstickX,jstickY);

		timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
	  releaseCPU(); // Let other tasks run now.
	  wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	}// While Loop
}// Foreground Main Task*/
