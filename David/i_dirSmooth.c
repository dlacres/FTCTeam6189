#pragma config(Hubs,  S1, MatrxRbtcs, none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_Matrix_S1_1, ltWheelMotor,  tmotorMatrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_Matrix_S1_2, rtWheelMotor,  tmotorMatrix, PIDControl, encoder)
#pragma config(Motor,  mtr_Matrix_S1_3, motorF,        tmotorMatrix, openLoop)
#pragma config(Motor,  mtr_Matrix_S1_4, motorG,        tmotorMatrix, openLoop)
#pragma config(Servo,  srvo_Matrix_S1_1, servo1,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_2, servo2,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_3, servo3,               tServoNone)
#pragma config(Servo,  srvo_Matrix_S1_4, servo4,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

//*====================Add / for debug======================//
#include "i_debug.c"
#include "i_rateLimit.c"
#include "i_limit.c"
//*/
// Story: As a software designer I want to smoothly change the direction the robot goes without stopping.
// Assume that the left motor is called motorLt and the right motor is
// Dependency: i_rateLimit.c, i_limit.c
// Usage: A positive dirCmd is turn right. Returns the direction command.
// Tuning:
//#define DIR_RL 100
//------------------Direction Controller-----------------------//
//int rbtDirClkInt=(int)(nMotorEncoder[ltWheelMotor] - nMotorEncoder[rtWheelMotor]);
//dirCmdInt=Direction(dirCmdInt, rbtDirClkInt);
#define DIR_LIMIT 15 // The max diff motor command for the turn
#define DIR_KP 25
int DirSmooth(int dirCmdClk, int rbtDirClk)
{
	int dirMotorCmd;

//	dirCmd=RateLimit(dirCmd*DEG2CLK,dir_rl,directionRl);
	dirMotorCmd = LimitSym((dirCmdClk-rbtDirClk)/DIR_KP, DIR_LIMIT);

	return(dirMotorCmd);
}
//*====================Add / for debug======================//
// Add this code to a while loop in main
// Unit Test
// [] drive forward to specific inch distance
// [] drive backward to a specific inch distance

long mrtLtClk, mrtLtClkOld=0, mtrRtClk, mtrRtClkOld=0, mtrLtSpdClk, mtrRtSpdClk, rbtDistClk;
int rbtDirClk;
		int mrtLtRlPct=0;
		int mtrRtRlPct=0;

#define FOREGROUND_MS 50
task Foreground(){
  int timeLeft;
//	int iFrameCnt=0;
//	int out,in=0;

	while(true){
		ClearTimer(T1);
		hogCPU();
		//--------------------UNIT TEST Code---------------------------//

		int rbtDirCmdDeg=90; // Degrees
		int spdCmdPct=40; // Percent of full motor speed command

		#define DEG2CLK 35
  	#define IN2CLK 300
//		#define DIR_KP 25 // Start tuning by setting this to around 25. Bigger numbers are a smaller gain
		#define STOPDIST_CLK 12*IN2CLK
		#define TURN90 90*DEG2CLK
		#define TURN_SPEED 15

		// Calculate robot and motor information (speed, distance, direction)
		mrtLtClk = nMotorEncoder[ltWheelMotor];
		mtrRtClk = nMotorEncoder[rtWheelMotor];

		mtrLtSpdClk = mrtLtClk - mrtLtClkOld;mrtLtClkOld = mrtLtClk;
		mtrRtSpdClk = mtrRtClk - mtrRtClkOld;mtrRtClkOld = mtrRtClk;

		rbtDistClk = mtrRtClk + mrtLtClk;
		rbtDirClk = mrtLtClk - mtrRtClk;

		// Calculate the direction command
		DebugInt(" rbtDirC",rbtDirClk);
		int dirCmdPct;
		//dirCmdPct = DirSmooth(rbtDirCmdDeg, rbtDirClk);//dirCmdDeg, rbtDirClk
		dirCmdPct = LimitSym((TURN90-rbtDirClk)/DIR_KP, TURN_SPEED);

		// Calculate the speed command
		if (abs(dirCmdPct)<5) {
			spdCmdPct=0;
			dirCmdPct=0;
		}
		//if (rbtDistClk>STOPDIST_CLK) spdCmdPct=0;


		// Calculate the motor commands
		int mtrCmdLtPct;
		int mtrCmdRtPct;
		mtrCmdLtPct=spdCmdPct+dirCmdPct;
		mtrCmdRtPct=spdCmdPct-dirCmdPct;

		// Limit the rate of change of the motor commands to prevent slipping.
  	DebugInt(" mlc1",mtrCmdLtPct);
  	DebugInt(" mrc1",mtrCmdRtPct);
		mtrCmdLtPct=RateLimit( mtrCmdLtPct, 4, mrtLtRlPct);
		mtrCmdRtPct=RateLimit( mtrCmdRtPct, 4, mtrRtRlPct );

		// Power the drive motors
		motor[ltWheelMotor]=mtrCmdLtPct;
		motor[rtWheelMotor]=mtrCmdRtPct;
  	DebugInt(" mlc2",mtrCmdLtPct);
  	DebugInt(" mrc2",mtrCmdRtPct);
  	DebugInt(" mslc", mtrLtSpdClk);
  	DebugInt(" msrc", mtrRtSpdClk);

		//--------------------------End UNIT TEST Code--------------------------//
		// Wait for next itteration
	  timeLeft=FOREGROUND_MS-time1[T1];
	  releaseCPU();
	  wait1Msec(timeLeft);
	}// While
}//Foreground
task main()
{
	//--------------------UNIT TEST INIT Code---------------------------//

		nMotorEncoder[ltWheelMotor]=0;
		nMotorEncoder[rtWheelMotor]=0;

	//--------------------------End UNIT TEST INIT Code--------------------------//

  StartTask(Foreground, 255);

  while(true){

  	//-----------------Print the debug statements out------------------//
		DebugPrint();

	}// While
}// Main
//*/
