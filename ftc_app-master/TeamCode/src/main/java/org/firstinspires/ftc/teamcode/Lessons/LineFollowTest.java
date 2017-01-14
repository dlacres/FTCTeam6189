/*
Copyright (c) 2016 Robert Atkinson

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted (subject to the limitations in the disclaimer below) provided that
the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

Neither the name of Robert Atkinson nor the names of his contributors may be used to
endorse or promote products derived from this software without specific prior
written permission.

NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESSFOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
package org.firstinspires.ftc.teamcode.Lessons;

import com.qualcomm.robotcore.eventloop.opmode.Autonomous;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.util.ElapsedTime;

import org.firstinspires.ftc.teamcode.VelocityVortex.HardwareCompetitionRobot;

/**
 * This file illustrates the concept of driving a path based on encoder counts.
 * It uses the common Pushbot hardware class to define the drive on the robot.
 * The code is structured as a LinearOpMode
 *
 * The code REQUIRES that you DO have encoders on the wheels,
 *   otherwise you would use: PushbotAutoDriveByTime;
 *
 *  This code ALSO requires that the drive Motors have been configured such that a positive
 *  power command moves them forwards, and causes the encoders to count UP.
 *
 *   The desired path in this example is:
 *   - Drive forward for 48 inches
 *   - Spin right for 12 Inches
 *   - Drive Backwards for 24 inches
 *   - Stop and close the claw.
 *
 *  The code is written using a method called: encoderDrive(speed, leftInches, rightInches, timeoutS)
 *  that performs the actual movement.
 *  This methods assumes that each movement is relative to the last stopping place.
 *  There are other ways to perform encoder based moves, but this method is probably the simplest.
 *  This code uses the RUN_TO_POSITION mode to enable the Motor controllers to generate the run profile
 *
 * Use Android Studios to Copy this Class, and Paste it into your team's code folder with a new name.
 * Remove or comment out the @Disabled line to add this opmode to the Driver Station OpMode list
 */
//@Disabled
@Autonomous(name="Line Follower Test", group="Test")

public class LineFollowTest extends LinearOpMode {

    /* Declare OpMode members. */
    HardwareCompetitionRobot    robot   = new HardwareCompetitionRobot();   // Use a Pushbot's hardware
    private ElapsedTime     runtime = new ElapsedTime();


    static final double     COUNTS_PER_MOTOR_REV    = 1440 ;    // eg: TETRIX Motor Encoder
    static final double     DRIVE_GEAR_REDUCTION    = 2.0 ;     // This is < 1.0 if geared UP
    static final double     WHEEL_DIAMETER_INCHES   = 4.0 ;     // For figuring circumference
    static final double     COUNTS_PER_INCH         = (COUNTS_PER_MOTOR_REV * DRIVE_GEAR_REDUCTION) /
                                                      (WHEEL_DIAMETER_INCHES * 3.1415);
    static final double     DRIVE_SPEED             = 0.6;
    static final double     TURN_SPEED              = 0.5;

    static final double THRESHOLD = 2.2;


    double RedDifference;
    double BlueDifference;
    double GreenDifference;

    double RedDifference2;
    double BlueDifference2;
    double GreenDifference2;

    double RedComparsion;
    double BlueComparsion;

    int TrueRed = 255;
    int TrueBlue = 255;

    int BlueHue = 6000000;
    int RedHue = 6500000;
    int RedHueSample = 0;
    int BlueHueSample = 0;


