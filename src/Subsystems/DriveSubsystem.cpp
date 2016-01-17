#include <WPILib.h>
#include "DriveSubsystem.h"
#include "../RobotMap.h"

DriveSubsystem::DriveSubsystem() :
		Subsystem("DriveSubsystem") {
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

DriveSubsystem::~DriveSubsystem(){
	delete pRobotDrive;
}

void DriveSubsystem::InitDefaultCommand() {
	// we probably don't want this command running during auto
	// SetDefaultCommand(new DriveJoystickCommand());
}

void DriveSubsystem::DriveJoystick(double y, double x) {
	pRobotDrive->ArcadeDrive(y, x);
}
