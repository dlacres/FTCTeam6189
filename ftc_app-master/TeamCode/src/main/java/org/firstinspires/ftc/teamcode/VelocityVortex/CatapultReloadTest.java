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
package org.firstinspires.ftc.teamcode.VelocityVortex;

import com.qualcomm.robotcore.eventloop.opmode.Autonomous;
import com.qualcomm.robotcore.eventloop.opmode.Disabled;
import com.qualcomm.robotcore.eventloop.opmode.LinearOpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.util.ElapsedTime;

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
@Disabled
@Autonomous(name="Catapult Reload Test", group="Test")

public class CatapultReloadTest extends LinearOpMode {

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
    static final int CATAPULT_POSITION = -1900;


    double RedDifferenceLt;
    double BlueDifferenceLt;
    double GreenDifferenceLt;

    double RedDifference2Lt;
    double BlueDifference2Lt;
    double GreenDifference2Lt;

    double RedComparsionLt;
    double BlueComparsionLt;

    double RedDifferenceRt;
    double BlueDifferenceRt;
    double GreenDifferenceRt;

    double RedDifference2Rt;
    double BlueDifference2Rt;
    double GreenDifference2Rt;

    double RedComparsionRt;
    double BlueComparsionRt;

    int TrueRed = 255;
    int TrueBlue = 255;


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

        RedComparsionRt = 0;
        BlueComparsionRt = 0;
        GreenDifferenceRt = 0;
        RedDifferenceRt = 0;
        BlueDifferenceRt = 0;
        GreenDifference2Rt = 0;
        RedDifference2Rt = 0;
        BlueDifference2Rt = 0;

