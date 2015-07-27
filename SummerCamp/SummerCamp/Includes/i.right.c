void Right (int speed, int Degrees)
{
	int wait;

switch (speed)
{
case 100:
  wait=Degrees*4;
  break;

case 75:
  wait=Degrees*4;
  break;

case 50:
  wait=Degrees*5;
  break;

case 25:
  wait=Degrees*7;
  break;

default:
  break;
}

motor[rightmotor]=-speed;
motor[leftmotor]=speed;
wait1Msec(wait);
motor[rightmotor]=0;
motor[leftmotor]=0;
}
