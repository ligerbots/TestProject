#include <TestProject.h>

bool RobotMap::inited = false;
CANTalon* RobotMap::pDriveLeft1 = NULL;
CANTalon* RobotMap::pDriveLeft2 = NULL;
CANTalon* RobotMap::pDriveRight1 = NULL;
CANTalon* RobotMap::pDriveRight2 = NULL;
AHRS* RobotMap::pNavX = NULL;

/**
 * Creates a new CANTalon or throws an exception on failure
 * @param canNumber The CAN ID of the CANTalon
 * @return The CANTalon if successful
 * @throws WPILibException on a WPILib error; std::runtime_error if CANTalon didn't construct
 */
CANTalon* RobotMap::createCANTalon(int canNumber) {
	CANTalon* pCanTalon = new CANTalon(canNumber);

	THROW_IF_NULL(pCanTalon);
	WPILibException::throwIfError(pCanTalon);

	return pCanTalon;
}

bool RobotMap::isInited() {
	return inited;
}

void RobotMap::init() {
	if (inited)
		return;

	printf("RobotMap::init\r\n");

	bool errors = false;

	// initialize all motor controllers
	TRY_AND_REPORT_ERROR(
			INITIALIZE_IF_NULL(pDriveLeft1, createCANTalon(CAN_DRIVE_LEFT1)),
			errors = true);
	TRY_AND_REPORT_ERROR(
			INITIALIZE_IF_NULL(pDriveLeft2, createCANTalon(CAN_DRIVE_LEFT2)),
			errors = true);
	TRY_AND_REPORT_ERROR(
			INITIALIZE_IF_NULL(pDriveRight1, createCANTalon(CAN_DRIVE_RIGHT1)),
			errors = true);
	TRY_AND_REPORT_ERROR(
			INITIALIZE_IF_NULL(pDriveRight2, createCANTalon(CAN_DRIVE_RIGHT2)),
			errors = true);

	// initialize the navX IMU
	TRY_AND_REPORT_ERROR(
			{ INITIALIZE_IF_NULL(pNavX, new AHRS(SPI::Port::kMXP)); THROW_IF_NULL(pNavX); },
			errors = true);

	if (errors) {
		printf("Problems initializing RobotMap\n");
	} else {
		// no problems up to this point; mark that RobotMap is initialized
		inited = true;
		printf("RobotMap initialized\n");
	}
}
