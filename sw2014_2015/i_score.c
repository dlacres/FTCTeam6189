#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     rtWheelMotor,  tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     ltWheelMotor,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     sweeper,       tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    score,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool SCORE()
{
	servo[score]=240;
if (servo[score]=>240)
{
SCORE=true;
servo[score]=120;
}
return();
}
