/* Copyright (c) 2014, 2015 Qualcomm Technologies Inc

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted (subject to the limitations in the disclaimer below) provided that
the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this
list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

Neither the name of Qualcomm Technologies Inc nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

package com.qualcomm.ftcrobotcontroller.opmodes;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.hardware.ServoController;
import com.qualcomm.robotcore.util.Range;

/**
 * TeleOp Mode
 * <p>
 * Enables control of the robot via the gamepad
 */
public class CompetitionTankServo extends OpMode {



  DcMotorController.DeviceMode devMode;
  DcMotorController DriveTrain;
  DcMotor MotorLeft;
  DcMotor MotorRight;
  DcMotorController TrackMovement;
  DcMotor TrackLeftRight;
  DcMotor TrackUpDown;

  DcMotorController TrackMovement2;
  DcMotor TrackInOut;

  Servo ArmFlipper;
  ServoController ServoController;


  int numOpLoops = 1;

  /*
   * Code to run when the op mode is first enabled goes here
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#init()
   */
  @Override
  public void init() {

    MotorLeft = hardwareMap.dcMotor.get("MotorLeft");
    MotorRight = hardwareMap.dcMotor.get("MotorRight");
    TrackLeftRight = hardwareMap.dcMotor.get("TrackLeftRight");
    TrackUpDown = hardwareMap.dcMotor.get("TrackUpDown");
    TrackInOut = hardwareMap.dcMotor.get("TrackInOut");




    DriveTrain = hardwareMap.dcMotorController.get("DriveTrain");
    TrackMovement = hardwareMap.dcMotorController.get("TrackMovement");
    TrackMovement2 = hardwareMap.dcMotorController.get("TrackMovement2");

    ServoController= hardwareMap.servoController.get("ServoController");
    ArmFlipper=hardwareMap.servo.get("ArmFlipper");
  }

  /*
   * Code that runs repeatedly when the op mode is first enabled goes here
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#init_loop()
   */
  @Override
  public void init_loop() {

    devMode = DcMotorController.DeviceMode.WRITE_ONLY;

    //motorRight.setDirection(DcMotor.Direction.REVERSE);
    //motorLeft.setDirection(DcMotor.Direction.REVERSE);

    // set the mode
    // Nxt devices start up in "write" mode by default, so no need to switch device modes here.

    TrackMovement.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
    TrackMovement2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
    DriveTrain.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);

    ArmFlipper.setPosition(0.8);

  }

  /*
   * This method will be called repeatedly in a loop
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#loop()
   */
  @Override
  public void loop() {

    // The op mode should only use "write" methods (setPower, setChannelMode, etc) while in
    // WRITE_ONLY mode or SWITCHING_TO_WRITE_MODE
    if (allowedToWrite()) {
    /*
     * Gamepad 1
     *
     * Gamepad 1 controls the motors via the left stick, and it controls the wrist/claw via the a,b,
     * x, y buttons
     */
      /*if (gamepad1.dpad_left) {
        // Nxt devices start up in "write" mode by default, so no need to switch modes here.
        MotorLeft.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);
        MotorRight.setChannelMode(DcMotorController.RunMode.RUN_WITHOUT_ENCODERS);

      }
      if (gamepad1.dpad_right) {
        // Nxt devices start up in "write" mode by default, so no need to switch modes here.
        MotorLeft.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
        MotorRight.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
      }*/



      float right = -gamepad1.right_stick_y;
      float left = -gamepad1.left_stick_y;


       //clip the right/left values so that the values never exceed +/- 1

      MotorRight.setPower(right);
      MotorLeft.setPower(left);





      // clip the right/left values so that the values never exceed +/- 1


      // write the values to the motors

    if(gamepad1.a)
    {
      ArmFlipper.setPosition(0.9);
    }

      if(gamepad1.b)
      {
        ArmFlipper.setPosition(0);
      }



    /*
     * Gamepad 2
     *

      }*/

      //Control Tracks going up down left right using right stick of gamepad 2
      float trackUpDown = -(gamepad2.right_stick_y)/3*2;
      float trackLeftRight = -(gamepad2.right_stick_x)/2;

      float TrackLeftRightPower = Range.clip(trackLeftRight, -1, 1);
      float TrackUpDownPower = Range.clip(trackUpDown, -1, 1);

      TrackUpDown.setPower(TrackUpDownPower);
      TrackLeftRight.setPower(TrackLeftRightPower);

      //Control Tracks to pick up cubes
      float trackInOut=gamepad2.left_stick_y;

      float TrackInOutPower = Range.clip(trackInOut, -1, 1);

      TrackInOut.setPower(TrackInOutPower);



    }

    // To read any values from the NXT controllers, we need to switch into READ_ONLY mode.
    // It takes time for the hardware to switch, so you can't switch modes within one loop of the
    // op mode. Every 17th loop, this op mode switches to READ_ONLY mode, and gets the current power.
    /*if (numOpLoops % 17 == 0) {
      // Note: If you are using the NxtDcMotorController, you need to switch into "read" mode
      // before doing a read, and into "write" mode before doing a write. This is because
      // the NxtDcMotorController is on the I2C interface, and can only do one at a time. If you are
      // using the USBDcMotorController, there is no need to switch, because USB can handle reads
      // and writes without changing modes. The NxtDcMotorControllers start up in "write" mode.
      // This method does nothing on USB devices, but is needed on Nxt devices.
      TrackMovement.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
      TrackMovement2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
      DriveTrain.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);
    }

    // Every 17 loops, switch to read mode so we can read data from the NXT device.
    // Only necessary on NXT devices.
    if (DriveTrain.getMotorControllerDeviceMode() == DcMotorController.DeviceMode.READ_ONLY) {

      // Update the reads after some loops, when the command has successfully propagated through.
      telemetry.addData("Telemetry", "Data");
      telemetry.addData("left motor", MotorLeft.getPower());
      telemetry.addData("right motor", MotorRight.getPower());
      telemetry.addData("Tracks In out: ", TrackInOut.getPower());
      telemetry.addData("Tracks Up Down: ", TrackUpDown.getPower());
      telemetry.addData("Tracks Left Right: ", TrackLeftRight.getPower());
      telemetry.addData("Right Encoder: ", MotorRight.getCurrentPosition());
      telemetry.addData("Left Encoder: ", MotorLeft.getCurrentPosition());



      // Only needed on Nxt devices, but not on USB devices
      TrackMovement.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
      TrackMovement2.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
      DriveTrain.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);

      // Reset the loop
      numOpLoops = 0;
    }*/

    // Update the current devMode
    devMode = DriveTrain.getMotorControllerDeviceMode();
    numOpLoops++;
  }


  // If the device is in either of these two modes, the op mode is allowed to write to the HW.
  private boolean allowedToWrite(){
    return (devMode == DcMotorController.DeviceMode.WRITE_ONLY);
  }


  double scaleInput(double dVal)  {
    double[] scaleArray = { 0.0, 0.05, 0.09, 0.10, 0.12, 0.15, 0.18, 0.24,
            0.30, 0.36, 0.43, 0.50, 0.60, 0.72, 0.85, 1.00, 1.00 };

    // get the corresponding index for the scaleInput array.
    int index = (int) (dVal * 16.0);

    // index should be positive.
    if (index < 0) {
      index = -index;
    }

    // index cannot exceed size of array minus 1.
    if (index > 16) {
      index = 16;
    }

    // get value from the array.
    double dScale = 0.0;
    if (dVal < 0) {
      dScale = -scaleArray[index];
    } else {
      dScale = scaleArray[index];
    }

    // return scaled value.
    return dScale;
  }
}
