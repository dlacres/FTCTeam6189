
void IrReading(bool Infared,int ir_position)
	{
		while(true)
		{
			if(SensorValue[IR]==ir_position)
			{
			Infared=true;
			}

			else
			{
			Infared=false;
			}
		}

		return;
	}
