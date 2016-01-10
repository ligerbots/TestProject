/*
 * RobotMap.cpp
 *
 *  Created on: Dec 25, 2015
 *      Author: Erik
 */

#include "RobotMap.h"
#include <stdexcept>
#include "Utils/WPILibException.h"

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
 * @throws WPILibException on a WPILib error; std::runtime_error on other problems
 */
CANTalon* RobotMap::createCANTalon(int canNumber) {
	CANTalon* pCanTalon = new CANTalon(canNumber);
	if(pCanTalon == NULL){
		throw std::runtime_error("Failed to initialize CANTalon (pointer is null)");
	} else {
		Error& error = pCanTalon->GetError();
		if(error.GetCode() != 0){
			throw WPILibException(&error);
		} else {
			return pCanTalon;
		}
	}
}

void RobotMap::init() {
	if (inited)
		return;
	try {
		// initialize all motor controllers
		pDriveLeft1 = createCANTalon(CAN_DRIVE_LEFT1);
		pDriveLeft2 = createCANTalon(CAN_DRIVE_LEFT2);
		pDriveRight1 = createCANTalon(CAN_DRIVE_RIGHT1);
		pDriveRight2 = createCANTalon(CAN_DRIVE_RIGHT2);

		// initialized the navX IMU
		pNavX = new AHRS(SPI::Port::kMXP);

		// no problems up to this point; mark that RobotMap is initialized
		inited = true;
		printf("RobotMap initialized");
	} catch (const std::exception &ex) {
		std::string err_string = "Error in RobotMap::init() ";
		err_string += ex.what();
		printf(err_string.c_str());
		DriverStation::ReportError(err_string);
	}

}
