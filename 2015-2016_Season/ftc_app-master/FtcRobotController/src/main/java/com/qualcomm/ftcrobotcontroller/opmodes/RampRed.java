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

import com.qualcomm.ftccommon.DbgLog;
import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.hardware.ServoController;
import com.qualcomm.robotcore.hardware.UltrasonicSensor;

/**
 * NxtEncoderOp
 * <p>
 * Very simple op mode that demonstrates a state machine with the NXT motor controllers.
 * Should move forward, and then move backwards to its original location.
 */
public class RampRed extends OpMode {

  DcMotorController.DeviceMode devMode;
  DcMotorController DriveTrain;
  DcMotor MotorLeft;
  DcMotor MotorRight;
  DcMotorController DriveTrainEncoder;




  DcMotor MotorLeftEncoder;
  DcMotor MotorRightEncoder;




  Servo ArmFlipperRight;
  Servo ArmFlipperLeft;
  Servo PauletteFlipper;
  Servo Plow;
  ServoController ServoController;
  UltrasonicSensor Sonar;


  //int motorRightCurrentEncoder;
  //int motorLeftCurrentEncoder;
  int motorRightTargetEncoder;
  int motorLeftTargetEncoder;

  DcMotorController.RunMode motorRightRunMode;
  DcMotorController.RunMode motorLeftRunMode;

  int NumLoop = 0;


  State state_mach;
  public enum State {
    STATE_ZERO,
    STATE_ONE,
    STATE_TWO,
    STATE_THREE,
    STATE_FOUR,
    State_FIVE,
    State_SIX,
    State_SEVEN
  }
  //140 encoder clicks per inch when going straight.
  int firstTarget = 140 * 90;
  int secondTarget = 1200;
  int thirdTarget = 140 * 23;

  /**
   * Constructor
   */
  public RampRed() {

  }

  /*
   * Code to run when the op mode is first enabled goes here
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#start()
   */
  @Override
  public void init() {

    state_mach = State.State_SEVEN;
    MotorLeft = hardwareMap.dcMotor.get("MotorLeft");
    MotorRight = hardwareMap.dcMotor.get("MotorRight");
    MotorLeftEncoder = hardwareMap.dcMotor.get("LinearSlide");
    MotorRightEncoder = hardwareMap.dcMotor.get("TrackUpDown");

    MotorLeftEncoder=hardwareMap.dcMotor.get("TrackUpDown");
    MotorRightEncoder=hardwareMap.dcMotor.get("LinearSlide");



    DriveTrain = hardwareMap.dcMotorController.get("DriveTrain");
    DriveTrainEncoder = hardwareMap.dcMotorController.get("TrackMovement");


    ServoController = hardwareMap.servoController.get("ServoController");
    ArmFlipperRight = hardwareMap.servo.get("ArmFlipperRight");
    ArmFlipperLeft = hardwareMap.servo.get("ArmFlipperLeft");
    PauletteFlipper = hardwareMap.servo.get("PauletteFlipper");
    Plow = hardwareMap.servo.get("Plow");
    Sonar = hardwareMap.ultrasonicSensor.get("Sonar");

    MotorRight.setDirection(DcMotor.Direction.REVERSE);
    MotorRightEncoder.setDirection(DcMotor.Direction.REVERSE);
    MotorLeft.setDirection(DcMotor.Direction.REVERSE);
    //MotorLeftEncoder.setDirection(DcMotor.Direction.REVERSE);

    MotorRightEncoder.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);
    MotorLeftEncoder.setChannelMode(DcMotorController.RunMode.RESET_ENCODERS);


    // set the mode
    // Nxt devices start up in "write" mode by default, so no need to switch device modes here.


