#include <TestProject.h>

double DriveJoystickCommand::TURN_MAX = 0.7;
double DriveJoystickCommand::LINEAR_MAX = 0.6;

DriveJoystickCommand::DriveJoystickCommand() {
	printf("DriveJoystickCommand: constructor\n");
	Requires(Subsystems::pDriveSubsystem);
}

void DriveJoystickCommand::Initialize() {
	printf("DriveJoystickCommand: initialize\n");
	// DriveSubsystem should have set everything correctly
	SetInterruptible(true);
}

void DriveJoystickCommand::Execute() {
	Joystick* pXboxController =
			Robot::instance->pOperatorInterface->pXboxController;

	if(!WPILibException::isWPIObjectOK(pXboxController)){
		printf("Xbox controller not present!\n");
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
	printf("DriveJoystickCommand: interrupted\n");
	Subsystems::pDriveSubsystem->DriveJoystick(0, 0);
}

double DriveJoystickCommand::clampJoystickValue(double value, double min,
		double max) {
	if (value < min)
		value = min;
	if (value > max)
		value = max;
	return value;
}
