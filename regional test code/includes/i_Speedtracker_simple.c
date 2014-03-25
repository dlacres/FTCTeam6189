//As a driver I want the robot to stop if it something so the motors do not burn out.

// takes  speeed and actual encoder values from motors and if there is power to motors and motors are not moving it will output fales
// if motors stop it will start up again eventually

//******************************* code to add to autonomous main *******************************************
//name of include: #include "i_Speedtracker_simple.c"
/* 	add code below right before it sets motor speeds
bool speedVal = SpeedTracker;
if(speedVal)
{
	speedCmd = 0;
	dirCmd = 0;
}
*/

int lastLeftEncoder = 0, lastRightEncoder = 0;
int safetyCount = 0;
int resetCount = 0;
bool SpeedTracker(int Spdleftmotor, int SpdrightMotor, int leftencoder, int rightencoder) // add motors
{
	bool safetyBool = false;
	int tempint;
	tempint = abs(lastRightEncoder) - abs(rightencoder);
	lastRightEncoder = abs(tempint);
	tempint = abs(lastLeftEncoder) - abs(leftencoder);
	lastLeftEncoder = abs(tempint);

	if(abs(Spdleftmotor) > 1 && lastLeftEncoder > 5)
	{
		safetyCount++;
	}

	else if(abs(SpdrightMotor) > 1 && lastRightEncoder > 5)
	{
		safetyCount++;
	}
	else
	{
		safetyCount = 0;
	}
	if(safetyCount > 5)
	{
		safetyBool = true;
	}
	else
	{
		safetyBool = false;
	}
	lastLeftEncoder = leftencoder;
	lastRightEncoder = rightencoder;

	if(safetyBool == true)//
	{
		resetCount++;
		if(resetCount > 10)
		{
			resetCount = 0;
			safetyCount = 0;
		}
	}
	return safetyBool;
}


  task main()
{



}
