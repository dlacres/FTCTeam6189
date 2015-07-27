void Backward(int speed, int distance)
{
	int wait;

switch (speed)
{
case 100:
  wait=distance*66;
  break;

case 75:
  wait=distance*71;
  break;

case 50:
  wait=distance*104;
  break;

case 25:
  wait=distance*208;
  break;

default:
  break;
}

motor[rightmotor]=-speed;
motor[leftmotor]=-speed;
wait1Msec(wait);
motor[rightmotor]=0;
motor[leftmotor]=0;
}
