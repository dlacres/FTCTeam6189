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

package com.qualcomm.ftcrobotcontroller.opmodes.FirstResqSeason;



import com.qualcomm.robotcore.hardware.DcMotorController;
import com.qualcomm.robotcore.util.Range;

/**
 * TeleOp Mode
 * <p>
 * Enables control of the robot via the gamepad
 */
public class CompetitionTankServo extends TeleopRobotHardware {




  /*
   * This method will be called repeatedly in a loop
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#loop()
   */
  @Override
  public void loop() {

    // The op mode should only use "write" methods (setPower, setChannelMode, etc) while in
    // WRITE_ONLY mode or SWITCHING_TO_WRITE_MODE

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



      float right = (gamepad1.right_stick_y);
      float left = -(gamepad1.left_stick_y);


       //clip the right/left values so that the values never exceed +/- 1

      MotorRight.setPower(right);
      MotorLeft.setPower(left);





      // clip the right/left values so that the values never exceed +/- 1


      // write the values to the motors

    if(gamepad1.a)
    {
      PauletteFlipper.setPosition(0.9);
    }

      if(gamepad1.b)
      {
        PauletteFlipper.setPosition(0);
      }


      if(gamepad1.left_bumper)
      {
        ArmFlipperLeft.setPosition(1);
      }

      if(gamepad1.left_trigger > 0)
      {
        ArmFlipperLeft.setPosition(0.5);
      }

      if(gamepad1.right_trigger > 0)
      {
        ArmFlipperRight.setPosition(1);
      }

      if(gamepad1.right_bumper)
      {
        ArmFlipperRight.setPosition(0.5);
      }

    /*
     * Gamepad 2
     *

      }*/



      //Control Tracks going up down left right using right stick of gamepad 2
      if(Mode==0)
      {
        float trackUpDown = -(gamepad2.right_stick_y)/3;


        float TrackUpDownPower = Range.clip(trackUpDown, -1, 1);

        TrackUpDown.setPower(TrackUpDownPower);
      }

      else if (Mode==1)
      {
        float trackUpDown = -(gamepad2.right_stick_y);


        float TrackUpDownPower = Range.clip(trackUpDown, -1, 1);

        TrackUpDown.setPower(TrackUpDownPower);
      }

        if(gamepad2.dpad_down)
        {
          LinearSlidePower2 = 1f;
          LinearSlide2.setPower(LinearSlidePower2);
        }
      else if(gamepad2.dpad_up)
      {
        LinearSlidePower2 = -1f;
        LinearSlide2.setPower(LinearSlidePower2);
      }
      else
      {
        LinearSlidePower2 = 0.0f;
        LinearSlide2.setPower(LinearSlidePower2);
      }

      if(gamepad2.y)
      {
        LinearSlidePower = 1;
        LinearSlide.setPower(LinearSlidePower);
      }
      else if(gamepad2.a)
      {
        LinearSlidePower = -1;
        LinearSlide.setPower(LinearSlidePower);
      }
      else
      {
        LinearSlidePower = 0;
        LinearSlide.setPower(LinearSlidePower);
      }

      if(gamepad2.left_trigger > 0)
      {
      Winch.setPower(1);
      }
     else if(gamepad2.right_trigger > 0)
      {
        Winch.setPower(-1);
      }
      else
      {
        Winch.setPower(0);
      }


      if (gamepad2.left_bumper)
      {
        RightPlow.setPosition(0.9);
        LeftPlow.setPosition(0.0);
      }

      if (gamepad2.right_bumper)
      {
        RightPlow.setPosition(0.1);
        LeftPlow.setPosition(0.9);
      }
    telemetry.addData("Sonar : ", Sonar.getUltrasonicLevel());
    telemetry.addData("LinearSlidePower : ", LinearSlidePower);
    telemetry.addData("LinearSlidePower2 : ", LinearSlidePower2);





    // To read any values from the NXT controllers, we need to switch into READ_ONLY mode.
    // It takes time for the hardware to switch, so you can't switch modes within one loop of the
    // op mode. Every 17th loop, this op mode switches to READ_ONLY mode, and gets the current power.
    /*if (numOpLoops % 17 == 0) {
      // Note: If you are using the NxtDcMotorController, you needd to switch into "read" mode
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
