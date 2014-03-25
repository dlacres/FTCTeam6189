#pragma DebuggerWindows("debugStream")
//
// David Lempia - 12/8/13 - Add a function DebugPrint to call from main (instead of pasting in multiple lines)
//
// Story - As a software debugger, I want to see a descriptive string and a variable so that I can understand
//    what my software is doing.
// Usage - To use this software,
//   1. Place the DebugPrint(); function in main within a while loop that runs 20 Hz or less.
//   2. Put the DebugInt function within the software to collect the debug information.
//
string debugStr[8];
int debugInt[8];
int debugI=0;
bool debugRun=false;
int debugSkip=0;
int debugSkipI=0;
int iFrameCnt=0;
// Debug(nameStr,valueInt);
void DebugInt(const string name, int value){
	if (debugI<8){
		strncpy(debugStr[debugI],name,6);
		debugInt[debugI++]=value;
	}
	debugRun=true;
	return;
}

// Use this to set the number of times the printout is skipped
void DebugSkip(int skip){
	debugSkip=skip;
}

// Place in the main loop. Do not call more than 20 times per second.
void DebugPrint(){
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
}
/* Add this code to a while loop in main
// Unit Test
// [x] Normal test
// [x] To many calls to debug
// [] Skip number is right
task main(){
	int tmp=0;
	int iFrameCnt=0;

  while(true){

  	DebugSkip(2);
  	DebugInt("r1",tmp++);
  	DebugInt("r2",tmp++);

		wait1Msec(100);

  	//-----------------Print the debug statements out------------------//
		DebugPrint();
	}
}
//*/
