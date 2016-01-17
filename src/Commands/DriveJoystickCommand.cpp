#include <WPILib.h>
#include "DriveJoystickCommand.h"
#include "Subsystems/Subsystems.h"

double DriveJoystickCommand::TURN_MAX = 0.7;
double DriveJoystickCommand::LINEAR_MAX = 0.6;

DriveJoystickCommand::DriveJoystickCommand() {
	printf("DriveJoystickCommand: constructor");
	Requires(Subsystems::pDriveSubsystem);
}

void DriveJoystickCommand::Initialize() {
	printf("DriveJoystickCommand: initialize");
	// DriveSubsystem should have set everything correctly
}

void DriveJoystickCommand::Execute() {
	Joystick* pXboxController =
			Robot::instance->pOperatorInterface->pXboxController;

	if(pXboxController == NULL){
		return;
	}

	double y = pXboxController->GetY();
	// there was a 0.7 turnMax variable in the 2015 bot
	y = clampJoystickValue(y, -TURN_MAX, TURN_MAX);
	double x = pXboxController->GetX();
	// roadkill safety
	x = clampJoystickValue(x, -LINEAR_MAX, LINEAR_MAX);

	SmartDashboard::PutNumber("DriveJoystick_x", x);
	SmartDashboard::PutNumber("DriveJoystick_y", y);

	Subsystems::pDriveSubsystem->DriveJoystick(y, x);
}

bool DriveJoystickCommand::IsFinished() {
	// we always want joystick control
	return false;
}

void DriveJoystickCommand::End() {
	printf("DriveJoystickCommand: end");
}

void DriveJoystickCommand::Interrupted() {
	printf("DriveJoystickCommand: interrupted");
}

double DriveJoystickCommand::clampJoystickValue(double value, double min,
		double max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}
