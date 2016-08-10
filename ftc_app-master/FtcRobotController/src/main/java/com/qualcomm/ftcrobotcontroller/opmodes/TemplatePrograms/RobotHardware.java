package com.qualcomm.ftcrobotcontroller.opmodes.TemplatePrograms;

import com.qualcomm.ftcrobotcontroller.reusableClasses.Deadzone;
import com.qualcomm.ftcrobotcontroller.reusableClasses.RobotDrive;
import com.qualcomm.ftcrobotcontroller.reusableClasses.followPath;
import com.qualcomm.ftcrobotcontroller.reusableClasses.limit;
import com.qualcomm.ftcrobotcontroller.reusableClasses.scaleInput;
import com.qualcomm.robotcore.eventloop.opmode.OpMode;
import com.qualcomm.robotcore.hardware.DcMotor;

//------------------------------------------------------------------------------
//
//

/**
 *
 * @author SSI Robotics
 * @version 2015-08-13-20-04
 */

//This file is where all the robot hardware initizlation will be.
public class RobotHardware extends OpMode

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
	Deadzone myDeadzone;
	RobotDrive myRobotDrive;
	scaleInput myScaleInput;
    limit myLimit;

	DcMotor motorRight;
	DcMotor motorLeft;

	public RobotHardware()

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
		motorRight = hardwareMap.dcMotor.get("motor_2");
		motorLeft = hardwareMap.dcMotor.get("motor_1");

		myDeadzone= new Deadzone();
		myRobotDrive = new RobotDrive(hardwareMap.dcMotor.get("motor_2"),hardwareMap.dcMotor.get("motor_1"));
		myScaleInput = new scaleInput();
        myLimit = new limit();


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
