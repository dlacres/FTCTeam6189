#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rtWheelMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     ltWheelMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     sweeper,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    clamp,                tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "i_debug.c"
#include "i_limit.c"
#include "i_rateLimit.c"
#include "i_direction.c"
#include "i_forwardDist.c"
//--------------------Path definition----------------------//
#define SPD 40;
#define DIST_IDX 0
#define DIR_IDX 1
#define SPD_IDX 2
int pathIdx=0;
// dist, dir, spd
#define PATH_MAX 2
int path[][]={
		{12, 0, 50},
		{12, 90, 50},
		{12, 0, 50}};
//*--------------------Foreground---------------------------//
// Story: As a player, I want the robot to follow a path so i can score autonomous points in a game
// [] Follow path stored in an array
// [] Stop at the end of the path
#define FOREGROUND_MS 50
task Foreground(){
  int timeLeft;
	while(true){
		ClearTimer(T1);
		hogCPU();
		//--------------------Robot Code---------------------------//

		int robotDist = nMotorEncoder[rtWheelMotor] + nMotorEncoder[ltWheelMotor];
		int robotDir  = nMotorEncoder[ltWheelMotor] - nMotorEncoder[rtWheelMotor];

		// Calculate the speed and direction commands
    int speedCmd = ForwardDist(path[pathIdx][DIST_IDX], robotDist, path[pathIdx][SPD_IDX]);
		int dirCmd=Direction(path[pathIdx][DIR_IDX], robotDir);

		DebugInt("spd",speedCmd);
		DebugInt("dir",dirCmd);

		// Calculate when to move to the next path index
		if (abs(speedCmd)<2 && abs(dirCmd)<2) pathIdx++;
		int s=sizeof(path)/sizeof(path[0])-1;
		DebugInt("siz",s);
		if (pathIdx>s) pathIdx=s;

		motor[ltWheelMotor]=speedCmd+dirCmd;
		motor[rtWheelMotor]=speedCmd-dirCmd;
		//--------------------------Robot Code--------------------------//
		// Wait for next itteration
	  timeLeft=FOREGROUND_MS-time1[T1];
	  releaseCPU();
	  wait1Msec(timeLeft);
	}// While
}//Foreground
task main()
{
	int iFrameCnt=0;

	//--------------------INIT Code---------------------------//
  ForwardDistReset((tMotor)rtWheelMotor, (tMotor)ltWheelMotor);
	DirectionReset();
	//--------------------End INIT Code--------------------------//

  StartTask(Foreground, 255);

  while(true){

  	//-----------------Start i_debug.c output------------------//
  	if (debugRun==true){// Do not send out a stream if Debug is not called
			if (debugSkip<debugSkipI++){
	  		writeDebugStream("[%d] ",iFrameCnt);
	  		for (int i=0; i<debugI; ++i)
	  			writeDebugStream(" %5s=%5d",debugStr[i],debugInt[i]);

	  		writeDebugStream("\n");
	  		debugSkipI=0;
			}
			iFrameCnt++;
			debugRun=false;
			debugI=0; //Clear the debug buffer
		}
		//------------------Stop i_debug.c output----------------------//

	}// While
}// Main
