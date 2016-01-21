#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <WPILib.h>

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 */
class CommandBase: public Command
{
public:
	explicit CommandBase(char const *name);
	CommandBase();

	static Command *pAutonomousCommand;
	static Command *pDriveJoystickCommand;
	static Command *pTurn90Command;
	static void init();
};

#endif
