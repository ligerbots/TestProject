/*
 * YawSensor.h
 *
 *  Created on: Jan 21, 2016
 *      Author: Erik
 */

#ifndef SRC_SENSORS_YAWSENSOR_H_
#define SRC_SENSORS_YAWSENSOR_H_

/**
 * Uses both the NavX and wheel encoders to try to calculate yaw
 * Meant to avoid the robot crazily spinning if the IMU breaks
 * Prefers NavX
 */
class YawSensor {
public:
	static constexpr double YAW_INVALID = std::numeric_limits<double>::quiet_NaN();

	YawSensor();

	/**
	 * Tries to calculate yaw based on navx (if available) or encoders
	 * @return The yaw (in degrees) OR YAW_INVALID if there are no working feedback mechanisms
	 */
	double getYaw();

	double getLastGoodYaw() const;

	virtual ~YawSensor();

protected:
	bool haveNavX;
	bool haveEncoders;
	double lastYaw;
	double encoderOffsetYaw;
	double navXOffsetYaw;

	static double DEGREES_PER_TICK;
};

#endif /* SRC_SENSORS_YAWSENSOR_H_ */
