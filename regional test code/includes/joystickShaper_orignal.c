// Change the shape of the joystick signal to give better control for small signals
// Between 0 and 80 the slope is 1/2.
// Between 80 and 115 the slope is 1.
// Between 115 and 128 the slope is 2.


int jsShape(int Jstick){
	int out = 0;
	int absoluteJstick = 0;

	absoluteJstick =abs(Jstick); //Work with positive numbers

	if (absoluteJstick <= 80)
		{
			out = absoluteJstick>>1; //slope of 1/2
		}
	else if(absoluteJstick > 80 && absoluteJstick <= 115)
		{
			out = absoluteJstick - 40; // slope of 1
		}
	else out= (absoluteJstick<<1) - 156; // slope of 2

	if (Jstick < 0) out=-out; // Return to negative number if needed

	return(out);
}
