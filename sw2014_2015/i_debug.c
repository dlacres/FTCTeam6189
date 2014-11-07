#pragma DebuggerWindows("debugstream")
// Story - As a software debugger, I want to see a descriptive string and a variable so that I can understand
//    what my software is doing.
// Usage - To use this software,
//   1. DebugSkip(4); Print out every 5th value. Use any number you want. The default is 0 (no skips).
//   2. Use DebugInt, DebugFloat, or DebugBool to collect the debug information.
//   3. Select the output method (1 or more) by calling one time: Debug2File(), Debug2NXT() or Debug2Stream();
//   4. Place the DebugPrint(); after all the debugInt calls. (Takes 10ms or less to run).
//
//   The data is output to the debug stream and to a file called "debug.txt"
//   The data going to the file is limited to 10000 characters. This is about 151 rows with 10 columns.
//
//  Written by David Lempia
//
#define DBG_MAX_COL 10
string debugColName[10];
string debugValue[10];
int debugI=0;
int debugSkip=0;
int debugSkipI=0;
int iFrameCntDebug=0;

TFileHandle DebugFile;
TFileIOResult isOk;
short nFileSize=10000;
string debugFileName="debug.txt";

// ---------------- Capture integer debug information ---------------------//
void DebugInt(const string name, int value){
  string tmp;
  if (debugI < DBG_MAX_COL){
    if (iFrameCntDebug==0){
      strncat(tmp,name,5);
      sprintf(debugColName[debugI],"%5s",tmp);
    }
    sprintf(debugValue[debugI++],"%5d",value);
  }
  return;
}
// ---------------- Capture float debug information ---------------------//
void DebugFloat(const string name, float value){
  string tmp;
  if (debugI < DBG_MAX_COL){
    if (iFrameCntDebug==0){
      strncat(tmp,name,5);
      sprintf(debugColName[debugI],"%5s",tmp);
    }
    sprintf(debugValue[debugI++],"% 2.2f",value);
  }
  return;
}
// ---------------- Capture boolean debug information ---------------------//
void DebugBool(const string name, bool value){
  string tmp;
  if (debugI < DBG_MAX_COL){
    if (iFrameCntDebug==0){
      strncat(tmp,name,5);
      sprintf(debugColName[debugI],"%5s",tmp);
    }
    if (value==true)
      debugValue[debugI++]="    T";
    else
      debugValue[debugI++]="    F";
  }
  return;
}

// Set the number of times the printout is skipped (Default is to print every time)
void DebugSkip(int skip){
  debugSkip=skip;
}

// Use this to pick the form of output
bool Debug2FileBool   =false;
bool Debug2NXTBool    =false;
bool Debug2StreamBool =false;
void Debug2File(){    Debug2FileBool  =true; }
void Debug2NXT(){     Debug2NXTBool   =true; }
void Debug2Stream(){  Debug2StreamBool=true; }

// Send the print data to the debug window and the debug file "debug.txt"
void DebugPrint(){
  char str[70];
  int i;

  if (debugI>0){// Do not send out Debug info if not needed
    if (iFrameCntDebug==0){
      if (Debug2FileBool){
	      //writeDebugStream("col size %d", debugI);
	      Delete(debugFileName, isOk);
	      OpenWrite(DebugFile, isOk, debugFileName, nFileSize);
      }
      strcpy(str,"Frame,");
      for (i=0; i < (debugI-1); ++i){
        strcat(str,debugColName[i]);
        strcat(str,",");
      }
      strcat(str,debugColName[i]);
      strcat(str, "\n");

      if (Debug2StreamBool)
        writeDebugStream(str);
      if (Debug2FileBool)
        WriteString(DebugFile, isOk, str);
      if (Debug2NXTBool){
        eraseDisplay();
      	wait1Msec(10);
      }
    }

    if (debugSkip < debugSkipI++){
      if (Debug2NXTBool){
	      for (i=0; i < debugI; ++i){
  	      strcpy(str,"");
          strcat(str,debugColName[i]);
          strcat(str,"=");
	        strcat(str,debugValue[i]);
	        displayTextLine(i+2,str);
	      }
      }
      if (Debug2FileBool){
	      strcpy(str,"");
	      sprintf(str,"%5d,",iFrameCntDebug);
	      for (i=0; i < (debugI-1); ++i){
	        strcat(str,debugValue[i]);
	        strcat(str,",");
	      }
	      strcat(str,debugValue[i]);
	      strcat(str,"\n");

	      WriteString(DebugFile, isOk, str);
      }
      if (Debug2StreamBool){
	      strcpy(str,"");
	      sprintf(str,"%5d,",iFrameCntDebug);
	      for (i=0; i < (debugI-1); ++i){
	        strcat(str,debugValue[i]);
	        strcat(str,",");
	      }
	      strcat(str,debugValue[i]);
	      strcat(str,"\n");

        writeDebugStream(str);
      }
      debugSkipI=0;
    }
    iFrameCntDebug++;
    debugI=0; //Clear the debug buffer
  }
}
//#define TEST_DEBUG //-------------------------------------------------
#ifdef TEST_DEBUG
// Unit Test
// [x] Normal test
// [x] To many debugInt(3) calls
// [x] No calls to debugInt() - No output should happen.
// [x] Skip number is right
// [x] The name is longer than 5 characters. Should be limited to 5.
// [x] Output to file and debug stream match
// [x] Test max file size (File output ends without issue when the max file is hit)
// [x] Test worst case time. It takes between 3 and 10 ms to output all 10 columns of data.
task main(){
  int tmp=0;
  //DebugSkip(2); //

  ClearTimer(T2);

  for (int i=0; i < 10; i++){
    DebugInt("r1",time1[T2]);
    DebugInt("r2",time1[T2]);
    DebugInt("r3",time1[T2]);
    DebugInt("r4",time1[T2]);
    DebugInt("r5",time1[T2]);
    DebugInt("r6",time1[T2]);
    DebugInt("r7",time1[T2]);
    DebugInt("r8",time1[T2]);
    DebugInt("r9",time1[T2]);
    DebugInt("r10",time1[T2]);
    DebugInt("r11",time1[T2]);

    /*DebugInt("1234567",tmp++);
    DebugFloat("r2",2.5);
    DebugBool("r3",false);*/

    //-----------------Print the debug statements out------------------//
    DebugPrint();
  }
}
#endif
