package com.qualcomm.ftcrobotcontroller.reusableClasses;

import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.util.Range;

/**
 * Created by Andrew on 4/16/2016.
 */
public class RobotDrive {


    DcMotor rightMotor;
    DcMotor leftMotor;



    public RobotDrive(DcMotor right, DcMotor left)
    {
        leftMotor = left;
        rightMotor = right;
    }

    public void arcadeDrive(float forwardSpeed, float turnRate)
    {
        float rightspd = forwardSpeed - turnRate;
        float leftspd = forwardSpeed + turnRate;

        // clip the right/left values so that the values never exceed +/- 1

        rightspd = Range.clip(rightspd, -1, 1);
        leftspd = Range.clip(leftspd, -1, 1);

        // scale the joystick value to make it easier to control
        // the robot more precisely at slower speeds.


        // write the values to the motors
        leftMotor.setPower(leftspd);
        rightMotor.setPower(rightspd);
    }

    public void tankDrive(float leftJoystick,float rightJoystick )
    {
        float rightSpd = rightJoystick;
        float leftSpd = leftJoystick;

        rightSpd = Range.clip(rightSpd, -1, 1);
        leftSpd = Range.clip(leftSpd, -1, 1);

        // scale the joystick value to make it easier to control
        // the robot more precisely at slower speeds.


        // write the values to the motors
        leftMotor.setPower(leftSpd);
        rightMotor.setPower(rightSpd);

    }


}