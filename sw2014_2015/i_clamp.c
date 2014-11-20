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

#include "JoystickDriver.c"

void Clampgoal(bool clampgoal) {
	if(clampgoal){
		servo[clamp]=255 ;
	}else{
		servo[clamp]=70 ;
	}
	return;
}


/*task main() {
	while(true){
		getJoystickSettings(joystick);
		Clampgoal(true);
	if(joy1Btn(3))
		{
			Clampgoal(true);
		}
		else
		{
			Clampgoal(false);
		}

		wait1Msec(50);
	}
}//*/
