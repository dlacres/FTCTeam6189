// As a ROLE I want to WHAT_I_WANT so that VALUE_I_GET
//
//======================================================//
int RaiseArm(int speed, int distance, short MotorName){


	return(myInput);
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
		// xxxxxxx [] Describe test 1 here. Put an X inside of [] when the test passes.
		// xxxxxxx [] Describe test 2 here. Put an X inside of [] when the test passes.

		// USAGE NOTES:
		//   The units for a are encoder clicks
		//   Set #define NO_UNIT_TEST
		if (i<5) in=0;
		if (i<10) in=1;

		out=MySoftwareModule(in);

		DebugInt("In",in);
		DebugInt("Out",out);

		i+=1; // Increment the frame counter for unit test
		// ------------- Unit code test is done here ---------------//
		DebugPrint();
		timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
		releaseCPU(); // Let other tasks run now.
		wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	}// While Loop
}// Main Task
#endif
