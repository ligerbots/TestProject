#ifndef NavXSubsystem_H
#define NavXSubsystem_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "RobotMap.h"

/**
 * Mainly a class for commands to detect if they might have conflicting ZeroYaw()s
 */
class NavXSubsystem: public Subsystem
{
public:
	NavXSubsystem();
	void InitDefaultCommand();
	void ZeroYaw();
};

#endif
