#ifndef SRC_SUBSYSTEMS_DRIVESUBSYSTEM_H_
#define SRC_SUBSYSTEMS_DRIVESUBSYSTEM_H_

#include <WPILib.h>
#include "Commands/Subsystem.h"

class DriveSubsystem: public Subsystem
{
protected:
	RobotDrive* pRobotDrive;
public:
	DriveSubsystem();
	~DriveSubsystem();
	void InitDefaultCommand();
	void DriveJoystick(double y, double x);

	/**
	 * Checks if the motor is OK to use (not null, no error on it)
	 * @param motor The motor controller to check
	 * @return True if this motor can be used, false otherwise
	 */
	static bool motorIsOk(CANTalon* motor, bool checkForFaults);

	/**
	 * Checks if this motor has a valid encoder that can be used
	 * @param motor The motor controller to check an encoder on
	 * @return True if the encoder is returning a position, false if it cannot be used
	 */
	static bool encoderIsOk(CANTalon* motor);
};

#endif
