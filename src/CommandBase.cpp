#include "CommandBase.h"
#include "Commands/ExampleCommand.h"
#include "Commands/DriveJoystickCommand.h"
#include "Commands/TurnCommand.h"

Command* CommandBase::pAutonomousCommand = NULL;
Command* CommandBase::pDriveJoystickCommand = NULL;
Command* CommandBase::pTurnCommand = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
	pAutonomousCommand = new ExampleCommand();
	pDriveJoystickCommand = new DriveJoystickCommand();
	pTurnCommand = new TurnCommand();
}
