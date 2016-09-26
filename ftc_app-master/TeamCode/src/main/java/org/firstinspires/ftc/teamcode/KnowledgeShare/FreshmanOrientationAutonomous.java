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

package com.qualcomm.ftcrobotcontroller.opmodes.KnowledgeShare;

import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;
import com.qualcomm.robotcore.hardware.Servo;

/**
 * NxtEncoderOp
 * <p>
 * Very simple op mode that demonstrates a state machine with the NXT motor controllers.
 * Should move forward, and then move backwards to its original location.
 */
public class FreshmanOrientationAutonomous extends OpMode {




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

  DcMotor motorRight;
  DcMotor motorLeft;
  Servo hammer;


  /**
   * Constructor
   */
  public FreshmanOrientationAutonomous() {

  }

  /*
   * Code to run when the op mode is first enabled goes here
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#start()
   */
  @Override
  public void init() {

      state_mach = State.STATE_ZERO;

      motorLeft = hardwareMap.dcMotor.get("motor_1");
      motorRight = hardwareMap.dcMotor.get("motor_2");

      motorRight.setDirection(DcMotor.Direction.REVERSE);
      motorRight.setMode(DcMotorController.RunMode.RESET_ENCODERS);
      motorRight.setMode(DcMotorController.RunMode.RESET_ENCODERS);

      hammer = hardwareMap.servo.get("servo_1");


  }

  /*
   * This method will be called repeatedly in a loop
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#loop()
   */
  @Override
  public void loop() {


    // The op mode should only use "write" methods (setPower, setChannelMode, etc) while in
    // WRITE_ONLY mode.



        switch (state_mach) {


          case STATE_ZERO:

              motorRight.setMode(DcMotorController.RunMode.RUN_TO_POSITION);
              motorRight.setMode(DcMotorController.RunMode.RUN_TO_POSITION);

              motorRight.setTargetPosition(1000);
              motorLeft.setTargetPosition(1000);

              motorLeft.setPower(0.75);
              motorRight.setPower(0.75);



            break;

          case STATE_ONE:



            break;


          case STATE_THREE:



            break;


        }

      }




    //end of loop


    // To read any values from the NXT controllers, we need to switch into READ_ONLY mode.
    // It takes time for the hardware to switch, so you can't switch modes within one loop of the
    // op mode. Every 17th loop, this op mode switches to READ_ONLY mode.


  /*
   * Code to run when the op mode is first disabled goes here
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#stop()
   */
  @Override
  public void stop() {


  }

  /*private boolean allowedToWrite(){
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
  }*/

}
