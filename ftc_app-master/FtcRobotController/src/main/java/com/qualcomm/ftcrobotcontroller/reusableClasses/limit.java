package com.qualcomm.ftcrobotcontroller.reusableClasses;

/**
 * Created by Andrew on 4/16/2016.
 */
public class limit
{

    public int LimitSym(long in, long max){

        if (in>max) return((int) max);
        if (in<-max) return((int) -max);
        return((int) in);
    }
    public int Limit(int in, int max, int min){

        if (in>max) return(max);
        if (in<min) return(min);
        return(in);
    }

    public int RateLimit(long in, int rate, int z1)
    {
        if (in-z1 >= rate) z1 = z1 + rate;
        else if (z1-in >= rate) z1 = z1 - rate;
        else z1=(int) in;
        return(z1);
    }

}
