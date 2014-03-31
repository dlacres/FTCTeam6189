// Story: As a software designer I want to find the rising edge of a signal so that I can trigger an event
// Usage: Make sure globalBoolEq0 is initialized equal to false
// outBool = RiseEdge( inBool, globalBoolEqF );
bool RiseEdge(bool in, bool &z1)
{
	bool out=false;

  if ((in==true) && (z1==false)) out=true;
  z1=in;

	return(out);
}
/* Add this code to a while loop in main
// Unit Test
// [] Rise Edge
// [] Fall Edge
// [] High
// [] Low
#include "i_debug.c"

task main(){
	int iFrameCnt=0;
	bool z=false;
	bool out,in=false;

  while(true){

  	if (iFrameCnt<2) in=false;
  	else if (iFrameCnt<4) in=true;
  	else if (iFrameCnt<6) in=false;
  	else if (iFrameCnt<8) in=true;

  	out=RiseEdge(in, z);
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
