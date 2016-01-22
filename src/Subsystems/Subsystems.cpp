#include <TestProject.h>

DriveSubsystem* Subsystems::pDriveSubsystem = NULL;
NavXSubsystem* Subsystems::pNavXSubsystem = NULL;

YawSensor* Subsystems::pYawSensor = NULL;

void Subsystems::init(){
	pDriveSubsystem = new DriveSubsystem();
	pNavXSubsystem = new NavXSubsystem();

	pYawSensor = new YawSensor();
}
