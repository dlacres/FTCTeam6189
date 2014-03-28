// As a developer I want to filter a sensor to remove noise or to delay a response.
float lpOld=0;
float out;
int Lowpass(int in,float tau){
	out = lpOld + tau * ((float)in - lpOld);
	lpOld=out;
	return((int)lpOld);
}

/*#pragma DebuggerWindows ("debugStream")// Bring up the debug stream window

// Periodic Model used to read sensors and control the motors on a NXT brick
//
// As a software programmer, I want my tasks to run at a periodic rate. A periodic rate makes control, filtering,
//    and counting much easier.
//

int count=0;
int timeLeft=0; // A global variable that sticks around each frame

// ------------------------Foreground Task -----------------------------//
// Run every second
#define FOREGROUND_MS 50 //I change this to 50 when I control the robot. 1000 is good for testing.
task main(){
	int cmd=20;
  //---------------------------INIT-----------------------------------//

  //---------------------------END INIT-------------------------------//
//	while(SensorValue(endPgm) == 0){
//	while(true){
		while(count<20){
		ClearTimer(T1);
		hogCPU(); //Prevent other tasks from running when this one is.
		//writeDebugStreamLine("Foreground\n"); //Let me know when the foreground runs
	  count=count+1; // Count the number of times the foreground runs.

	  //--------------------------FOREGROUND------------------------------------//
		out=Lowpass(cmd,0.5);
	  //--------------------------END FOREGROUND--------------------------------//

	  timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
	  releaseCPU(); // Let other tasks run now.
	  wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	 	if (count==1){
	  	writeDebugStreamLine("Cnt,Cmd[%i],Out",cmd);
	  	writeDebugStreamLine("Cnt,Cmd,Out");
	  }
	 	writeDebugStreamLine("%3i,%3i,%3i",count,cmd,out);

	}// While Loop
}// Foreground Main Task*/
