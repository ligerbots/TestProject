#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include <WPILib.h>
#include "AHRS.h"

#define INITIALIZE_IF_NULL(x, y) if(x == NULL){\
		printf("Initializing " #x "\n");\
		x = y;\
	} else { printf(#x " is not null, skipping\n"); }

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
	static bool isInited();
private:
	static bool inited;
	static CANTalon* createCANTalon(int canNumber);
};

#endif /* ROBOTMAP_H */
