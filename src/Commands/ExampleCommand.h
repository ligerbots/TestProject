#ifndef EXAMPLE_COMMAND_H
#define EXAMPLE_COMMAND_H

#include <WPILib.h>
#include "../CommandBase.h"

class ExampleCommand: public CommandBase
{
public:
	ExampleCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
