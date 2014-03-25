#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Sonar,          sensorSONAR)
#pragma config(Sensor, S4,     ABC,            sensorI2CHiTechnicColor)
#pragma config(Motor,  mtr_S1_C1_1,     ltWheelMotor,  tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rtWheelMotor,  tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     blockthrower,  tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "i_debug.c"
#include "i_rateLimit.c"
#include "i_limit.c"
#include "i_fallEdge.c"
//*/
// Story: As a software designer I want to smoothly change the direction the robot goes as it follows a path.
// Story: As a reliability engineer, I want the software to turn off the motor command when the motor stalls because
//     We are burning up motors.
// Dependency: i_rateLimit.c, i_limit.c
// Usage: A positive dirCmd is turn right. Returns the direction command.
// Tuning:

long mrtLtClk, mrtLtClkOld=0, mtrRtClk, mtrRtClkOld=0, mtrLtSpdClk, mtrRtSpdClk, rbtDistClk, dirCmdClk;
int rbtDirClk;
int mrtLtRlPct=0;
int mtrRtRlPct=0;
int dirCmdPct;
long tmpDist;
bool fallOld=false;

#define FWDa 0
#define FWDb 2
#define FWDc 3
#define TURNa 4
#define TURNb 5
#define TURNc 6
#define STOP 7
short sm=TURNa;

#define MTR_OK 0
#define MTR_BAD 1
short sm2=MTR_OK;
short mtrBadTmr=0;

#define DEG2CLK 35
#define IN2CLK 300
#define DIR_KP 25 // Start tuning by setting this to around 25. Bigger numbers are a smaller gain
#define STOPDIST_CLK 12*IN2CLK
#define DST12 12*IN2CLK
#define DIR90 90*DEG2CLK
#define DIRm90 -90*DEG2CLK
#define DIR180 180*DEG2CLK
#define DIR45 45*DEG2CLK
#define DIR0 0
#define TURN_SPEED 30

#define FOREGROUND_MS 50
task Foreground(){
  int timeLeft;
//	int iFrameCnt=0;
//	int out,in=0;

	while(true){
		ClearTimer(T1);
		hogCPU();
		//--------------------UNIT TEST Code---------------------------//

		int spdCmdPct=40; // Percent of full motor speed command


		// Calculate robot and motor information (speed, distance, direction)
		mrtLtClk = nMotorEncoder[ltWheelMotor];
		mtrRtClk = nMotorEncoder[rtWheelMotor];

		mtrLtSpdClk = mrtLtClk - mrtLtClkOld;
		mrtLtClkOld = mrtLtClk;
		mtrRtSpdClk = mtrRtClk - mtrRtClkOld;
		mtrRtClkOld = mtrRtClk;

		DebugInt(" sLt",mtrLtSpdClk);
		DebugInt(" sRt",mtrRtSpdClk);

		rbtDistClk = mtrRtClk + mrtLtClk;
		rbtDirClk = mrtLtClk - mtrRtClk;

		// ------------- The path state machine --------------------//
		switch (sm) {

		case TURNa: //Drive Forward
    		dirCmdClk=DIR45;
    		spdCmdPct=20;
    		bool fall;
    		fall=FallEdge(abs(dirCmdPct)>5,fallOld);
    		if (fall) {
    			sm=STOP;
    			tmpDist=rbtDistClk;
    		}
			break;
		case STOP:
			spdCmdPct=0;
			break;
		default:
				spdCmdPct=40;
		}

		// Calculate the direction command
		DebugInt(" rbtDirC",rbtDirClk);
		dirCmdPct = LimitSym((dirCmdClk-rbtDirClk)/DIR_KP, TURN_SPEED);

		// Calculate the motor commands
		int mtrCmdLtPct;
		int mtrCmdRtPct;
		mtrCmdLtPct=spdCmdPct+dirCmdPct;
		mtrCmdRtPct=spdCmdPct-dirCmdPct;

		// Limit the rate of change of the motor commands to prevent slipping.
//  	DebugInt(" mlc1",mtrCmdLtPct);
//  	DebugInt(" mrc1",mtrCmdRtPct);
		mtrCmdLtPct=RateLimit( mtrCmdLtPct, 4, mrtLtRlPct);
		mtrCmdRtPct=RateLimit( mtrCmdRtPct, 4, mtrRtRlPct );

		// Protect against stalled motors
		switch (sm2) {
		case MTR_OK: //Drive Forward
#define MTR_TRP 45
/*    		if ((abs(mtrLtSpdClk)<MTR_TRP && abs(mtrCmdLtPct)>30)||(abs(mtrRtSpdClk)<MTR_TRP && abs(mtrCmdRtPct)>30)){
    			mtrBadTmr+=1;
    			if (mtrBadTmr>7) sm2=MTR_BAD;
    		} else {
    			mtrBadTmr=0;
    		}
*/			break;
		case MTR_BAD: //Drive Forward
			mtrCmdLtPct=0;
			mtrCmdRtPct=0;
			break;
		default:
		}

  	DebugInt(" mlc2",mtrCmdLtPct);
  	DebugInt(" mrc2",mtrCmdRtPct);
		// Power the drive motors
		motor[ltWheelMotor]=mtrCmdLtPct;
		motor[rtWheelMotor]=mtrCmdRtPct;
//  	DebugInt(" mlc2",mtrCmdLtPct);
//  	DebugInt(" mrc2",mtrCmdRtPct);
//  	DebugInt(" SM", sm);
  	DebugInt(" tmr", mtrBadTmr);
  	DebugInt(" SM2", sm2);

		//--------------------------End UNIT TEST Code--------------------------//
		// Wait for next itteration
	  timeLeft=FOREGROUND_MS-time1[T1];
	  if (timeLeft<0) timeLeft=0;
	  DebugInt(" time", timeLeft);

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