    PauletteFlipper.setPosition(0.9);
    ArmFlipperLeft.setPosition(0);
    ArmFlipperRight.setPosition(1);
    Plow.setPosition(0.1);
  }

  /*
   * This method will be called repeatedly in a loop
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#loop()
   */
  @Override
  public void loop() {
    DbgLog.error("mode: " + devMode);

    // The op mode should only use "write" methods (setPower, setChannelMode, etc) while in
    // WRITE_ONLY mode.

    if(NumLoop == 0)
    {
      MotorRightEncoder.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
      MotorLeftEncoder.setChannelMode(DcMotorController.RunMode.RUN_USING_ENCODERS);
    }

    if(NumLoop == 12) {

      DriveTrainEncoder.setMotorControllerDeviceMode(DcMotorController.DeviceMode.READ_ONLY);

    }

      if (NumLoop >= 14) {

        switch (state_mach) {


          case STATE_ZERO:


            MotorLeft.setPower(0.7);
            MotorRight.setPower(0.7);

            //if((MotorLeftEncoder.getCurrentPosition() <= motorLeftTargetEncoder)&&(MotorRightEncoder.getCurrentPosition() <= motorRightTargetEncoder))
            if ((MotorLeftEncoder.getCurrentPosition() >= firstTarget) && (MotorRightEncoder.getCurrentPosition() >= firstTarget)) {
              MotorLeft.setPower(0.0);
              MotorRight.setPower(0.0);
              state_mach = State.STATE_ONE;
            }
            else
            {
              MotorLeft.setPower(0.7);
              MotorRight.setPower(0.7);
            }

            break;

          case STATE_ONE:


            motorLeftTargetEncoder = secondTarget + firstTarget;
            motorRightTargetEncoder = secondTarget - firstTarget;

            // if((motorLeftCurrentEncoder<=motorLeftTargetEncoder)&&(motorRightCurrentEncoder>=motorRightTargetEncoder))
            if ((MotorLeftEncoder.getCurrentPosition() >= motorLeftTargetEncoder) && (MotorRightEncoder.getCurrentPosition() >= motorRightTargetEncoder)) {
              MotorLeft.setPower(0.0);
              MotorRight.setPower(0.0);
              state_mach = State.STATE_THREE;
            } else {
              MotorLeft.setPower(-0.7);
              MotorRight.setPower(0.7);
            }

            break;


          case STATE_THREE:

            motorLeftTargetEncoder = secondTarget + firstTarget + thirdTarget;
            motorRightTargetEncoder = secondTarget - firstTarget + thirdTarget;

            if ((MotorLeftEncoder.getCurrentPosition() <= motorLeftTargetEncoder) && (MotorRightEncoder.getCurrentPosition() <= motorRightTargetEncoder))
            {
              MotorLeft.setPower(0.0);
              MotorRight.setPower(0.0);
            }
            else
            {
              MotorLeft.setPower(0.4);
              MotorRight.setPower(0.4);
            }

            break;

          case State_SEVEN:
            Plow.setPosition(0.9);
            state_mach = State.STATE_ZERO;

            break;

        }
        telemetry.addData("Telemetry", "Data");
        telemetry.addData("right curr enc", MotorRightEncoder.getCurrentPosition());
        telemetry.addData("left curr enc", MotorLeftEncoder.getCurrentPosition());
        telemetry.addData("state", state_mach);
      }



    NumLoop++;
    }//end of loop


    // To read any values from the NXT controllers, we need to switch into READ_ONLY mode.
    // It takes time for the hardware to switch, so you can't switch modes within one loop of the
    // op mode. Every 17th loop, this op mode switches to READ_ONLY mode.


  /*
   * Code to run when the op mode is first disabled goes here
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#stop()
   */
  @Override
  public void stop() {
    PauletteFlipper.setPosition(0);

  }

  private boolean allowedToWrite(){
    return (devMode == DcMotorController.DeviceMode.WRITE_ONLY);
  }

  private boolean withinMarginOfError(int goal, int value) {
    int lowerMargin = goal - 2;
    int upperMargin = goal + 2;
    return (value >= lowerMargin && value <= upperMargin);
  }

  private boolean bothEncodersZero() {
    return MotorLeftEncoder.getCurrentPosition() == 0 && MotorRightEncoder.getCurrentPosition() == 0;
  }

  private boolean motorsInCorrectMode(DcMotorController.RunMode runMode) {
    return MotorLeftEncoder.getMode() == runMode &&  MotorRightEncoder.getMode() == runMode;
  }

}
