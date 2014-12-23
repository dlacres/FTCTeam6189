/*#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rtWheelMotor,  tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     ltWheelMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     sweeper,       tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

// As a ROLE I want to WHAT_I_WANT so that VALUE_I_GET
//
//======================================================//

void forward_intizalize()
	{
	nMotorEncoder[ltWheelMotor]=0;
	nMotorEncoder[rtWheelMotor]=0;
	}

bool backward(int speed, int distance){
	while(true)
	{

		if(nMotorEncoder[ltWheelMotor]>-distance)
		{
		motor[rtWheelMotor]=-speed;
		motor[ltWheelMotor]=-speed;
		}
		else
		{
		motor[rtWheelMotor]=0;
		motor[ltWheelMotor]=0;
		break;
		}
	}
return(true);
}

bool forward(int speed, int distance){
	while(true)
	{
		if(nMotorEncoder[ltWheelMotor]<distance)
		{
		motor[rtWheelMotor]=speed;
		motor[ltWheelMotor]=speed;
		}
		else
		{
		motor[rtWheelMotor]=0;
		motor[ltWheelMotor]=0;
		break;
		}
	}
return(true);
}
// ==================UNIT TEST==========================//

/*#ifndef NO_UNIT_TEST
#include "i_debug.c"
int timeLeft=0; // A global variable used to adjust the time it takes to complet the while loop
int i=0;
#define FOREGROUND_MS 50 //The while loop takes 50 MS to run. This means the software runs 20 times per second
task main(){
	nMotorEncoder[ltWheelMotor]=0;
	// Initialize variables here //
	int myInt=0;
	int in=0;
	int out=0;
	//Debug2File(); //Send the debug information to the file debug.txt
	//Debug2NXT();  //Send the debug information to the NXT screen
	Debug2Stream(); //Send the debug information to the PC Screen

	// End of initialize //
	while(true){
		clearTimer(T1);
		hogCPU(); //Prevent other tasks from running when this one is.
		// ------------- Put Unit Test code here -------------------//
		// xxxxxxx [] Describe test 1 here. Put an X inside of [] when the test passes.
		// xxxxxxx [] Describe test 2 here. Put an X inside of [] when the test passes.
int clicks_ft =1000;
		// USAGE NOTES:
		//   The units for a are encoder clicks
		//   Set #define NO_UNIT_TEST
		if (i<5) in=0;
		if (i<10) in=1;

	Forward(-25,-1*clicks_ft);

		DebugInt("%d",nMotorEncoder[ltWheelMotor]);


		i+=1; // Increment the frame counter for unit test
		// ------------- Unit code test is done here ---------------//
		DebugPrint();
		timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
		releaseCPU(); // Let other tasks run now.
		wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	}// While Loop
}// Main Task
#endif*/
