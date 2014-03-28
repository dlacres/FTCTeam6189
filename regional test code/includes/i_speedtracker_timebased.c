/* add before while loop in foreground
  int previousTime = 0;
  int leftMotorSpd = 0;
	int rightMotorSpd = 0;
  ClearTimer(T2);
*/

int lastLeftEncoder = 0, lastRightEncoder = 0;
int safetyCount = 0;
int resetCount = 0;

bool safety(int currentTime, int previousTime, int setLeftSpd, int setRightSpd, long leftencoder, long rightencoder) // add motors
{
	bool safetyBool = false;
	int tempint;
	int timeDifference = currentTime-previousTime;
	int actualRightSpd = 0;
	int actualLeftSpd = 0;
	tempint = abs(lastRightEncoder) - abs(rightencoder);
	lastRightEncoder = abs(tempint);
	tempint = abs(lastLeftEncoder) - abs(leftencoder);
	lastLeftEncoder = abs(tempint);

	actualRightSpd = (lastRightEncoder/timeDifference)/10;// divide by ten because its the conversion from clicks per second to speed of 1 to 100
	actualLeftSpd = (lastLeftEncoder/timeDifference)/10; // divide by ten because its the conversion from clicks per second to speed of 1 to 100

	if((abs(actualRightSpd) - abs(setRightSpd)) > 10)
	{
		safetyCount++;
	}

	else if(true)
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


	if(safetyBool == true)
	{
		resetCount++;
		if(resetCount > 10)
		{
			resetCount = 0;
			safetyCount = 0;
		}
	}
	lastLeftEncoder = leftencoder;
	lastRightEncoder = rightencoder;

	return safetyBool;
}


  task main()
{



}
