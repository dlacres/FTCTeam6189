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

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.util.ElapsedTime;
import com.qualcomm.robotcore.util.Range;

import org.firstinspires.ftc.teamcode.ReusableClasses.RobotDrive;

/**
 * This file contains an example of an iterative (Non-Linear) "OpMode".
 * An OpMode is a 'program' that runs in either the autonomous or the teleop period of an FTC match.
 * The names of OpModes appear on the menu of the FTC Driver Station.
 * When an selection is made from the menu, the corresponding OpMode
 * class is instantiated on the Robot Controller and executed.
 *
 * This particular OpMode just executes a basic Tank Drive Teleop for a PushBot
 * It includes all the skeletal structure that all iterative OpModes contain.
 *
 * Use Android Studios to Copy this Class, and Paste it into your team's code folder with a new name.
 * Remove or comment out the @Disabled line to add this opmode to the Driver Station OpMode list
 */
//@Disabled
@com.qualcomm.robotcore.eventloop.opmode.TeleOp(name="TeleOp: Tank Drive", group="TeleOp")  // @Autonomous(...) is the other common choice
public class TankTeleOp extends OpMode
{
    /* Declare OpMode members. */
    //HardwareCompetitionRobot robot = new HardwareCompetitionRobot();
    private ElapsedTime runtime = new ElapsedTime();
    RobotDrive robotDrive ;
    HardwareCompetitionRobot robot = new HardwareCompetitionRobot();



    double forkLiftPower;
    double linearSlidePower;
    int Speed;

    /*
    This is where you declare variables such as motors, servos, sensors, and other variables like ints.
     */


    /*
     * Code to run ONCE when the driver hits INIT
     */
    @Override
    public void init() {
        telemetry.addData("Status", "Initialized");

        robot.init(hardwareMap);


        robotDrive = new RobotDrive(robot.rightMotor,robot.leftMotor);


        linearSlidePower = 0;
        Speed = 1;


    /*
    This is where you put init code, such as reseting variables or setting up motors, servos, and sensors with the hardware map
     */
    }

    /*
     * Code to run REPEATEDLY after the driver hits INIT, but before they hit PLAY
     */
    @Override
    public void init_loop() {
    }

    /*
     * Code to run ONCE when the driver hits PLAY
     */
    @Override
    public void start() {
        runtime.reset();
    }

    /*
     * Code to run REPEATEDLY after the driver hits PLAY but before they hit STOP
     */
    @Override
    public void loop() {
        telemetry.addData("Status", "Running: " + runtime.toString());

        //gamepad1

        robotDrive.tankDrive(-gamepad1.left_stick_y/Speed,-gamepad1.right_stick_y/Speed);

        if (gamepad1.dpad_up)//Turbo Controls
        {
            Speed = 1;
        }
        if (gamepad1.dpad_down)
        {
            Speed = 3;
        }//End Turbo Controls

        if(gamepad1.right_bumper)//Beacon Servo Controls
        {
            robot.buttonRight.setPosition(0.25);
        }
        if (gamepad1.right_trigger>0)
        {
            robot.buttonRight.setPosition(1);
        }

        if(gamepad1.left_bumper)
        {
            robot.buttonLeft.setPosition(1);
        }
        if (gamepad1.left_trigger>0)
        {
            robot.buttonLeft.setPosition(0.25);
        }//End Servo Controls

        if (gamepad1.a)//Catapult Control
        {
            robot.catapultMotor.setPower(-0.75);
        }
        else if (!gamepad1.a)
        {
            robot.catapultMotor.setPower(0);
        }

        if (gamepad1.x)//Catapult Reload Control
        {
            robot.catapultReload.setPosition(0);
        }
        else if(!gamepad1.x)
        {
            robot.catapultReload.setPosition(1);
        }//End Catapult Reload Control

        telemetry.addData("Catapult Encoder: ", robot.catapultMotor.getCurrentPosition());
        telemetry.addData("Touch Sensor Pressed: ",robot.touchSensor.isPressed());
        telemetry.addData("Touch Sensor Value: ",robot.touchSensor.getValue());
        telemetry.update();


        //gamepad2

        linearSlidePower = gamepad2.left_stick_y;
        linearSlidePower = Range.clip(linearSlidePower, -1,1);
        robot.linearSlide.setPower(linearSlidePower);
        robot.linearSlide2.setPower(-linearSlidePower);

        /*
        This is where you put your main code to run the robot. example: setting the motor speed
        or checking a sensor
         */
    }

    /*
     * Code to run ONCE after the driver hits STOP
     */
    @Override
    public void stop() {
    }

}
