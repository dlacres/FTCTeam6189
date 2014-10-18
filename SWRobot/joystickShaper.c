// Change the shape of the joystick signal to give better control for small signals
// Between 0 and 80 the slope is 1/2.
// Between 80 and 115 the slope is 1.
// Between 115 and 128 the slope is 2.


int jsShape(int Jstick){
	int out = 0;
	int absoluteJstick = 0;

	absoluteJstick =abs(Jstick); //Work with positive numbers
	if (absoluteJstick < 2)
	{
		out=0;
	}

	else if (absoluteJstick <= 60)
		{
			out = absoluteJstick>>1 -3; //slope of 1/2
		}
	else if(absoluteJstick > 60 && absoluteJstick <= 123)
		{
			out = absoluteJstick - 33; // slope of 1
		}
	else out= ((absoluteJstick-6)<<1) - 144; // slope of 2

	if (Jstick < 0) out=-out; // Return to negative number if needed

	return(out);
}
//----------Test Code------------//
#pragma DebuggerWindows ("debugStream")// Bring up the debug stream window

int output;
task main(){
	for (int i=1;i<100;i++){
		output=jsShape(i);
		writeDebugStreamLine("%3i,%3i",i,output);
	}
}//*/
