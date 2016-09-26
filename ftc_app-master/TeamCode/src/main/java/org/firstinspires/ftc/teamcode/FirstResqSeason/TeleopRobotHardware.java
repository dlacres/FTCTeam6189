package com.qualcomm.ftcrobotcontroller.opmodes.FirstResqSeason;

import com.qualcomm.ftccommon.DbgLog;
import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;
import com.qualcomm.robotcore.hardware.DcMotorController;
import com.qualcomm.robotcore.hardware.Servo;
import com.qualcomm.robotcore.hardware.ServoController;
import com.qualcomm.robotcore.hardware.UltrasonicSensor;
import com.qualcomm.robotcore.util.Range;

//------------------------------------------------------------------------------
//
// PushBotHardware
//

/**
 * Provides a single hardware access point between custom op-modes and the
 * OpMode class for the Push Bot.
 *
 * This class prevents the custom op-mode from throwing an exception at runtime.
 * If any hardware fails to map, a warning will be shown via telemetry data,
 * calls to methods will fail, but will not cause the application to crash.
 *
 * @author SSI Robotics
 * @version 2015-08-13-20-04
 */
public class TeleopRobotHardware extends OpMode

{
	//--------------------------------------------------------------------------
	//
	//
	//
	/**
	 * Construct the class.
	 * <p>
	 * The system calls this member when the class is instantiated.
	 */
	DcMotorController.DeviceMode devMode;
	DcMotorController DriveTrain;
	DcMotor MotorLeft;
	DcMotor MotorRight;
	DcMotorController TrackMovement;
	DcMotor LinearSlide;
	DcMotor TrackUpDown;
	DcMotorController WinchControl;
	DcMotor Winch;
	DcMotor LinearSlide2;


	Servo ArmFlipperRight;
	Servo ArmFlipperLeft;
	Servo PauletteFlipper;
	Servo RightPlow;
	Servo LeftPlow;
	com.qualcomm.robotcore.hardware.ServoController ServoController;

	UltrasonicSensor Sonar;
	int numOpLoops = 1;
	int Mode = 0;
	float LinearSlidePower = 0;
	float LinearSlidePower2 = 0;

	public TeleopRobotHardware()

	{
		//
		// Initialize base classes.
		//
		// All via self-construction.

		//
		// Initialize class members.
		//
		// All via self-construction.

	}

	//--------------------------------------------------------------------------
	//
	// init
	//

	/**
	 * Perform any actions that are necessary when the OpMode is enabled.
	 * <p>
	 * The system calls this member once when the OpMode is enabled.
	 */
	@Override
	public void init()

	{
		//
		MotorLeft = hardwareMap.dcMotor.get("MotorLeft");
		MotorRight = hardwareMap.dcMotor.get("MotorRight");
		TrackUpDown = hardwareMap.dcMotor.get("TrackUpDown");
		LinearSlide = hardwareMap.dcMotor.get("LinearSlide");
		Winch = hardwareMap.dcMotor.get("Winch");
		LinearSlide2 = hardwareMap.dcMotor.get("LinearSlide2");


		DriveTrain = hardwareMap.dcMotorController.get("DriveTrain");
		TrackMovement = hardwareMap.dcMotorController.get("TrackMovement");
		WinchControl = hardwareMap.dcMotorController.get("WinchControl");


		ServoController = hardwareMap.servoController.get("ServoController");

		ArmFlipperRight = hardwareMap.servo.get("ArmFlipperRight");
		ArmFlipperLeft = hardwareMap.servo.get("ArmFlipperLeft");
		PauletteFlipper = hardwareMap.servo.get("PauletteFlipper");
		RightPlow = hardwareMap.servo.get("RightPlow");
		LeftPlow = hardwareMap.servo.get("LeftPlow");

		Sonar = hardwareMap.ultrasonicSensor.get("Sonar");

		devMode = DcMotorController.DeviceMode.WRITE_ONLY;

		//motorRight.setDirection(DcMotor.Direction.REVERSE);
		//motorLeft.setDirection(DcMotor.Direction.REVERSE);

		// set the mode
		// Nxt devices start up in "write" mode by default, so no need to switch device modes here.

		TrackMovement.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);
		DriveTrain.setMotorControllerDeviceMode(DcMotorController.DeviceMode.WRITE_ONLY);


		PauletteFlipper.setPosition(0.9);
		ArmFlipperLeft.setPosition(1);
		ArmFlipperRight.setPosition(0.5);
		RightPlow.setPosition(0.1);
		LeftPlow.setPosition(0.9);

	}

	//--------------------------------------------------------------------------
	//
	// start
	//

	/**
	 * Perform any actions that are necessary when the OpMode is enabled.
	 * <p>
	 * The system calls this member once when the OpMode is enabled.
	 */
	@Override
	public void start()

	{
		//
		// Only actions that are common to all Op-Modes (i.e. both automatic and
		// manual) should be implemented here.
		//
		// This method is designed to be overridden.
		//

	} // start

	//--------------------------------------------------------------------------
	//
	// loop
	//

	/**
	 * Perform any actions that are necessary while the OpMode is running.
	 * <p>
	 * The system calls this member repeatedly while the OpMode is running.
	 */
	@Override
	public void loop()

	{
		//
		// Only actions that are common to all OpModes (i.e. both auto and\
		// manual) should be implemented here.
		//
		// This method is designed to be overridden.
		//

	} // loop

	//--------------------------------------------------------------------------
	//
	// stop
	//

	/**
	 * Perform any actions that are necessary when the OpMode is disabled.
	 * <p>
	 * The system calls this member once when the OpMode is disabled.
	 */
	@Override
	public void stop() {
		//
		// Nothing needs to be done for this method.
		//

	} // stop

}
