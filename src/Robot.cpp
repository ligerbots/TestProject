#include "Robot.h"
#include "WPILib.h"
#include "CommandBase.h"
#include "RobotMap.h"
#include "Subsystems/Subsystems.h"
#include "Utils/LigerbotsPreferences.h"

Robot* Robot::instance = NULL;

Robot::Robot() {
	if (Robot::instance != NULL) {
		printf("Warning: Robot instance already exists!");
	}

	testParameter = NULL;

	// specific order
	pOperatorInterface = new OI();
	RobotMap::init(); // initialize hardware interfaces
	Subsystems::init(); // initialize subsystems (depend on hardware)
	CommandBase::init(); // initialize commands (depend on subsystems, OI)
	pOperatorInterface->registerCommands(); // register commands to controller buttons

	Robot::instance = this;
	printf("Robot constructor completed");
}

Robot::~Robot() {
	delete pOperatorInterface;
}

void Robot::DisabledInit() {
	printf("Test robot disabled initialize");
}

void Robot::RobotInit() {
	if (RobotMap::pNavX) {
		pOperatorInterface->pLiveWindow->AddSensor("IMU", "Gyro",
				RobotMap::pNavX);
	}
	printf("Calling LigerbotsPreferences::GetInstance()");
	LigerbotsPreferences::GetInstance();
	printf("Creating testParameter");
	testParameter = LigerbotsPreferences::GetInstance()->createStringParameter(
			"TestParameter");
	printf("Setting test parameter");
	testParameter->set("Testing 123");
	printf("RobotInit complete");
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	// cancel the joystick drive command
	if (CommandBase::pDriveJoystickCommand != NULL)
		CommandBase::pDriveJoystickCommand->Cancel();

	// start the autonomous command
	if (CommandBase::pAutonomousCommand != NULL)
		CommandBase::pAutonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (CommandBase::pAutonomousCommand != NULL)
		CommandBase::pAutonomousCommand->Cancel();

	// reset the navX to compensate for drift
	RobotMap::pNavX->ZeroYaw();

	if (CommandBase::pDriveJoystickCommand != NULL)
		CommandBase::pDriveJoystickCommand->Start();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	if (!RobotMap::pNavX) {
		printf("navX not present");
		return;
	}

	// send value of test parameter
	SmartDashboard::PutString("TestParameter_Value", testParameter->get());

	bool reset_yaw_button_pressed =
			pOperatorInterface->pDriverStation->GetStickButton(0, 1);
	if (reset_yaw_button_pressed) {
		RobotMap::pNavX->ZeroYaw();
	}

	SmartDashboard::PutBoolean("IMU_Connected", RobotMap::pNavX->IsConnected());
	SmartDashboard::PutNumber("IMU_Yaw", RobotMap::pNavX->GetYaw());
	SmartDashboard::PutNumber("IMU_Pitch", RobotMap::pNavX->GetPitch());
	SmartDashboard::PutNumber("IMU_Roll", RobotMap::pNavX->GetRoll());
	SmartDashboard::PutNumber("IMU_CompassHeading",
			RobotMap::pNavX->GetCompassHeading());
	SmartDashboard::PutNumber("IMU_Update_Count",
			RobotMap::pNavX->GetUpdateCount());
	SmartDashboard::PutNumber("IMU_Byte_Count",
			RobotMap::pNavX->GetByteCount());

	/* These functions are compatible w/the WPI Gyro Class */
	SmartDashboard::PutNumber("IMU_TotalYaw", RobotMap::pNavX->GetAngle());
	SmartDashboard::PutNumber("IMU_YawRateDPS", RobotMap::pNavX->GetRate());

	SmartDashboard::PutNumber("IMU_Accel_X",
			RobotMap::pNavX->GetWorldLinearAccelX());
	SmartDashboard::PutNumber("IMU_Accel_Y",
			RobotMap::pNavX->GetWorldLinearAccelY());
	SmartDashboard::PutBoolean("IMU_IsMoving", RobotMap::pNavX->IsMoving());
	SmartDashboard::PutNumber("IMU_Temp_C", RobotMap::pNavX->GetTempC());
	SmartDashboard::PutBoolean("IMU_IsCalibrating",
			RobotMap::pNavX->IsCalibrating());

	SmartDashboard::PutNumber("Velocity_X", RobotMap::pNavX->GetVelocityX());
	SmartDashboard::PutNumber("Velocity_Y", RobotMap::pNavX->GetVelocityY());
	SmartDashboard::PutNumber("Displacement_X",
			RobotMap::pNavX->GetDisplacementX());
	SmartDashboard::PutNumber("Displacement_Y",
			RobotMap::pNavX->GetDisplacementY());

	/* Display Raw Gyro/Accelerometer/Magnetometer Values                       */
	/* NOTE:  These values are not normally necessary, but are made available   */
	/* for advanced users.  Before using this data, please consider whether     */
	/* the processed data (see above) will suit your needs.                     */

	SmartDashboard::PutNumber("RawGyro_X", RobotMap::pNavX->GetRawGyroX());
	SmartDashboard::PutNumber("RawGyro_Y", RobotMap::pNavX->GetRawGyroY());
	SmartDashboard::PutNumber("RawGyro_Z", RobotMap::pNavX->GetRawGyroZ());
	SmartDashboard::PutNumber("RawAccel_X", RobotMap::pNavX->GetRawAccelX());
	SmartDashboard::PutNumber("RawAccel_Y", RobotMap::pNavX->GetRawAccelY());
	SmartDashboard::PutNumber("RawAccel_Z", RobotMap::pNavX->GetRawAccelZ());
	SmartDashboard::PutNumber("RawMag_X", RobotMap::pNavX->GetRawMagX());
	SmartDashboard::PutNumber("RawMag_Y", RobotMap::pNavX->GetRawMagY());
	SmartDashboard::PutNumber("RawMag_Z", RobotMap::pNavX->GetRawMagZ());
	SmartDashboard::PutNumber("IMU_Temp_C", RobotMap::pNavX->GetTempC());
	/* Omnimount Yaw Axis Information                                           */
	/* For more info, see http://navx-mxp.kauailabs.com/installation/omnimount  */
	AHRS::BoardYawAxis yaw_axis = RobotMap::pNavX->GetBoardYawAxis();
	SmartDashboard::PutString("YawAxisDirection", yaw_axis.up ? "Up" : "Down");
	SmartDashboard::PutNumber("YawAxis", yaw_axis.board_axis);

	/* Sensor Board Information                                                 */
	SmartDashboard::PutString("FirmwareVersion",
			RobotMap::pNavX->GetFirmwareVersion());

	/* Quaternion Data                                                          */
	/* Quaternions are fascinating, and are the most compact representation of  */
	/* orientation data.  All of the Yaw, Pitch and Roll Values can be derived  */
	/* from the Quaternions.  If interested in motion processing, knowledge of  */
	/* Quaternions is highly recommended.                                       */
	SmartDashboard::PutNumber("QuaternionW", RobotMap::pNavX->GetQuaternionW());
	SmartDashboard::PutNumber("QuaternionX", RobotMap::pNavX->GetQuaternionX());
	SmartDashboard::PutNumber("QuaternionY", RobotMap::pNavX->GetQuaternionY());
	SmartDashboard::PutNumber("QuaternionZ", RobotMap::pNavX->GetQuaternionZ());
}

void Robot::TestPeriodic() {
	pOperatorInterface->pLiveWindow->Run();
}

START_ROBOT_CLASS(Robot);

