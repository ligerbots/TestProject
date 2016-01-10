#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "AHRS.h"

/**
 * Stores ID numbers for various hardware components, and the WPILib objects for the hardware as well
 */
class RobotMap {
public:
	static const int CAN_DRIVE_LEFT1 = 2;
	static const int CAN_DRIVE_LEFT2 = 3;
	static const int CAN_DRIVE_RIGHT1 = 4;
	static const int CAN_DRIVE_RIGHT2 = 5;

	static CANTalon* pDriveLeft1;
	static CANTalon* pDriveLeft2;
	static CANTalon* pDriveRight1;
	static CANTalon* pDriveRight2;
	static AHRS* pNavX;

	static void init();
private:
	static bool inited;
	static CANTalon* createCANTalon(int canNumber);
};

#endif /* ROBOTMAP_H */
