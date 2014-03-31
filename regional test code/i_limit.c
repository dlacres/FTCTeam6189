// Story: As a software designer, I want to limit the size a signal can be.
//
int LimitSym(int in, int max){

	if (in>max) return(max);
	if (in<-max) return(-max);
	return(in);
}
int Limit(int in, int max, int min){

	if (in>max) return(max);
	if (in<min) return(min);
	return(in);
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

  	if (iFrameCnt<2) in=7;
  	else if (iFrameCnt<4) in=5;
  	else if (iFrameCnt<6) in=1;
  	else if (iFrameCnt<8) in=-1;
   	else if (iFrameCnt<10) in=-4;
  	else if (iFrameCnt<12) in=-5;
  	else if (iFrameCnt<14) in=-7;

  	DebugInt("In",in);
  	out=LimitSym(in, 5);
  	DebugInt("OutS5",out);
  	out=Limit(in, 5, -4);
  	DebugInt("Out5-4",out);

		wait1Msec(100);

  	//-----------------Start i_debug.c output------------------//
  	if (debugRun==true){// Do not send out a stream if Debug is not called
			if (debugSkip<debugSkipI++){
	  		writeDebugStream("[%d] ",iFrameCnt);
	  		for (int i=0; i<debugI; ++i)
	  			writeDebugStream(" %5s=%6d",debugStr[i],debugInt[i]);

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
