// Story: As a software designer, I want to ignore small noisy signals so that outputs (like motors) don't buzz or move.
// Usage:
// Return a value of 0 if the signal is inside the deadZone
// outInt = DeadZone(inInt, sizeInt);
int DeadZone(int in, int size){
	int out;

	out=in;
	if ((in<size && in>-size)) out=0;

	return(out);
}
/* Add this code to a while loop in main
// Unit Test
// [x] input < -size
// [x] input > size
// [x] input in between
#include "i_debug.c"

task main(){
	int iFrameCnt=0;
	int out,in=0;

  while(true){

  	if (iFrameCnt<2) in=5;
  	else if (iFrameCnt<4) in=3;
  	else if (iFrameCnt<6) in=1;
  	else if (iFrameCnt<8) in=-1;
   	else if (iFrameCnt<10) in=-3;
  	else if (iFrameCnt<12) in=-5;
  	else if (iFrameCnt<14) in=-7;

  	out=DeadZone(in, 3);
  	DebugInt("In",in);
  	DebugInt("Out",out);

		wait1Msec(100);

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
	}
}
//*/
