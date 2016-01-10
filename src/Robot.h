/*
 * Robot.h
 *
 *  Created on: Dec 26, 2015
 *      Author: Erik
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include "WPILib.h"
#include "OI.h"
#include "Utils/Parameter.h"

class Robot: public IterativeRobot {
public:
	OI* pOperatorInterface;
	Parameter<std::string>* testParameter;
	static Robot* instance;

	Robot();
	virtual ~Robot();

	void DisabledInit();
	void RobotInit();
	void DisabledPeriodic();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void TestPeriodic();
};

#endif /* SRC_ROBOT_H_ */
