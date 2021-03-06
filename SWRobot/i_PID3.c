/*#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     endPgm,         sensorI2CMuxController)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rtMotor,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     ltMotor,       tmotorTetrix, openLoop, encoder)*/
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define m1 ltMotor
#define m2 rtMotor
#define m3 rtMotor

#include "i_Lowpass.c"

#define Kp .3  // Kp
#define Ki 0.08 // Ki
#define Kd 0.1   //Kd
#define ERR_SIZE 30

float integral1=0.0,integral2=0.0,integral3=0.0;
int distanceOld1=0,distanceOld2=0,distanceOld3=0;
int speedOld1=0,speedOld2=0,speedOld3=0;
bool failedPid=false;
float lpZ11=0;
float lpZ21=0;
float lpZ31=0,lpZ32=0;
float accelerationKdOld1=0,accelerationKdOld2=0;


#define MAX_INTEGRAL 50/Ki

void Pid_Init1(){
	distanceOld1=0;
	speedOld1=0;
	integral1=0.0;
  nMotorEncoder[m1]=0;  // initialize encoder of motor B
  nMotorPIDSpeedCtrl[m1] = mtrNoReg;//disable NXT inbuilt PID
	nSyncedMotors = synchNone;//disable NXT inbuilt PID
	failedPid=false;
	lpZ11=0;
	return;
}
void Pid_Init2(){
	distanceOld2=0;
	speedOld2=0;
	integral2=0.0;
  nMotorEncoder[m2]=0;  // initialize encoder of motor B
  nMotorPIDSpeedCtrl[m2] = mtrNoReg;//disable NXT inbuilt PID
	nSyncedMotors = synchNone;//disable NXT inbuilt PID
	failedPid=false;
	lpZ21=0;
	return;
}
void Pid_Init3(){
	distanceOld3=0;
	speedOld3=0;
	integral3=0.0;
  nMotorEncoder[m3]=0;  // initialize encoder of motor B
  nMotorPIDSpeedCtrl[m3] = mtrNoReg;//disable NXT inbuilt PID
	nSyncedMotors = synchNone;//disable NXT inbuilt PID
	failedPid=false;
	lpZ31=0;

	return;
}


int min(int in1, int in2){
	if (in1>in2)
		return(in2);
	return(in1);
}

//---------------------------pid 1-------------------------------//

