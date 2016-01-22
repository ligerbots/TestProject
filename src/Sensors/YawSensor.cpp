#include <TestProject.h>

// robotWidth = !testBot ? 24.5 : 26.5
// ninetyDegreeTurn = (3.14159 * robotWidth) / 4.0
// m_left = ninetyDegreeTurn
// position = Encoder->GetPosition() * inchesPerTick
// ticksPerRotation = (!testBot ? 7680 : 1000);
// wheelDiameter = (!testBot ? 6.25 : 4.3);
// inchesPerRotation = wheelDiameter * 3.14159;
// ticksPerInch = ticksPerRotation/inchesPerRotation;
// inchesPerTick = 1.0/ticksPerInch;

// ninetyDegreeTurn = 26.5 * M_PI / 4.0
// position90 = EncoderPosition * (4.3 * M_PI/1000))

// 1degree = 4.3 * 4 / 1000 / 26.5

// (wheel_diameter) * 4 / ticks_per_rotation / robot_width
double YawSensor::DEGREES_PER_TICK = 4.3 * 4.0 / (1000.0 * 26.5);

YawSensor::YawSensor() {
	haveNavX = false;
	haveEncoders = false;
	lastYaw = 0;
	encoderOffsetYaw = 0;
	navXOffsetYaw = 0;
}

YawSensor::~YawSensor() {
}

double YawSensor::getYaw(){
	if(RobotMap::pNavX && RobotMap::pNavX->IsConnected() && !RobotMap::pNavX->IsCalibrating()){
		if(!haveNavX){
			haveNavX = true;
			navXOffsetYaw = RobotMap::pNavX->GetYaw() - lastYaw;
		}

		lastYaw = RobotMap::pNavX->GetYaw() - navXOffsetYaw;
		return lastYaw;
	} else {
		haveNavX = false;

		bool encoderLeft1 = DriveSubsystem::encoderIsOk(RobotMap::pDriveLeft1);
		bool encoderLeft2 = DriveSubsystem::encoderIsOk(RobotMap::pDriveLeft2);
		bool encoderRight1 = DriveSubsystem::encoderIsOk(RobotMap::pDriveRight1);
		bool encoderRight2 = DriveSubsystem::encoderIsOk(RobotMap::pDriveRight2);

		// we need 1 encoder on each side
		if((encoderLeft1 || encoderLeft2) && (encoderRight1 || encoderRight2)){
			CANTalon* left = encoderLeft1 ? RobotMap::pDriveLeft1 : RobotMap::pDriveLeft2;
			CANTalon* right = encoderRight1 ? RobotMap::pDriveRight1 : RobotMap::pDriveRight2;

			double offset = left->GetPosition() - right->GetPosition();
			double angle = offset * DEGREES_PER_TICK;

			if(!haveEncoders){
				haveEncoders = true;
				encoderOffsetYaw = angle - lastYaw;
			}
			lastYaw = angle - encoderOffsetYaw;
			return lastYaw;
		} else {
			haveEncoders = false;
		}
	}

	return YAW_INVALID;
}

double YawSensor::getLastGoodYaw() const {
	return lastYaw;
}