    @Override
    public void runOpMode() throws InterruptedException {

        /*
         * Initialize the drive system variables.
         * The init() method of the hardware class does all the work here
         */
        robot.init(hardwareMap);

        // Send telemetry message to signify robot waiting;
        telemetry.addData("Status", "Resetting Encoders");    //
        telemetry.update();


        robot.leftMotor.setMode(DcMotor.RunMode.STOP_AND_RESET_ENCODER);
        robot.rightMotor.setMode(DcMotor.RunMode.STOP_AND_RESET_ENCODER);
        idle();

        robot.leftMotor.setMode(DcMotor.RunMode.RUN_USING_ENCODER);
        robot.rightMotor.setMode(DcMotor.RunMode.RUN_USING_ENCODER);

        // Send telemetry message to indicate successful Encoder reset
        telemetry.addData("Path0",  "Starting at %7d :%7d",
                          robot.leftMotor.getCurrentPosition(),
                          robot.rightMotor.getCurrentPosition());
        telemetry.update();

        RedComparsion = 0;
        BlueComparsion = 0;

        GreenDifference = 0;
        RedDifference = 0;
        BlueDifference = 0;

        GreenDifference2 = 0;
        RedDifference2 = 0;
        BlueDifference2 = 0;

        BlueHueSample = 0;
        RedHueSample = 0;

        // Wait for the game to start (driver presses PLAY)
        waitForStart();

        // Step through each leg of the path,
        // Note: Reverse movement is obtained by setting a negative distance (not speed)

        /*while (robot.colorSensor1.getRawLightDetected() < THRESHOLD)//Start First Beacon Code
        {
            robot.rightMotor.setPower(0.75);
            robot.leftMotor.setPower(0.75);
            idle();
        }
        encoderDrive(0.5,2,2,3);

        while (robot.colorSensor1.getRawLightDetected() < THRESHOLD)
        {
            robot.rightMotor.setPower(-0.75);
            robot.leftMotor.setPower(0.75);
            idle();
        }


        while (!robot.touchSensor.isPressed())
        {
            telemetry.addData("Touch Sensor: ", false);
            telemetry.update();

            // If the sensor is on the line
            // only the right motor rotates to move it off the line
            while (robot.colorSensor1.getRawLightDetected() >= THRESHOLD) {
                robot.rightMotor.setPower(0.4);
                robot.leftMotor.setPower(0);
                idle();
            }
            // Otherwise (if the sensor is off the line)
            // only the left motor rotates to move it back toward the line
            while (robot.colorSensor1.getRawLightDetected() <= THRESHOLD) {
                robot.leftMotor.setPower(0.4);
                robot.rightMotor.setPower(0);
                idle();
            }
            idle();
        }
        robot.rightMotor.setPower(0);
        robot.leftMotor.setPower(0);

        BlueDifference = java.lang.Math.pow(robot.colorSensor0.blue()-TrueBlue,2);
        GreenDifference = java.lang.Math.pow(robot.colorSensor0.green()-0,2);
        RedDifference = java.lang.Math.pow(robot.colorSensor0.red()-0,2);

        BlueComparsion = java.lang.Math.sqrt(BlueDifference + RedDifference + GreenDifference);

        BlueDifference2 = java.lang.Math.pow(robot.colorSensor0.blue()-0,2);
        GreenDifference2 = java.lang.Math.pow(robot.colorSensor0.green()-0,2);
        RedDifference2 = java.lang.Math.pow(robot.colorSensor0.red()-TrueRed,2);

        RedComparsion = java.lang.Math.sqrt(BlueDifference2 + RedDifference2 + GreenDifference2);

        if (BlueComparsion < RedComparsion)//Sensor Sees Blue
        {
            robot.buttonRight.setPosition(0.25);
        }
        if (RedComparsion < BlueComparsion)//Sensor Sees Red
        {
            robot.buttonLeft.setPosition(1);
        }

        /*if (robot.colorSensor0.argb() < BlueHue)
        {
            robot.buttonRight.setPosition(0.25);
        }
        if (robot.colorSensor0.argb() > RedHue)
        {
            robot.buttonLeft.setPosition(1);
        }*/                 //End First Beacon Code

        /*encoderDrive(0.7,-2,-2,2);
        encoderDrive(0.7,2,2,2);

        encoderDrive(0.7,-19,-19,4);
        encoderDrive(0.5,-7,7,4);

        robot.buttonLeft.setPosition(0.25);
        robot.buttonRight.setPosition(1);

        RedComparsion = 0;
        BlueComparsion = 0;

        GreenDifference = 0;
        RedDifference = 0;
        BlueDifference = 0;

        GreenDifference2 = 0;
        RedDifference2 = 0;
        BlueDifference2 = 0;

        encoderDrive(0.7,6,6,3);

        while (robot.colorSensor1.getRawLightDetected() < THRESHOLD)
        {
            robot.rightMotor.setPower(0.9);
            robot.leftMotor.setPower(0.9);
            idle();
        }
        encoderDrive(0.5,2,2,3);

        while (robot.colorSensor1.getRawLightDetected() < THRESHOLD)
        {
            robot.rightMotor.setPower(-0.5);
            robot.leftMotor.setPower(0.5);
            idle();
        }


        while (!robot.touchSensor.isPressed())
        {
            telemetry.addData("Touch Sensor: ", false);
            telemetry.update();

            // If the sensor is on the line
            // only the right motor rotates to move it off the line
            while (robot.colorSensor1.getRawLightDetected() >= THRESHOLD) {
                robot.rightMotor.setPower(0.4);
                robot.leftMotor.setPower(0);
                idle();
            }
            // Otherwise (if the sensor is off the line)
            // only the left motor rotates to move it back toward the line
            while (robot.colorSensor1.getRawLightDetected() <= THRESHOLD) {
                robot.leftMotor.setPower(0.4);
                robot.rightMotor.setPower(0);
                idle();
            }
            idle();
        }
        robot.rightMotor.setPower(0);
        robot.leftMotor.setPower(0);*/

        while (!robot.touchSensor.isPressed()) {
            telemetry.addData("Touch Sensor: ", false);
            telemetry.update();
        }

        if (robot.colorSensor0.argb() < BlueHue)
        {
            BlueHueSample = robot.colorSensor0.argb();
            RedHueSample = 0;
        }
        if (robot.colorSensor0.argb() > RedHue)
        {
            BlueHueSample = 0;
            RedHueSample = robot.colorSensor0.argb();
        }

        BlueDifference = java.lang.Math.pow(robot.colorSensor0.blue()-TrueBlue,2);
        GreenDifference = java.lang.Math.pow(robot.colorSensor0.green()-0,2);
        RedDifference = java.lang.Math.pow(robot.colorSensor0.red()-0,2);


        BlueComparsion = java.lang.Math.sqrt(BlueDifference + RedDifference + GreenDifference + BlueHueSample);

        BlueDifference2 = java.lang.Math.pow(robot.colorSensor0.blue()-0,2);
        GreenDifference2 = java.lang.Math.pow(robot.colorSensor0.green()-0,2);
        RedDifference2 = java.lang.Math.pow(robot.colorSensor0.red()-TrueRed,2);

        RedComparsion = java.lang.Math.sqrt(BlueDifference2 + RedDifference2 + GreenDifference2 + RedHueSample);

        if (BlueComparsion < RedComparsion)//Sensor Sees Blue
        {
            telemetry.addData("Red Comparsion: ", RedComparsion);
            telemetry.addData("Blue Comparsion: ", BlueComparsion);
            telemetry.addData("Beacon: ","Blue");
            telemetry.update();
            robot.buttonRight.setPosition(0.25);
        }
        if (RedComparsion < BlueComparsion)//Sensor Sees Red
        {
            telemetry.addData("Red Comparsion: ", RedComparsion);
            telemetry.addData("Blue Comparsion: ", BlueComparsion);
            telemetry.addData("Beacon: ","Red");
            telemetry.update();
            robot.buttonLeft.setPosition(1);
        }

        //encoderDrive(0.75,-2,-2,2);

        while (opModeIsActive())
        {
            telemetry.addData("Hue: ",robot.colorSensor0.argb());
            telemetry.addData("Red Comparsion: ", RedComparsion);
            telemetry.addData("Blue Comparsion: ", BlueComparsion);
            telemetry.update();
            idle();
        }

        telemetry.addData("Path", "Complete");
        telemetry.update();
    }

