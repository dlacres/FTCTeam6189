/*#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

//#include "JoystickDriver.c"

void DumpBucket(bool dumpbucket) {
	if(dumpbucket){
		servo[dump]=255 ;
	}else{
		servo[dump]=125;
	}
	return;
}


/*task main() {
	while(true){
		getJoystickSettings(joystick);
	if(joy1Btn(0))
				{
					DumpBucket(true);
				}
					else
					{
						DumpBucket(false);
					}
			displayCenteredBigTextLine(5, "%d",servo[servo2]);
	//servo[dump]=25;
	//servo[clamp]=25;
		wait1Msec(50);
	}
}//*/