int Pid1(int speedCmd){
	int error,lpError;
	int speed,distance;
	float output,integralKi,errorKp;
	int lpSpdCmd=0;
	int speedB;
	float accelerationKdB,accelerationKd;

	lpSpdCmd=speedCmd;

	//AddToDatalog(0,distance);
	distance = nMotorEncoder[m1];  // find actual degrees of motor B
	speed = distance - distanceOld1; distanceOld1=distance;
	speedB=(speed+speedOld1)/2;
  accelerationKd = ((float)(speed - speedOld1))*Kd;speedOld1=speed;
  accelerationKdB=(accelerationKdOld1+accelerationKd)/2;accelerationKdOld1=accelerationKd;

	error=lpSpdCmd-speedB;
  errorKp=error*Kp;
  integral1=integral1+error;  // find value of integral

  if (integral1>MAX_INTEGRAL) integral1=MAX_INTEGRAL; // Limit the value of the integral
  if (integral1<-MAX_INTEGRAL) integral1=-MAX_INTEGRAL;

  integralKi=integral1*Ki;   // Normilize to the size of motor command 0->100.

  output=errorKp+integralKi-accelerationKdB;

	lpError=Lowpass(errorKp,0.4,lpZ11);
  if (lpError>ERR_SIZE || failedPid){
  	failedPid=true;
  	//output=0;
  }
	return((int)output);
}
//---------------------------pid 2-------------------------------//
int Pid2(int speedCmd){
	int error,lpError;
	int speed,distance;
	float output,integralKi,errorKp;
	int lpSpdCmd=0;
	int speedB;
	float accelerationKdB,accelerationKd;

	lpSpdCmd=speedCmd;

	//AddToDatalog(0,distance);
	distance = nMotorEncoder[m2];  // find actual degrees of motor B
	speed = distance - distanceOld2; distanceOld2=distance;
	speedB=(speed+speedOld2)/2;
  accelerationKd = ((float)(speed - speedOld2))*Kd;speedOld2=speed;
  accelerationKdB=(accelerationKdOld2+accelerationKd)/2;accelerationKdOld2=accelerationKd;

	error=lpSpdCmd-speedB;
  errorKp=error*Kp;
  integral2=integral2+error;  // find value of integral

  if (integral2>MAX_INTEGRAL) integral2=MAX_INTEGRAL; // Limit the value of the integral
  if (integral2<-MAX_INTEGRAL) integral2=-MAX_INTEGRAL;

  integralKi=integral2*Ki;   // Normilize to the size of motor command 0->100.

  output=errorKp+integralKi;

	lpError=Lowpass(errorKp,0.4,lpZ21);
  if (lpError>ERR_SIZE || failedPid){
  	failedPid=true;
  	//output=0;
  }

	return((int)output);
}
//---------------------------pid 3-------------------------------//
int Pid3(int speedCmd,int stopDistance){
	int error,lpError;
	int speed,distance;
	float output,integralKi,errorKp;
	int lpSpdCmd=0;

	lpSpdCmd=Lowpass(speedCmd,0.2,lpZ32);

	//AddToDatalog(0,distance);
	distance = nMotorEncoder[m1];  // find actual degrees of motor B
	if (stopDistance>0){
		if (lpSpdCmd>0)
			lpSpdCmd=min(lpSpdCmd,abs((stopDistance-distance)/10));
		else
			lpSpdCmd=-min(-lpSpdCmd,abs((stopDistance-distance)/10));
	}
	speed = distance - distanceOld3; distanceOld3=distance;

	error=lpSpdCmd-speed;
  errorKp=error*Kp;
  integral3=integral3+error;  // find value of integral

  if (integral3>MAX_INTEGRAL) integral3=MAX_INTEGRAL; // Limit the value of the integral
  if (integral3<-MAX_INTEGRAL) integral3=-MAX_INTEGRAL;

  integralKi=integral3*Ki;   // Normilize to the size of motor command 0->100.

  output=errorKp+integralKi;

	lpError=Lowpass(errorKp,0.4,lpZ31);
  if (lpError>ERR_SIZE || failedPid){
  	failedPid=true;
  	output=0;
  }

	return((int)output);
}

// Periodic Model used to read sensors and control the motors on a NXT brick
//
// As a software programmer, I want my tasks to run at a periodic rate. A periodic rate makes control, filtering,
//    and counting much easier.
//
/*#pragma DebuggerWindows ("debugStream")// Bring up the debug stream window
int count=0;
int timeLeft=0; // A global variable that sticks around each frame

// ------------------------Foreground Task -----------------------------//
// Run every second
int pltCnt=0;
#define FOREGROUND_MS 50
task main(){
	int spdCmd;
  //---------------------------INIT-----------------------------------//
	Pid_Init1();
//	Pid_Init2();

  //---------------------------END INIT-------------------------------//
//	while(SensorValue(endPgm) == 0){
	while(true){
		ClearTimer(T1);
		hogCPU(); //Prevent other tasks from running when this one is.
		//writeDebugStreamLine("Foreground\n"); //Let me know when the foreground runs
	  count=count+1; // Count the number of times the foreground runs.

	  //--------------------------FOREGROUND------------------------------------//
	  spdCmd=100;
		motor[m1]=Pid1(spdCmd);
//		motor[ltMotor]=Pid2(spdCmd, nMotorEncoder[ltMotor]);
	  //--------------------------END FOREGROUND--------------------------------//

	 	if (count==1){
	  	writeDebugStreamLine("SpdCmd[%f],Kp[%f],Ki[%f],Kd[%f]",spdCmd,Kp,Ki,Kd);
	  	writeDebugStreamLine("Count,timeLeft,ErrorKp,lpError,distance,Speed,IntegralKi,output,failed");
	  }
//	  if (pltCnt++>1){
//	 		writeDebugStreamLine("%2i,%2i,%f,%3i,%3i,%3i,%f,%f,%1i",count,timeLeft,failedPid);
			pltCnt=0;
//		}

		timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
	  releaseCPU(); // Let other tasks run now.
	  wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	}// While Loop
}// Foreground Main Task*/
