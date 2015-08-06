void Left (int speed, int Degrees)
{
	nMotorEncoder[rightmotor] = 0;
	nMotorEncoder[leftmotor] = 0;

	//250 counts per motor revolution = 6.9 inches (Wheel diameter is 2.2 inches)
	while ((abs(nMotorEncoder[rightmotor])+abs(nMotorEncoder[leftmotor])) < (distance*72))  // wait for motor to reach a specific location
	{
  	motor[rightmotor] = speed;
  	motor[leftmotor] = -speed;
	}

	motor[rightmotor]=0;
	motor[leftmotor]=0;

}
