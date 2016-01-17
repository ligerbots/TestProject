#include <WPILib.h>
#include "TurnCommand.h"
#include <math.h>
#include "RobotMap.h"
#include "Subsystems/Subsystems.h"
#include "Commands/DriveJoystickCommand.h"

double TurnCommand::PROPORTIONAL_CONSTANT = 0.1;

TurnCommand::TurnCommand() {
	printf("TurnCommand: constructor");
	Requires(Subsystems::pDriveSubsystem);
	Requires(Subsystems::pNavXSubsystem);
	targetAngle = 0;
	currentAngle = 0;
}

void TurnCommand::Initialize() {
	printf("TurnCommand::Initialize");
	// make sure it doesn't get stuck turning forever if something fails
	SetTimeout(2);
	currentAngle = RobotMap::pNavX->GetYaw() * M_PI / 180;
	// XXX: debug, turn 90 degrees
	targetAngle = currentAngle + M_PI;
}

void TurnCommand::Execute() {
	currentAngle = RobotMap::pNavX->GetYaw() * M_PI / 180;

	double normalizedCurrentAngle = fmod(currentAngle + 2 * M_PI, 2 * M_PI);
	double normalizedTargetAngle = fmod(currentAngle + 2 * M_PI, 2 * M_PI);
	// find shortest way to reach target angle
	double proportionalTurn;
	// XXX: may not be the correct turn direction; depends on hardware
	if (abs(normalizedTargetAngle - normalizedCurrentAngle)
			< fmin(normalizedCurrentAngle, normalizedTargetAngle) + 2 * M_PI
					- fmax(normalizedCurrentAngle, normalizedTargetAngle)) {
		// rotating without going through 360 degrees
		proportionalTurn = PROPORTIONAL_CONSTANT * (normalizedTargetAngle - normalizedCurrentAngle);
	} else {
		// rotating through 360 degrees
		proportionalTurn = PROPORTIONAL_CONSTANT * (normalizedCurrentAngle - normalizedTargetAngle);
	}

	proportionalTurn = DriveJoystickCommand::clampJoystickValue(proportionalTurn, -DriveJoystickCommand::TURN_MAX, DriveJoystickCommand::TURN_MAX);

	SmartDashboard::PutNumber("TurnCommand_currentAngle", currentAngle);
	SmartDashboard::PutNumber("TurnCommand_targetAngle", targetAngle);

	Subsystems::pDriveSubsystem->DriveJoystick(0,
				proportionalTurn);
}

bool TurnCommand::IsFinished() {
	if (IsTimedOut())
		return true;
	double normalizedCurrentAngle = fmod(currentAngle + 2 * M_PI, 2 * M_PI);
	double normalizedTargetAngle = fmod(currentAngle + 2 * M_PI, 2 * M_PI);
	// max drift is about 1 degree. If we are within 2 degrees, consider it good
	return abs(normalizedTargetAngle - normalizedCurrentAngle) < 2 * M_PI / 180;
}

void TurnCommand::End() {
	// reset drive to 0
	Subsystems::pDriveSubsystem->DriveJoystick(0, 0);
}

void TurnCommand::setTargetAngle(double angle) {
	targetAngle = angle;
}

double TurnCommand::getTargetAngle() {
	return targetAngle;
}

void TurnCommand::Interrupted() {
	printf("TurnCommand: interrupted!\n");
}
