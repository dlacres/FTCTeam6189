package org.firstinspires.ftc.teamcode.VelocityVortex;

import com.qualcomm.robotcore.hardware.ColorSensor;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.GyroSensor;
import com.qualcomm.robotcore.hardware.HardwareMap;
import com.qualcomm.robotcore.hardware.I2cAddr;
import com.qualcomm.robotcore.hardware.I2cDevice;
import com.qualcomm.robotcore.hardware.I2cDeviceSynch;
import com.qualcomm.robotcore.hardware.I2cDeviceSynchImpl;
import com.qualcomm.robotcore.hardware.LightSensor;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.hardware.TouchSensor;
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
    public DcMotor linearSlide = null;
    public DcMotor linearSlide2 = null;
    public DcMotor catapultMotor = null;


    public Servo buttonRight = null;
    public Servo buttonLeft = null;
    public Servo catapultReload = null;

    public ColorSensor colorSensor0 = null;
    public LightSensor colorSensor1 = null;
    public TouchSensor touchSensor = null;
    public ColorSensor colorSensor2 = null;
    public TouchSensor touchSensorM = null;
    public ColorSensor MRColorSensor = null;

   public float hsvValues[] = {0F,0F,0F};
    public float hsvValues2[] = {0F,0F,0F};

    // values is a reference to the hsvValues array.
   public final float values[] = hsvValues;


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
        linearSlide = hwMap.dcMotor.get("linearSlide");
        linearSlide2 = hwMap.dcMotor.get("linearSlide2");
        catapultMotor = hwMap.dcMotor.get("catapultMotor");


        leftMotor.setDirection(DcMotor.Direction.REVERSE); // Set to REVERSE if using AndyMark motors
        rightMotor.setDirection(DcMotor.Direction.FORWARD);// Set to FORWARD if using AndyMark motors

        // Set all motors to zero power
        //leftMotor.setPower(0);
        //rightMotor.setPower(0);

        catapultMotor.setMode(DcMotor.RunMode.STOP_AND_RESET_ENCODER);

        // Set all motors to run without encoders.
        // May want to use RUN_USING_ENCODERS if encoders are installed.
        leftMotor.setMode(DcMotor.RunMode.RUN_USING_ENCODER);
        rightMotor.setMode(DcMotor.RunMode.RUN_USING_ENCODER);
        catapultMotor.setMode(DcMotor.RunMode.RUN_USING_ENCODER);



        // Define and initialize ALL installed servos.
        buttonRight = hwMap.servo.get("buttonRight");
        buttonLeft = hwMap.servo.get("buttonLeft");
        catapultReload = hwMap.servo.get("catapultReload");

        buttonRight.setPosition(0.9);
        buttonLeft.setPosition(0.25);
        catapultReload.setPosition(1);

        colorSensor0 = hwMap.colorSensor.get("colorSensor0");
        colorSensor1 = hwMap.lightSensor.get("colorSensor1");
        colorSensor2 = hwMap.colorSensor.get("colorSensor2");
        MRColorSensor = hwMap.colorSensor.get("cc");



        colorSensor0.enableLed(false);
        colorSensor1.enableLed(true);
        colorSensor2.enableLed(false);
        MRColorSensor.enableLed(false);

        touchSensor =  hwMap.touchSensor.get("touchSensor");
        touchSensorM = hwMap.touchSensor.get("touchSensorM");


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

