
int delayatruecount=0;
bool Delayatrue (int delay,bool signal)
{

if(signal==true)
{
	delayatruecount++;
}
else
{
	delayatruecount=0;
}
if(delayatruecount>delay)
{
	delayatruecount=delay;
	return(true);
}

return(false);
}
int delayatruecount2=0;
bool Delayatrue2 (int delay,bool signal)
{

if(signal==true)
{
	delayatruecount2++;
}
else
{
	delayatruecount2=0;
}
if(delayatruecount2>delay)
{
	delayatruecount2=delay;
	return(true);
}

return(false);
}
