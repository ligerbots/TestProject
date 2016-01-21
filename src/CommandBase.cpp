#include <TestProject.h>

Command* CommandBase::pAutonomousCommand = NULL;
Command* CommandBase::pDriveJoystickCommand = NULL;
Command* CommandBase::pTurn90Command = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name) {
}

CommandBase::CommandBase() :
		Command() {

}

void CommandBase::init() {
	pAutonomousCommand = new ExampleCommand();
	pDriveJoystickCommand = new DriveJoystickCommand();
	pTurn90Command = new TurnCommand(M_PI / 2);
}
