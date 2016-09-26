package com.qualcomm.ftcrobotcontroller.reusableClasses;


import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;

/**
 * Created by Andrew on 4/16/2016.
 */



public class followPath
{
    limit myLimit;


     DcMotor leftmotor;
     DcMotor rightmotor;



    public int IN2CLK = 200;
    public int STOP_RATE = 30; // Smaller numbers stop faster
    public int START_RATE = 5; // Larger numbers start faster
    int DEG2CLK = 29;
    int DIR_KP = 20; // Start tuning by setting this to around 25. Bigger numbers are a smaller gain
    int DIR_RL = 100;

    int directionRl=0;
    int forwardDistZ1=0; // This is a global variable used to maintain state history.

    public followPath (DcMotor right, DcMotor left)
    {
        rightmotor = right;
        leftmotor = left;
    }

    public void encoderReset()
    {
        forwardDistZ1=0;
        rightmotor.setMode(DcMotorController.RunMode.RESET_ENCODERS);
        leftmotor.setMode(DcMotorController.RunMode.RESET_ENCODERS);
    }

    public void DirectionReset(){
        directionRl=0;
    }

    public long ForwardDist(long distCmdInch, long distClicks, long speedCmd)
    {
        myLimit = new limit();
        long mtrSpdCmd,moveDistLeft,moveDistSpdCmd;

        moveDistLeft = (distCmdInch*IN2CLK - distClicks)/STOP_RATE;
        moveDistSpdCmd = myLimit.LimitSym(moveDistLeft, speedCmd); // Limit to the max speed desired
        mtrSpdCmd = myLimit.RateLimit(moveDistSpdCmd, START_RATE, forwardDistZ1); // This is used to ramp the command up slowly. The command will change 1*1000/TASKTIME_MS each second.

        return(mtrSpdCmd);
    }

    public long Direction(long dirCmd, long dir)
    {
        int dirMotorCmd;

        dirCmd=myLimit.RateLimit(dirCmd*DEG2CLK,DIR_RL,directionRl);
        dirMotorCmd = (int) (dirCmd-dir)/DIR_KP;

        return(dirMotorCmd);
    }


}
