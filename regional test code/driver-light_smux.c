#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorA,          leftsweeper,   tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          light,         tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     ltMotor,       tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rtMotor,       tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     ltBack,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     rtBack,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     flagraiser,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     blockthrower,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     robotlifter,   tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     blockgrabber,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C1_1,    irArm,                tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S3_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-colour-v1.h"
#include "drivers/lego-ultrasound.h"
#include "drivers/hitechnic-gyro.h"

#include "JoystickDriver.c"
#include "joystickDeadzone.c"
#include "i_PID2.c"
#include "joystickShaper.c"

#include "i_block_there.c"
#include "i_limit.c"
#include "i_flipperArm_driver.c"
#define LIGHT_OFF 0
#define LIGHT_ON_1 1
#define LIGHT_ON_2 2
#define FLASH 3
void initializeRobot()
{

}

#define FOREGROUND_MS 50
const tMUXSensor HTGYRO = msensor_S4_1;
task main()
{
	initializeRobot();

  waitForStart();
  ClearTimer(T2);
	nMotorEncoder[robotlifter] = 0;
	nMotorEncoder[blockthrower] = 0;
	bool lifterTrigger = false;
	int rightmotors;
	int leftmotors;
	int lifterEncoder = 0;
	int lifterSpd = 0;
	int block_count = 0;
	int throwerEncoder = 0;
	int throwerSpd = 0;
	int throwerSet = 0;
	int jstick2Y2 = 0;
	int jstick2Y1 = 0;
	int prev_time=time10[T2];
	int sm_light=LIGHT_OFF;
	int	bias=HTGYROreadRot(HTGYRO);
	wait10Msec(20);
	bias=(HTGYROreadRot(HTGYRO)+bias);
	wait10Msec(20);
	bias=(HTGYROreadRot(HTGYRO)+bias)/3;
	servo[irArm]=243;
	bool lightflash=true;

		Pid_Init();
	Pid_Init2();

	while(true)
	{
				ClearTimer(T1);
		hogCPU();

		int jstickX = 0;
		int jstickY = 0;
		getJoystickSettings(joystick);
		jstick2Y1 = jsShape(joystick.joy2_y1);
		jstick2Y2 = -jsShape(joystick.joy2_y2);
		jstickX = jsShape(joystick.joy1_x2);// makes driving less touchy... hopefully
		jstickY = jsShape(joystick.joy1_y2);// same here
		jstickX = joystick.joy1_x2;// makes driving less touchy... hopefully
		jstickY = joystick.joy1_y2;// same here
	  jstickX = jstickX-(deadZone((HTGYROreadRot(HTGYRO)-bias)/2, 7));
//	  writeDebugStreamLine("sensor=%d",HTGYROreadRot(HTGYRO));
//	writeDebugStreamLine("joyX=%d,bias=%d",jstickX,bias);
//		writeDebugStreamLine("motorspeed %d", rightmotors);
    rightmotors = (-jstickY + jstickX)/2; // uses revised values to make driving on one joystick
   	leftmotors = (-jstickY + -jstickX)/2;// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    motor[blockgrabber] = jstick2Y2;
		motor[leftsweeper] = -jstick2Y2;
	motor[rtBack]=rightmotors;
	motor[rtMotor]=rightmotors;
	motor[ltMotor]=leftmotors;
	motor[ltBack]=leftmotors;
	rightmotors=Pid(spdCmd, nMotorEncoder[rtMotor]);
	leftmotors=Pid2(spdCmd, nMotorEncoder[ltMotor]);
//	writeDebugStreamLine("motorspeed %d", rightmotors);



switch (sm_light)
{

case LIGHT_OFF:

motor[light]=0;	//set light off


if(block_count==4)
{
sm_light=LIGHT_ON_2;
}

if(nMotorEncoder[blockthrower]>1700)
{
	block_count=0;
	sm_light=LIGHT_OFF;
}
	if (joystick.joy2_y2<0&&block_there()==true) // Block in and light sees yellow
	{
		++block_count;
		sm_light=LIGHT_ON_1;
	}
		if (joystick.joy2_y2>0&&block_there()==true) // Block out and light sees yellow
	{
		--block_count;
		sm_light=LIGHT_ON_1;
	}

break;

case LIGHT_ON_1:

motor[light]=100;
if(nMotorEncoder[blockthrower]>1700)
{
	block_count=0;
	sm_light=LIGHT_OFF;
}
if (block_there()==false)
{
sm_light=LIGHT_OFF;
}
if(joystick.joy2_y2>0&&block_there()==false)
{
	--block_count;
	sm_light=LIGHT_OFF;
}
break;

case LIGHT_ON_2:

motor[light]=100;

	if (block_there()==true ) // Block in and light sees yellow
	{
		++block_count;
	}

if(block_count>4)
{
sm_light=FLASH;
}
if(nMotorEncoder[blockthrower]>1700)
{
	block_count=0;
	sm_light=LIGHT_OFF;
}
break;

case FLASH:

	if(lightflash==true)
	{
	motor[light]=100;
	if(time10[T2]-prev_time>10)
	{
	lightflash=false;
	prev_time=time10[T2];
	}
	}
if(lightflash==false)
{
	motor[light]=0;
	if(time10[T2]-prev_time>10)
	{
		lightflash=true;
		prev_time=time10[T2];
	}
}
if( nMotorEncoder[blockthrower]>1700)
{
	block_count=0;
	sm_light=LIGHT_OFF;
}
if(joystick.joy2_y2>0&&block_there()==false)
{
sm_light=LIGHT_ON_2;
}
break;
}
//writeDebugStreamLine("color=%d",SensorValue(S4));
//writeDebugStreamLine("count=%d",block_count);



// ********************* robotlifter ********************************


lifterEncoder = nMotorEncoder[robotlifter];
		if (joy2Btn(2) && joy2Btn(6))
		{
			lifterTrigger = false;
			if (lifterEncoder >10)
				{
					lifterSpd = -40;

				}
			else
				{
					lifterSpd = 0;

				}
		}
		else if(joy2Btn(5) && joy2Btn(6))
  	{
  		lifterSpd = jstick2Y1;
  	}
		else if ((joy2Btn(4) && joy2Btn(6)) || lifterTrigger)
		{
			lifterTrigger = true;
			if (lifterEncoder < 9000)
				{
					lifterSpd = 60;
				}
			else
				{
					lifterSpd = 0;
					lifterTrigger = false;
				}
		}
  	else
  	{
  		lifterSpd = 0;
  	}

  	motor[robotlifter] = lifterSpd;
  	if(!(joy2Btn(5) && joy2Btn(6)))
		{
			motor[flagraiser] = jstick2Y1;
		}

writeDebugStreamLine("lifterEncoder  %d",nMotorEncoder[robotlifter] );

//***************** block thrower **********************************************
			throwerEncoder = nMotorEncoder[blockthrower];
//		writeDebugStreamLine("Encoder value = %d", throwerEncoder);
		//writeDebugStreamLine("rspd = %d",motor[rightmotor] );
		//writeDebugStreamLine("lspd = %d",motor[leftmotor] );// max power is 50
//		writeDebugStreamLine("  %d",joystick.joy1_y2 );
				if (joy2Btn(8))
		{
			throwerSet = 2000;

		}

		else if (joy2Btn(7))
		{

			throwerSet = 10;

		}
 	else
  	{
  		throwerSet = throwerEncoder;
  	}

throwerSpd = FlipperArm(throwerEncoder, throwerSet);



//throwerSpd = jstick2Y2;

 motor[robotlifter] = lifterSpd;
 motor[blockthrower] = throwerSpd;

		//--------------------------Robot Code--------------------------//
		// Wait for next itteration
	  timeLeft=FOREGROUND_MS-time1[T1];
	  releaseCPU();
	  wait1Msec(timeLeft);
  }
 motor[blockgrabber] = 0;
 motor[robotlifter] = 0;
 motor[rtMotor] = 0;
 motor[ltMotor] = 0;

}
