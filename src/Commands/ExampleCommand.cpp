#include <TestProject.h>

ExampleCommand::ExampleCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void ExampleCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ExampleCommand::Execute() {
	printf("LedRingCommand::execute\n");
	if (WPILibException::isWPIObjectOK(RobotMap::pLedSpike)) {
		Relay::Value val = RobotMap::pLedSpike->Get();
		if (val == Relay::Value::kOff) {
			printf("LedRingCommand: turning led on\n");
			RobotMap::pLedSpike->Set(Relay::Value::kReverse);
		} else {
			printf("LedRingCommand: turning led off\n");
			RobotMap::pLedSpike->Set(Relay::Value::kOff);
		}
	} else {
		printf("LedRingCommand: spike not ok\n");
		WPILibException::reportIfError(RobotMap::pLedSpike);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ExampleCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ExampleCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExampleCommand::Interrupted() {

}
