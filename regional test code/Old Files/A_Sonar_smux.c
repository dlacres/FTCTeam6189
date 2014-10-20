#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorA,          leftsweeper,   tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          light,         tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     ltMotor,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rtMotor,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     ltBack,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     rtBack,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     flagraiser,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     blockthrower,  tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     robotlifter,   tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     blockgrabber,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C1_1,    irArm,                tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-ultrasound.h"

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

#include "i_PID2.c"
#include "i_delayatrue.c"
#include "i_debug.c"
#include "i_limit.c"
#include "i_rateLimit.c"
#include "i_direction.c"-------------------------------------------------------------------------------------------------------------------------------
#include "i_forwardDist.c"
#include "i_flipperArm_auto.c"
int rightmotors;
int leftmotors;

//--------------------Path definition----------------------//
// dist, dir, spd

int path[][]={
		{63, 0, 40},
  	{64, 0, 50},
  	{64, -90, 50},
  	{122, -90, 50},
  	{122, -190, 50},
  	{165, -190, 50},
		};

int shortPath[][]={
		{63, 0, 40},
  	{64, 0, 40},
  	{64, -90, 50},
  	{102, -90, 50},
  	{102, -190, 50},
  	{141, -190, 50},
		};
bool shortPathTrue = false;
int armSetPos = 0;
#define SPD 40;
#define DIST_IDX 0
#define DIR_IDX 1
#define SPD_IDX 2
int pathIdx=0;
int speedCmdZ1=0;



//*--------------------Foreground---------------------------//
// Story: As a player, I want the robot to follow a path so i can score autonomous points in a game
// [x] Follow path stored in an array
// [x] Stop at the end of the path
void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}

#define FOREGROUND_MS 50

task Foreground(){
	//servoChangeRate[servo2] = 2;
	Pid_Init();
	Pid_Init2();
  int timeLeft;
	int state=0;
	int speedCmd = 0;
	int dirCmd = 0;
	const tMUXSensor LEGOUS = msensor_S4_3;
	while(true){
		ClearTimer(T1);
		hogCPU();
		//--------------------Robot Code---------------------------//
	long armEncoder = nMotorEncoder[blockthrower];
	long  robotDist = nMotorEncoder[rtMotor] + nMotorEncoder[ltMotor];
	long  robotDir  = nMotorEncoder[ltMotor] - nMotorEncoder[rtMotor];
	long  distInches = robotDist/IN2CLK;
		// Calculate the speed and direction commands
  if(shortPathTrue == false)
  {
	   speedCmd = ForwardDist(path[pathIdx][DIST_IDX], robotDist, path[pathIdx][SPD_IDX]);
		 dirCmd=Direction(path[pathIdx][DIR_IDX], robotDir);
	}
	else
  {
     speedCmd = ForwardDist(shortPath[pathIdx][DIST_IDX], robotDist, shortPath[pathIdx][SPD_IDX]);
		 dirCmd=Direction(shortPath[pathIdx][DIR_IDX], robotDir);
	}

		int armSpd = FlipperArm(armEncoder, armSetPos);
	bool IRval;
	bool SonarVal;
	//calculate when to increment path
if (abs(speedCmd)<3 && abs(dirCmd)<3) pathIdx++;
// State O Follow Path
if (state==0)
{
	if (distInches>21)
	{
		state=1;
	}
}
IRval = Delayatrue(1, SensorValue[IR] == 1 || SensorValue[IR] == 2);
// State 1 Look for IR Beacon
 if (state==1)
 {
   speedCmd=10;
  if ( IRval)
  {
  	state=7;
  }
  else
  {
  	state=2;
  }
}
// State 2 Follow Path
if (state==2)
{

	if (distInches>28)
	{
		state=3;
	}

}
// State 3 Look for IR Beacon
 if (state==3)
 {
   speedCmd=10;
  if ( IRval==true)
  {
  	state=7;
  }
  else
  {
  	state=4;
  }
}
// State 4 Follow Path
if (state==4)
{
	if (distInches>50)//36
	{
		state=5;
	}

}

// State 5 Look for IR Beacon
 if (state==5)
 {
   speedCmd=10;
  if ( IRval==true)
  {
  	state=7;
  }
  else
  {
  	state=6;
  }
}
// State 6 Follow Path
if (state==6)
{
	if (pathIdx == 1)//45
	{
		state=7;
	}
}

if (state==7)// flip arm
{
	speedCmd=0;
	dirCmd = 0;
	armSetPos = 1900;
		if (abs(armSetPos - armEncoder) <20)
		{

			state=8;
		}

}
if (state==8)
{
	speedCmd = 0;
	dirCmd = 0;
	armSetPos = 0;
		if (abs(armSetPos) - abs(armEncoder) < 200)
		{
			state=9;
		}
}

SonarVal = Delayatrue2(1, USreadDist(LEGOUS) > 40);

if (state==9)
{
  if ((distInches>90) && (distInches<115))
  {

		if(SonarVal)
		{
		state=10;
		}
		else
		{
			state=11;
	  }
  }
}
if(state==10)
{
	shortPathTrue=true;
}
if(state==11)
{

}

DebugInt("spd",speedCmd);
DebugInt("dir",robotDir/DEG2CLK);
DebugInt("sonarval",SonarVal);
DebugInt("path",pathIdx);
DebugInt("state",state);
DebugInt("dist",distInches);


		// Calculate when to move to the next path index

		int s=sizeof(path)/sizeof(path[0])-1;
		DebugInt("siz",s);
		if (pathIdx>s) pathIdx=s;
	speedCmd = RateLimit(speedCmd, START_RATE,speedCmdZ1 );
		rightmotors=Pid(speedCmd-dirCmd, nMotorEncoder[rtMotor]);
		leftmotors=Pid2(speedCmd+dirCmd, nMotorEncoder[ltMotor]);
		motor[rtBack]=rightmotors;
		motor[rtMotor]=rightmotors;
		motor[ltMotor]=leftmotors;
		motor[ltBack]=leftmotors;
		motor[blockthrower]=armSpd;
		DebugInt("rightmotors",rightmotors);
		DebugInt("leftmotors",leftmotors);
		//--------------------------Robot Code--------------------------//
		// Wait for next itteration
	  timeLeft=FOREGROUND_MS-time1[T1];
	  releaseCPU();
	  wait1Msec(timeLeft);
	}// While
}//Foreground
task main()
{

  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.

	int iFrameCnt=0;

	//--------------------INIT Code---------------------------//
  ForwardDistReset((tMotor)rtMotor, (tMotor)ltMotor);
	DirectionReset();
	nMotorEncoder[blockthrower] = 0;
	speedCmdZ1=0;
	pathIdx=0;
	delayatruecount=0;


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