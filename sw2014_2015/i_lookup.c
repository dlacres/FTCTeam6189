// Change the shape of the joystick signal to give better control for small signals
// Between 0 and 80 the slope is 1/2.
// Between 80 and 115 the slope is 1.
// Between 115 and 128 the slope is 2.
int table_1[][]={
		{0, 0},
		{3, 0},
		{5, 3},
		{60, 40},
		{100, 80},
						};
#define x 0
#define y 1
int i,num,den;

int Lookup1(int in){
	int out = 0;
	int s=sizeof(table_1)/sizeof(table_1[0])-1;

	// Find the x region we are in
	for (i=0; i<s-1; ++i){
		if (table_1[i][x]<=in && table_1[i+1][x]>in)
			break;
	}
	num=table_1[i+1][y]-table_1[i][y];
	den=table_1[i+1][x]-table_1[i][x];
	out=(num*in)/den + table_1[i][y] - (num*table_1[i][x])/den;
	//out = (int)((float)(table_1[i+1][y]-table_1[i][y])/((float)(table_1[i+1][x]-table_1[i][x])))*(float)in;

	return(out);
}
//----------Test Code------------//
//#define TEST_DEBUG //-------------------------------------------------
#ifdef TEST_DEBUG

#pragma DebuggerWindows ("debugStream")// Bring up the debug stream window

int out;
task main(){
	writeDebugStreamLine("in,out,i,num,den");

	for (int in=1;in<100;in++){
		out=Lookup1(in);
		writeDebugStreamLine("%3i,%3i,%3i,%3i,%3i",in,out,i,num,den);
	}
}//*/
#endif
