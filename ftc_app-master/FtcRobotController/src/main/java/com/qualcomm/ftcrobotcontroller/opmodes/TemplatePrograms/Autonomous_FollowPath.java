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

package com.qualcomm.ftcrobotcontroller.opmodes.TemplatePrograms;

import com.qualcomm.ftcrobotcontroller.reusableClasses.followPath;
import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.util.Range;

import java.lang.Math;

/**
 * NxtEncoderOp
 * <p>
 * Very simple op mode that demonstrates a state machine with the NXT motor controllers.
 * Should move forward, and then move backwards to its original location.
 */
public class Autonomous_FollowPath extends RobotHardware {

  followPath myFollowPath;

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
    // dist, dir, spd
  int path[][]={
          {63, 0, 50},
          {63, 90, 50},
          {87, 90, 50},
          {63, 90, -50}
  };

  int SPD = 40;
  int DIST_IDX = 0;
  int DIR_IDX = 1;
  int SPD_IDX = 2;
  int pathIdx=0;
  int speedCmdZ1=0;
  long leftSpeed=0;
  long rightSpeed=0;

  /**
   * Constructor
   */
  public Autonomous_FollowPath() {

  }

  /*
   * Code to run when the op mode is first enabled goes here
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#start()
   */
  @Override
  public void init() {

    state_mach = State.STATE_ZERO;
    //myFollowPath = new followPath(hardwareMap.dcMotor.get("motor_2"),hardwareMap.dcMotor.get("motor_1"));

    myFollowPath.DirectionReset();
    myFollowPath.encoderReset();

      speedCmdZ1=0;
      pathIdx=0;

  }

  /*
   * This method will be called repeatedly in a loop
   * @see com.qualcomm.robotcore.eventloop.opmode.OpMode#loop()
   */
  @Override
  public void loop() {

      long  robotDist = motorRight.getCurrentPosition() + motorLeft.getCurrentPosition();
      long  robotDir  = motorLeft.getCurrentPosition() - motorRight.getCurrentPosition();
      long  distInches = robotDist/myFollowPath.IN2CLK;
      long  dirDegrees = robotDir/27;

      // Calculate the speed and direction commands
      long speedCmd = myFollowPath.ForwardDist(path[pathIdx][DIST_IDX], robotDist, path[pathIdx][SPD_IDX]);
      long dirCmd   = myFollowPath.Direction(path[pathIdx][DIR_IDX], robotDir);

      //calculate when to increment path
      if (Math.abs(path[pathIdx][DIR_IDX] - dirDegrees) < 10 && Math.abs(path[pathIdx][DIST_IDX] - distInches) < 9) pathIdx++;


        switch (state_mach)
        {


          case STATE_ZERO:

            break;

          case STATE_ONE:

            break;


          case STATE_THREE:

            break;


        }


      int s=(path.length/path[0].length)-1;
      if (pathIdx>s) pathIdx=s; // Protect the path index

      speedCmd = myLimit.RateLimit(speedCmd, myFollowPath.START_RATE,speedCmdZ1);

      leftSpeed = speedCmd + dirCmd;
      rightSpeed = speedCmd - dirCmd;

      rightSpeed = (long) Range.clip(rightSpeed, -1, 1);
      leftSpeed = (long) Range.clip(leftSpeed, -1, 1);

      motorRight.setPower(rightSpeed);
      motorLeft.setPower(leftSpeed);

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
