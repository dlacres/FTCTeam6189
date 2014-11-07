#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rtWheelMotor,  tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     ltWheelMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     sweeper,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)

void RaiseArm(int spd,int dist)
{
	if(nMotorEncoder[lift]>dist)
		motor[lift]=0;
	else
		motor[lift]=spd;
	return;
}
// ==================UNIT TEST==========================//
#ifndef NO_UNIT_TEST
#include "i_debug.c"
int timeLeft=0; // A global variable used to adjust the time it takes to complet the while loop
int i=0;
#define FOREGROUND_MS 50 //The while loop takes 50 MS to run. This means the software runs 20 times per second
task main(){
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
		// xxxxxxx [] Lift arm to 12 inches.
		// xxxxxxx [] Lift arm to 14 inches.
		// xxxxxxx [] Drop arm to 12 inches.
		// xxxxxxx [] Drop arm to 0 inches.

		// USAGE NOTES:
		//   The units for a are encoder clicks
		//   Set #define NO_UNIT_TEST
		#define SPEED 25
		#define KD 120
		if (i<3*20) {
			RaiseArm(SPEED,12*KD);
			DebugInt("Speed",SPEED);
		} else if (i<5*20) {
			RaiseArm(SPEED,14*KD);
			DebugInt("Speed",SPEED);
		}else if (i<7*20) {
			RaiseArm(-SPEED,12*KD);
			DebugInt("Speed",-SPEED);
		} else if (i<10*20) {
			RaiseArm(-SPEED,0*KD);
			DebugInt("Speed",-SPEED);
		}

		DebugInt("Dist",nMotorEncoder[lift]);

		i+=1; // Increment the frame counter for unit test
		// ------------- Unit code test is done here ---------------//
		DebugPrint();
		timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
		releaseCPU(); // Let other tasks run now.
		wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	}// While Loop
}// Main Task
#endif
