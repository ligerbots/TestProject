#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <string>
#include "WPILib.h"

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
	static Command *pTurnCommand;
	static void init();
};

#endif
