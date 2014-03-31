// Return a value of 0 if the signal is inside the deadZone
// tested on
int deadZone(int Jstick, int size){
	int out;

	out=Jstick;
	if (abs(Jstick)< size) out=0; // sets joystick equal to zero if absolute of joystick is less than size.

	return(out);
}
