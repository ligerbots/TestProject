#ifndef SRC_SUBSYSTEMS_DRIVESUBSYSTEM_H_
#define SRC_SUBSYSTEMS_DRIVESUBSYSTEM_H_

#include "Commands/Subsystem.h"
#include "WPILib.h"

class DriveSubsystem: public Subsystem
{
protected:
	RobotDrive* pRobotDrive;
public:
	DriveSubsystem();
	~DriveSubsystem();
	void InitDefaultCommand();
	void DriveJoystick(double y, double x);
};

#endif
