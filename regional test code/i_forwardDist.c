//#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
//#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
//#pragma config(Motor,  mtr_S1_C1_1,     ltWheelMotor,  tmotorTetrix, PIDControl, reversed, encoder)
//#pragma config(Motor,  mtr_S1_C1_2,     rtWheelMotor,  tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard
/*====================Add / for debug======================//
#include "i_limit.c"
#include "i_rateLimit.c"
#include "i_debug.c"
//*/

//Story: As a software designer I want to move the robot at a constant speed for a specific distance (forward or backward) in inches
//   without slipping the wheels so I can follow a path.
//Dependencies: i_limit.c, i_rateLimit.c
//Usage:
// Call at a periodic rate of 20hz.
// Motor PID control is on and encoders are enabled one wheel is reversed.
// Robot has a left wheel drive and a right wheel drive motor
#define IN2CLK 240
#define STOP_RATE 30 // Smaller numbers stop faster
#define START_RATE 5 // Larger numbers start faster
/*
#define FWD_SPD 50
#define FWD_DIST 12*/
//-------------------Call to reset the motor postion----------------------//
// ForwardDistReset(rightMotorNameInt, leftMotorNameInt);
int forwardDistZ1=0; // This is a global variable used to maintain state history.
void ForwardDistReset(int rightMotorName, int leftMotorName){
	  forwardDistZ1=0;
  	nMotorEncoder[rightMotorName] = 0;
  	nMotorEncoder[leftMotorName] = 0;
}

//-----------------Call to calculate the speed command--------------------//
// int moveDistClickInt = nMotorEncoder[rightMotorName] + nMotorEncoder[leftMotorName];
// mtrSpdCmdInt = ForwardDist(distCmdInchInt, distInt, speedCmdInt);
long ForwardDist(long distCmdInch, long distClicks, long speedCmd){
  long mtrSpdCmd,moveDistLeft,moveDistSpdCmd;

  moveDistLeft = (distCmdInch*IN2CLK - distClicks)/STOP_RATE;
//  DebugInt("err",moveDistLeft);
  moveDistSpdCmd = LimitSym(moveDistLeft, speedCmd); // Limit to the max speed desired
	mtrSpdCmd = RateLimit(moveDistSpdCmd, START_RATE, forwardDistZ1); // This is used to ramp the command up slowly. The command will change 1*1000/TASKTIME_MS each second.

	return(mtrSpdCmd);
}
//------------------Code to test goes here-------------------//
/*====================Add / for debug======================//
// Add this code to a while loop in main
// Unit Test
// [x] drive forward to specific inch distance
// [x] drive backward to a specific inch distance

#define FOREGROUND_MS 50
task Foreground(){
  int timeLeft,speedCmd;

	//--------------------INIT Code---------------------------//
  ForwardDistReset((tMotor)rtWheelMotor, (tMotor)ltWheelMotor);
  ForwardDistSet(DIST);
	//--------------------End INIT Code-----------------------//

	while(true){
		ClearTimer(T1);
		hogCPU();
		//--------------------Robot Code---------------------------//

		int moveDistClick = nMotorEncoder[rtWheelMotor] + nMotorEncoder[ltWheelMotor];
		DebugInt("dist",moveDistClick);

    speedCmd = ForwardDist(moveDistClick, SPD);

    DebugInt("spd",speedCmd);

		motor[rtWheelMotor]=motor[ltWheelMotor]=speedCmd;

		//--------------------------End Robot Code--------------------------//
		// Wait for next itteration
	  timeLeft=FOREGROUND_MS-time1[T1];
	  releaseCPU();
	  wait1Msec(timeLeft);
	}// While
}//Foreground
task main()
{
	int iFrameCnt=0;
	DebugSkip(1);

  StartTask(Foreground, 255);

  while(true){

  	//-----------------Start i_debug.c output------------------//
  	if (debugRun==true){// Do not send out a stream if Debug is not called
			if (debugSkip<debugSkipI++){
	  		writeDebugStream("[%d] ",iFrameCnt);
	  		for (int i=0; i<debugI; ++i)
	  			writeDebugStream("%5s=%5d",debugStr[i],debugInt[i]);

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
//*/
