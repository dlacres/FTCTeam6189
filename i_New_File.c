#ifndef NO_UNIT_TEST
// #PRAGMAs go here
#endif
// As a ROLE I want to WHAT_I_WANT so that VALUE_I_GET
//
//======================================================//
void MySoftwareModule(int a){
}
// ==================UNIT TEST==========================//
#ifndef NO_UNIT_TEST
int timeLeft=0; // A global variable used to adjust the time it takes to complet the while loop
#define FOREGROUND_MS 50 //The while loop takes 50 MS to run. This means the software runs 20 times per second
task main(){
	// Initialize variables here //
	
	// End of initialize //
	while(true){
		ClearTimer(T1);
		hogCPU(); //Prevent other tasks from running when this one is.
		// ------------- Put Unit Test code here -------------------//
		// xxxxxxx [] Describe test 1 here. Put an X inside of [] when the test passes.
		// xxxxxxx [] Describe test 2 here. Put an X inside of [] when the test passes.
		
		// USAGE NOTES:
		//   The units for a are encoder clicks
		//   Set #define NO_UNIT_TEST
		MySoftwareModule(a);
		
		// ------------- Unit code test is done here ---------------//
		timeLeft=FOREGROUND_MS-time1[T1]; // Calculate the time used in the foreground
		releaseCPU(); // Let other tasks run now.
		wait1Msec(timeLeft);// The time other tasks have to run before foreground takes control.
	}// While Loop
}// Main Task
#endif