    /*
     *  Method to perfmorm a relative move, based on encoder counts.
     *  Encoders are not reset as the move is based on the current position.
     *  Move will stop if any of three conditions occur:
     *  1) Move gets to the desired position
     *  2) Move runs out of time
     *  3) Driver stops the opmode running.
     */
    public void encoderDrive(double speed,
                             double leftInches, double rightInches,
                             double timeoutS) throws InterruptedException {
        int newLeftTarget;
        int newRightTarget;

        // Ensure that the opmode is still active
        if (opModeIsActive()) {

            // Determine new target position, and pass to motor controller
            newLeftTarget = robot.leftMotor.getCurrentPosition() + (int)(leftInches * COUNTS_PER_INCH);
            newRightTarget = robot.rightMotor.getCurrentPosition() + (int)(rightInches * COUNTS_PER_INCH);
            robot.leftMotor.setTargetPosition(newLeftTarget);
            robot.rightMotor.setTargetPosition(newRightTarget);

            // Turn On RUN_TO_POSITION
            robot.leftMotor.setMode(DcMotor.RunMode.RUN_TO_POSITION);
            robot.rightMotor.setMode(DcMotor.RunMode.RUN_TO_POSITION);

            // reset the timeout time and start motion.
            runtime.reset();
            robot.leftMotor.setPower(Math.abs(speed));
            robot.rightMotor.setPower(Math.abs(speed));

            // keep looping while we are still active, and there is time left, and both motors are running.
            while (opModeIsActive() &&
                   (runtime.seconds() < timeoutS) &&
                   (robot.leftMotor.isBusy() && robot.rightMotor.isBusy())) {

                // Display it for the driver.
                telemetry.addData("Path1",  "Running to %7d :%7d", newLeftTarget,  newRightTarget);
                telemetry.addData("Path2",  "Running at %7d :%7d",
                                            robot.leftMotor.getCurrentPosition(),
                                            robot.rightMotor.getCurrentPosition());
                telemetry.update();

                // Allow time for other processes to run.
                idle();
            }

            // Stop all motion;
            robot.leftMotor.setPower(0);
            robot.rightMotor.setPower(0);

            // Turn off RUN_TO_POSITION
            robot.leftMotor.setMode(DcMotor.RunMode.RUN_USING_ENCODER);
            robot.rightMotor.setMode(DcMotor.RunMode.RUN_USING_ENCODER);

            //  sleep(250);   // optional pause after each move
        }
    }
}