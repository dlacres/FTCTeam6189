package org.firstinspires.ftc.teamcode.ReusableClasses;

import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.util.Range;

/**
 * Created by Andrew on 9/29/2016.
 */
public class RobotDrive {

	scaleInput myscaleInput;
	private DcMotor rightMotor;
	private DcMotor leftMotor;



	public RobotDrive(DcMotor right, DcMotor left)
	{
		leftMotor = left;
		rightMotor = right;
	}

	public void arcadeDrive(float forwardSpeed, float turnRate)
	{
		float rightSpeed = (forwardSpeed - turnRate);
		float leftSpeed = (forwardSpeed + turnRate);

		// clip the right/left values so that the values never exceed +/- 1

		rightSpeed = Range.clip(rightSpeed, -1, 1);
		leftSpeed = Range.clip(leftSpeed, -1, 1);

		// scale the joystick value to make it easier to control
		// the robot more precisely at slower speeds.

		//rightSpeed = (float)myscaleInput.scaleValue(rightSpeed);
		//leftSpeed =  (float)myscaleInput.scaleValue(leftSpeed);

		// write the values to the motors
		leftMotor.setPower((double)leftSpeed);
		rightMotor.setPower((double)rightSpeed);
	}

	public void tankDrive(float leftJoystick,float rightJoystick )
	{
		float right = rightJoystick;
		float left = leftJoystick;

		right = Range.clip(right, -1, 1);
		left = Range.clip(left, -1, 1);

		// scale the joystick value to make it easier to control
		// the robot more precisely at slower speeds.

		//right = (float)myscaleInput.scaleValue(right);
		//left =  (float)myscaleInput.scaleValue(left);

		// write the values to the motors
		leftMotor.setPower((double)left);
		rightMotor.setPower((double)right);

	}


}
