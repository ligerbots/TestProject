/*
 * Subsystems.h
 *
 *  Created on: Jan 3, 2016
 *      Author: Erik
 */

#ifndef SRC_SUBSYSTEMS_SUBSYSTEMS_H_
#define SRC_SUBSYSTEMS_SUBSYSTEMS_H_
#include "DriveSubsystem.h"
#include "NavXSubsystem.h"

/**
 * This class holds and manages all the robot subsystems
 */
class Subsystems {
public:
	static DriveSubsystem* pDriveSubsystem;
	static NavXSubsystem* pNavXSubsystem;

	// sensors
	static YawSensor* pYawSensor;
	/**
	 * Initializes all subsystems for the robot. Called in Robot constructor
	 */
	static void init();
};

#endif /* SRC_SUBSYSTEMS_SUBSYSTEMS_H_ */
