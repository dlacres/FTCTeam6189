package org.firstinspires.ftc.teamcode.VelocityVortex;

import com.qualcomm.robotcore.hardware.ColorSensor;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorSimple;
import com.qualcomm.robotcore.hardware.HardwareMap;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.util.ElapsedTime;

/**

 *
 * Motor channel:  Left  drive motor:        "motorLeft"
 * Motor channel:  Right drive motor:        "motorRight"
 * Motor channel:   Sweeper motor: "sweeper"
 * Motor channel: linear slide motor: "linearSlide"
 *
 * servo channel: Right claw servo: "clawRight"
 * servo channel: Left claw servo: "clawLeft"
 */
public class HardwareCompetitionRobot
{
    /* Public OpMode members. */
    public DcMotor  leftMotor   = null;
    public DcMotor  rightMotor  = null;

    public DcMotor Sweeper = null;
    public DcMotor linearSlide = null;
    public DcMotor forkLift = null;


    public Servo buttonRight = null;
    public Servo buttonLeft = null;

    ColorSensor colorSensor;


    public static final double MID_SERVO       =  0.5 ;
    public static final double ARM_UP_POWER    =  0.45 ;
    public static final double ARM_DOWN_POWER  = -0.45 ;

    /* local OpMode members. */
    HardwareMap hwMap           =  null;
    private ElapsedTime period  = new ElapsedTime();

    /* Constructor */
    public HardwareCompetitionRobot(){

    }

    /* Initialize standard Hardware interfaces */
    public void init(HardwareMap ahwMap) {
        // Save reference to Hardware map
        hwMap = ahwMap;

        // Define and Initialize Motors
        leftMotor   = hwMap.dcMotor.get("motorLeft");
        rightMotor  = hwMap.dcMotor.get("motorRight");

        Sweeper = hwMap.dcMotor.get("sweeper");

        linearSlide = hwMap.dcMotor.get("linearSlide");
        forkLift = hwMap.dcMotor.get("forkLift");



        leftMotor.setDirection(DcMotor.Direction.REVERSE); // Set to REVERSE if using AndyMark motors
        rightMotor.setDirection(DcMotor.Direction.FORWARD);// Set to FORWARD if using AndyMark motors

        // Set all motors to zero power
        //leftMotor.setPower(0);
        //rightMotor.setPower(0);



        // Set all motors to run without encoders.
        // May want to use RUN_USING_ENCODERS if encoders are installed.
        leftMotor.setMode(DcMotor.RunMode.RUN_USING_ENCODER);
        rightMotor.setMode(DcMotor.RunMode.RUN_USING_ENCODER);


        // Define and initialize ALL installed servos.
        buttonRight = hwMap.servo.get("buttonRight");
        buttonLeft = hwMap.servo.get("buttonLeft");

        buttonRight.setPosition(0.25);
        buttonLeft.setPosition(1);

        boolean bLedOn = true;
        colorSensor = hwMap.colorSensor.get("colorSensor");

        colorSensor.enableLed(bLedOn);

    }

    /***
     *
     * waitForTick implements a periodic delay. However, this acts like a metronome with a regular
     * periodic tick.  This is used to compensate for varying processing times for each cycle.
     * The function looks at the elapsed cycle time, and sleeps for the remaining time interval.
     *
     * @param periodMs  Length of wait cycle in mSec.
     * @throws InterruptedException
     */
    public void waitForTick(long periodMs) throws InterruptedException {

        long  remaining = periodMs - (long)period.milliseconds();

        // sleep for the remaining portion of the regular cycle period.
        if (remaining > 0)
            Thread.sleep(remaining);

        // Reset the cycle clock for the next pass.
        period.reset();
    }
}

