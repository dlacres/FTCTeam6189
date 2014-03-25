const tMUXSensor HTCOLOR = msensor_S4_4;
bool block_there()
{
	int _color;
	 _color = HTCSreadColor(HTCOLOR);
	if (_color==7 || _color==5 || _color==6 )
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
