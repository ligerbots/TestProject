#include <TestProject.h>

DriveSubsystem* Subsystems::pDriveSubsystem = NULL;
NavXSubsystem* Subsystems::pNavXSubsystem = NULL;

void Subsystems::init(){
	pDriveSubsystem = new DriveSubsystem();
	pNavXSubsystem = new NavXSubsystem();
}
