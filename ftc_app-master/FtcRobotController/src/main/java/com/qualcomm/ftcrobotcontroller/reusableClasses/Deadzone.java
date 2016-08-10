package com.qualcomm.ftcrobotcontroller.reusableClasses;

/**
 * Created by Andrew on 4/16/2016.
 */
public class Deadzone {

   public int  DeadZone(int in, int size){
        int out;

        out=in;
        if ((in<size && in>-size)) out=0;

        return(out);
    }
}
