/*#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     endPgm,         sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rtMotor,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rtBack,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     ltMotor,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     ltBack,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

#include "i_lowpass.c"

#define Kp 0.25  // Kp
#define Ki 0.05 // Ki
#define Kd (-0)   //Kd

int error=0;
int integral=0;
int acceleration=0;
int distanceOld=0;
int speed,speedOld=0;
float output=0.0;
int integral2=0;
int distanceOld2=0;
int speed2,speedOld2=0;
#define MAX_INTEGRAL 30
void Pid_Init2(){
	distanceOld2=0;
	speedOld2=0;
	integral2=0;
  nMotorEncoder[ltMotor]=0;  // initialize encoder of motor B
  nMotorPIDSpeedCtrl[ltMotor] = mtrNoReg;//disable NXT inbuilt PID
	nSyncedMotors = synchNone;//disable NXT inbuilt PID
	return;
}
void Pid_Init(){
	distanceOld=0;
	speedOld=0;
	integral=0;
  nMotorEncoder[rtMotor]=0;  // initialize encoder of motor B
  nMotorPIDSpeedCtrl[rtMotor] = mtrNoReg;//disable NXT inbuilt PID
	nSyncedMotors = synchNone;//disable NXT inbuilt PID
	return;
}
bool failedPid=false;
int Pid2(int speedCmd, int distance){
	float integralKi,errorKp;

	//AddToDatalog(0,distance);
//	distance = nMotorEncoder[motorB];  // find actual degrees of motor B
	speed2 = distance - distanceOld2; distanceOld2=distance;
	acceleration = speed2 - speedOld2; speedOld2=speed2;
  error=speedCmd-speed2;  // Normilize speedCmd to the size of motor command 0->100.
  errorKp=error*Kp;
  integral2=integral2+error;  // find value of integral
  if (integral2>MAX_INTEGRAL) integral2=MAX_INTEGRAL; // Limit the value of the integral
  if (integral2<-MAX_INTEGRAL) integral2=-MAX_INTEGRAL;
  integralKi=integral2*Ki;   // Normilize to the size of motor command 0->100.


  output=errorKp+integralKi+Kd*acceleration;

 /* if (Lowpass(errorKp,0.2)>30 || failedPid){
  	failedPid=true;
  	output=0;
  }*/

  //AddToDatalog(1, actualDegreesC);

	return((int)output);
}
int Pid(int speedCmd, int distance){
	float integralKi,errorKp;

	//AddToDatalog(0,distance);
//	distance = nMotorEncoder[motorB];  // find actual degrees of motor B
	speed = distance - distanceOld; distanceOld=distance;
	acceleration = speed - speedOld; speedOld=speed;
  error=speedCmd-speed;  // Normilize speedCmd to the size of motor command 0->100.
  errorKp=error*Kp;
  integral=integral+error;// find value of integral
  if (integral>MAX_INTEGRAL) integral=MAX_INTEGRAL; // Limit the value of the integral
  if (integral<-MAX_INTEGRAL) integral=-MAX_INTEGRAL;
  integralKi=integral*Ki;   // Normilize to the size of motor command 0->100.


  output=errorKp+integralKi+Kd*acceleration;

 /* if (Lowpass(errorKp,0.2)>30 || failedPid){
  	failedPid=true;
  	output=0;
  }*/

  //AddToDatalog(1, actualDegreesC);

	return((int)output);
}

// Periodic Model used to read sensors and control the motors on a NXT brick
//
// As a software programmer, I want my tasks to run at a periodic rate. A periodic rate makes control, filtering,
//    and counting much easier.
//
#pragma DebuggerWindows ("debugStream")// Bring up the debug stream window
int spdCmd;
int count=0;
int timeLeft=0; // A global variable that sticks around each frame

// ------------------------Foreground Task -----------------------------//
// Run every second
//#define FOREGROUND_MS 50 //I change this to 50 when I control the robot. 1000 is good for testing.
/*task main(){
	int spdCmd;
  //---------------------------INIT-----------------------------------//
	Pid_Init();
	Pid_Init2();

  //---------------------------END INIT-------------------------------//
//	while(SensorValue(endPgm) == 0){
	while(true){
		ClearTimer(T1);
		hogCPU(); //Prevent other tasks from running when this one is.
		//writeDebugStreamLine("Foreground\n"); //Let me know when the foreground runs
	  count=count+1; // Count the number of times the foreground runs.

	  //--------------------------FOREGROUND------------------------------------//
	  spdCmd=100;
		motor[rtMotor]=Pid(spdCmd, nMotorEncoder[rtMotor]);
		motor[ltMotor]=Pid2(spdCmd, nMotorEncoder[ltMotor]);
motor[rtBack]=motor[rtMotor];
motor[ltBack]=motor[ltMotor];
	  //--------------------------END FOREGROUND--------------------------------//

	  timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
	  releaseCPU(); // Let other tasks run now.
	  wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	 	if (count==1){
	  	writeDebugStreamLine("SpdCmd[%f],Kp[%f],Ki[%f],Kd[%f]",spdCmd,Kp,Ki,Kd);
	  	writeDebugStreamLine("Count,Error,MtrCmd,Speed,Integral,Distance");
	  }
	 	writeDebugStreamLine("%2i,%3i,%3i,%3i,%3i,%5i",count,error,motor[rtMotor],speed,integral,nMotorEncoder[rtMotor]);

	}// While Loop
}// Foreground Main Task*/
