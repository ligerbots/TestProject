#include <TestProject.h>

double TurnCommand::PROPORTIONAL_CONSTANT = 0.5;

TurnCommand::TurnCommand(double targetDeltaAngle): proportionalConstant("TurnCommand_P") {
	printf("TurnCommand: constructor\n");
	Requires(Subsystems::pDriveSubsystem);
	Requires(Subsystems::pNavXSubsystem);
	this->targetDeltaAngle = targetDeltaAngle;
	startAngle = 0;
	currentAngle = 0;
}

void TurnCommand::Initialize() {
	printf("TurnCommand::Initialize\n");
	// make sure it doesn't get stuck turning forever if something fails
	SetTimeout(2);
	SetInterruptible(false);

	double currentYaw = Subsystems::pYawSensor->getYaw();
	if (currentYaw == YawSensor::YAW_INVALID) {
		printf("Warning: No way to find yaw; using dead reckoning\n");
		// todo: dead reckoning
		SetTimeout(fabs(targetDeltaAngle) / M_PI);
	} else {
		currentAngle = Subsystems::pYawSensor->getYaw() * M_PI / 180;
		startAngle = currentAngle;
	}
}

void TurnCommand::Execute() {
	printf("TurnCommand::execute\n");

	PROPORTIONAL_CONSTANT = proportionalConstant.get();

	double currentYaw = Subsystems::pYawSensor->getYaw();
	if (currentYaw == YawSensor::YAW_INVALID) {
		printf("Warning: No way to find yaw; using dead reckoning\n");
		Subsystems::pDriveSubsystem->DriveJoystick(0,
				targetDeltaAngle > 0 ?
						DriveJoystickCommand::TURN_MAX :
						-DriveJoystickCommand::TURN_MAX);
		return;
	}
	currentAngle = Subsystems::pYawSensor->getYaw() * M_PI / 180;
	printf("TurnCommand: current angle %f\n", currentAngle);

	double proportionalTurn = (fmod(startAngle + targetDeltaAngle + 4 * M_PI,
			2 * M_PI) - fmod(currentAngle + 4 * M_PI, 2 * M_PI))
			* PROPORTIONAL_CONSTANT;
	if (targetDeltaAngle > 0)
		proportionalTurn = fabs(proportionalTurn);
	else
		proportionalTurn = -fabs(proportionalTurn);

	proportionalTurn = DriveJoystickCommand::clampJoystickValue(
			proportionalTurn, -DriveJoystickCommand::TURN_MAX,
			DriveJoystickCommand::TURN_MAX);

	printf("TurnCommand: at %f / %f / turn is %f\n", fmod(currentAngle + 4 * M_PI, 2 * M_PI),
			fmod(startAngle + targetDeltaAngle + 4 * M_PI,
						2 * M_PI), proportionalTurn);

	Subsystems::pDriveSubsystem->DriveJoystick(0, proportionalTurn);
}

bool TurnCommand::IsFinished() {
	if (IsTimedOut()) {
		printf("TurnCommand: Timed Out\n");
		return true;
	}

	double a1 = fmod(startAngle + targetDeltaAngle + 4 * M_PI,
			2 * M_PI);
	double a2 = fmod(currentAngle + 4 * M_PI, 2 * M_PI);
	printf("TestCommand: %f / %f", a1, a2);

	return fabs(a1 - a2) < 5.0 * M_PI / 180.0;
}

void TurnCommand::End() {
	Subsystems::pDriveSubsystem->DriveJoystick(0, 0);
	CommandBase::pDriveJoystickCommand->Start();
}

void TurnCommand::setTargetAngle(double angle) {
	targetDeltaAngle = angle;
}

double TurnCommand::getTargetAngle() {
	return targetDeltaAngle;
}

void TurnCommand::Interrupted() {
	printf("TurnCommand: interrupted!\n");
	Subsystems::pDriveSubsystem->DriveJoystick(0, 0);
}
