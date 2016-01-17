/*
 * Subsystems.cpp
 *
 *  Created on: Jan 3, 2016
 *      Author: Erik
 */

#include <WPILib.h>
#include <Subsystems/Subsystems.h>

DriveSubsystem* Subsystems::pDriveSubsystem = NULL;
NavXSubsystem* Subsystems::pNavXSubsystem = NULL;

void Subsystems::init(){
	pDriveSubsystem = new DriveSubsystem();
	pNavXSubsystem = new NavXSubsystem();
}
