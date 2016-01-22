#include <TestProject.h>

DriveSubsystem::DriveSubsystem() :
		Subsystem("DriveSubsystem") {
	// XXX: check if all motors are OK before initing
	// set 1st motors to percentVbus mode
	RobotMap::pDriveLeft1->SetControlMode(CANSpeedController::kPercentVbus);
	RobotMap::pDriveRight1->SetControlMode(CANSpeedController::kPercentVbus);

	// set 2nd motors to follow
	RobotMap::pDriveLeft2->SetControlMode(CANSpeedController::kFollower);
	RobotMap::pDriveLeft2->Set(RobotMap::CAN_DRIVE_LEFT1);
	RobotMap::pDriveLeft2->EnableControl();

	RobotMap::pDriveRight2->SetControlMode(CANSpeedController::kFollower);
	RobotMap::pDriveRight2->Set(RobotMap::CAN_DRIVE_RIGHT1);
	RobotMap::pDriveRight2->EnableControl();

	// XXX: set ramp rate?

	// set up robot drive class that handles setting values for motor controllers
	pRobotDrive = new RobotDrive(RobotMap::pDriveLeft1, RobotMap::pDriveRight1);
	pRobotDrive->SetSafetyEnabled(false);
	pRobotDrive->SetExpiration(0.1);
	pRobotDrive->SetSensitivity(0.5);
	pRobotDrive->SetMaxOutput(1);
}

DriveSubsystem::~DriveSubsystem() {
	delete pRobotDrive;
}

void DriveSubsystem::InitDefaultCommand() {
	// we probably don't want this command running during auto
	// SetDefaultCommand(new DriveJoystickCommand());
}

void DriveSubsystem::DriveJoystick(double y, double x) {
	pRobotDrive->ArcadeDrive(y, x);
}

bool DriveSubsystem::motorIsOk(CANTalon* motor, bool checkForFaults) {
	bool valid = WPILibException::isWPIObjectOK(motor);
	if (!valid)
		return false;

	if (!checkForFaults)
		return true;

	uint16_t faults = motor->GetFaults();
	return faults == 0;
}

bool DriveSubsystem::encoderIsOk(CANTalon* motor) {
	bool valid = WPILibException::isWPIObjectOK(motor);
	if (!valid)
		return false;

	// clear any previous errors so we can test
	WPILibException::reportIfError(motor);

	motor->GetPosition();
	if (motor->GetError().GetCode() == 0)
		return true;
	else {
		motor->ClearError();
		return false;
	}
}
