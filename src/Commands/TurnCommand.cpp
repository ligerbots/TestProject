#include "TurnCommand.h"
#include <math.h>
#include "RobotMap.h"
#include "Subsystems/Subsystems.h"
#include "Commands/DriveJoystickCommand.h"

TurnCommand::TurnCommand() {
	printf("TurnCommand: constructor");
	Requires(Subsystems::pDriveSubsystem);
	Requires(Subsystems::pNavXSubsystem);
	targetAngle = 0;
	currentAngle = 0;
	directionToTurn = false;
	// make sure it doesn't get stuck turning forever if something fails
	SetTimeout(2);
}

void TurnCommand::Initialize() {
	currentAngle = RobotMap::pNavX->GetYaw();
	// XXX: debug, turn 90 degrees
	targetAngle = currentAngle + M_PI;
	double normalizedCurrentAngle = fmod(currentAngle + 2 * M_PI, 2 * M_PI);
	double normalizedTargetAngle = fmod(currentAngle + 2 * M_PI, 2 * M_PI);
	// find shortest way to reach target angle
	// XXX: may not be the correct turn direction; depends on hardware
	if (abs(normalizedTargetAngle - normalizedCurrentAngle)
			< fmin(normalizedCurrentAngle, normalizedTargetAngle) + 2 * M_PI
					- fmax(normalizedCurrentAngle, normalizedTargetAngle)) {
		// rotating without going through 360 degrees
		directionToTurn = normalizedTargetAngle > normalizedCurrentAngle;
	} else {
		// rotating through 360 degrees
		directionToTurn = normalizedTargetAngle < normalizedCurrentAngle;
	}
}

void TurnCommand::Execute() {
	Subsystems::pDriveSubsystem->DriveJoystick(0,
			directionToTurn ?
					DriveJoystickCommand::TURN_MAX :
					-DriveJoystickCommand::TURN_MAX);
	currentAngle = RobotMap::pNavX->GetYaw();
}

bool TurnCommand::IsFinished() {
	double normalizedCurrentAngle = fmod(currentAngle + 2 * M_PI, 2 * M_PI);
	double normalizedTargetAngle = fmod(currentAngle + 2 * M_PI, 2 * M_PI);
	return abs(normalizedTargetAngle - normalizedCurrentAngle) < 0.01;
}

void TurnCommand::End() {

}

void TurnCommand::setTargetAngle(double angle) {
	targetAngle = angle;
}

double TurnCommand::getTargetAngle() {
	return targetAngle;
}

void TurnCommand::Interrupted() {
	printf("TurnCommand: interrupted");
}
