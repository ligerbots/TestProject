#include "NavXSubsystem.h"
#include "../RobotMap.h"

NavXSubsystem::NavXSubsystem() :
		Subsystem("NavXSubsystem") {

}

void NavXSubsystem::InitDefaultCommand() {
}

void NavXSubsystem::ZeroYaw(){
	RobotMap::pNavX->ZeroYaw();
}