        RedComparsionLt = 0;
        BlueComparsionLt = 0;
        GreenDifferenceLt = 0;
        RedDifferenceLt = 0;
        BlueDifferenceLt = 0;
        GreenDifference2Lt = 0;
        RedDifference2Lt = 0;
        BlueDifference2Lt = 0;

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
            robot.rightMotor.setPower(0.75);
            robot.leftMotor.setPower(-0.75);
            idle();
        }


        while (!robot.touchSensor.isPressed())
        {
            telemetry.addData("Touch Sensor: ", robot.touchSensor.isPressed());
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

        BlueDifferenceRt = Math.pow(robot.colorSensor0.blue()-TrueBlue,2);
        GreenDifferenceRt = Math.pow(robot.colorSensor0.green()-0,2);
        RedDifferenceRt = Math.pow(robot.colorSensor0.red()-0,2);
        BlueComparsionRt = Math.sqrt(BlueDifferenceRt + RedDifferenceRt + GreenDifferenceRt);

        BlueDifference2Rt = Math.pow(robot.colorSensor0.blue()-0,2);
        GreenDifference2Rt = Math.pow(robot.colorSensor0.green()-0,2);
        RedDifference2Rt = Math.pow(robot.colorSensor0.red()-TrueRed,2);
        RedComparsionRt = Math.sqrt(BlueDifference2Rt + RedDifference2Rt + GreenDifference2Rt);

        BlueDifferenceLt = Math.pow(robot.colorSensor2.blue()-TrueBlue,2);
        GreenDifferenceLt = Math.pow(robot.colorSensor2.green()-0,2);
        RedDifferenceLt = Math.pow(robot.colorSensor2.red()-0,2);
        BlueComparsionLt = Math.sqrt(BlueDifferenceLt + RedDifferenceLt + GreenDifferenceLt);

        BlueDifference2Lt = Math.pow(robot.colorSensor2.blue()-0,2);
        GreenDifference2Lt = Math.pow(robot.colorSensor2.green()-0,2);
        RedDifference2Lt = Math.pow(robot.colorSensor2.red()-TrueRed,2);
        RedComparsionLt = Math.sqrt(BlueDifference2Lt + RedDifference2Lt + GreenDifference2Lt);

        if ((BlueComparsionRt < RedComparsionRt) && (RedComparsionLt < BlueComparsionLt))//Right Sensor Sees Blue and Left Sensor sees Red
        {
            robot.buttonLeft.setPosition(1);
        }
        if ((RedComparsionRt < BlueComparsionRt) && (BlueComparsionLt < RedComparsionLt))//Right Sensor Sees Red and Left Sensor sees Blue
        {
            robot.buttonRight.setPosition(0.25);
        }

        /*if (robot.colorSensor0.argb() < BlueHue)
        {
            robot.buttonRight.setPosition(0.25);
        }
        if (robot.colorSensor0.argb() > RedHue)
        {
            robot.buttonLeft.setPosition(1);
        }              //End First Beacon Code

        encoderDrive(0.7,-2,-2,2);
        encoderDrive(0.7,2,2,2);

        encoderDrive(0.7,-21,-21,4);
        encoderDrive(0.5,7,-7,4);

        robot.buttonLeft.setPosition(0.25);
        robot.buttonRight.setPosition(1);

        RedComparsionRt = 0;
        BlueComparsionRt = 0;
        GreenDifferenceRt = 0;
        RedDifferenceRt = 0;
        BlueDifferenceRt = 0;
        GreenDifference2Rt = 0;
        RedDifference2Rt = 0;
        BlueDifference2Rt = 0;

        RedComparsionLt = 0;
        BlueComparsionLt = 0;
        GreenDifferenceLt = 0;
        RedDifferenceLt = 0;
        BlueDifferenceLt = 0;
        GreenDifference2Lt = 0;
        RedDifference2Lt = 0;
        BlueDifference2Lt = 0;

        encoderDrive(0.7,6,6,3);

        while (robot.colorSensor1.getRawLightDetected() < THRESHOLD)
        {
            robot.rightMotor.setPower(0.9);
            robot.leftMotor.setPower(0.9);
            idle();
        }

        encoderDrive(0.5,-5,5,2);*/

        robot.leftMotor.setPower(0);
        robot.rightMotor.setPower(0);

        robot.catapultMotor.setTargetPosition(CATAPULT_POSITION);
        robot.catapultMotor.setMode(DcMotor.RunMode.RUN_TO_POSITION);
        robot.catapultMotor.setPower(0.75);

        while (robot.catapultMotor.isBusy())
        {
            idle();
        }
        robot.catapultMotor.setPower(0);

        robot.catapultReload.setPosition(0);

        /*encoderDrive(0.5,2,2,3);

        while (robot.colorSensor1.getRawLightDetected() < THRESHOLD)
        {
            robot.rightMotor.setPower(0.75);
            robot.leftMotor.setPower(-0.75);
            idle();
        }

        while (!robot.touchSensor.isPressed())
        {
            telemetry.addData("Touch Sensor: ", robot.touchSensor.isPressed());
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

        BlueDifferenceRt = Math.pow(robot.colorSensor0.blue()-TrueBlue,2);
        GreenDifferenceRt = Math.pow(robot.colorSensor0.green()-0,2);
        RedDifferenceRt = Math.pow(robot.colorSensor0.red()-0,2);
        BlueComparsionRt = Math.sqrt(BlueDifferenceRt + RedDifferenceRt + GreenDifferenceRt);

        BlueDifference2Rt = Math.pow(robot.colorSensor0.blue()-0,2);
        GreenDifference2Rt = Math.pow(robot.colorSensor0.green()-0,2);
        RedDifference2Rt = Math.pow(robot.colorSensor0.red()-TrueRed,2);
        RedComparsionRt = Math.sqrt(BlueDifference2Rt + RedDifference2Rt + GreenDifference2Rt);

        BlueDifferenceLt = Math.pow(robot.colorSensor2.blue()-TrueBlue,2);
        GreenDifferenceLt = Math.pow(robot.colorSensor2.green()-0,2);
        RedDifferenceLt = Math.pow(robot.colorSensor2.red()-0,2);
        BlueComparsionLt = Math.sqrt(BlueDifferenceLt + RedDifferenceLt + GreenDifferenceLt);

        BlueDifference2Lt = Math.pow(robot.colorSensor2.blue()-0,2);
        GreenDifference2Lt = Math.pow(robot.colorSensor2.green()-0,2);
        RedDifference2Lt = Math.pow(robot.colorSensor2.red()-TrueRed,2);
        RedComparsionLt = Math.sqrt(BlueDifference2Lt + RedDifference2Lt + GreenDifference2Lt);

        if ((BlueComparsionRt < RedComparsionRt) && (RedComparsionLt < BlueComparsionLt))//Right Sensor Sees Blue and Left Sensor sees Red
        {
            robot.buttonRight.setPosition(0.25);
        }
        if ((RedComparsionRt < BlueComparsionRt) && (BlueComparsionLt < RedComparsionLt))//Right Sensor Sees Red and Left Sensor sees Blue
        {
            robot.buttonLeft.setPosition(1);
        }

        encoderDrive(0.75,-2,-2,2);
        encoderDrive(0.75,2.5,2.5,2);
        encoderDrive(0.75,-2,-2,2);

        while (opModeIsActive())
        {
            telemetry.addData("Hue: ",robot.colorSensor0.argb());
            telemetry.update();
            idle();
        }

        telemetry.addData("Path", "Complete");
        telemetry.update();*/
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
