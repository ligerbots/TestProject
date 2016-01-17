#ifndef TurnCommand_H
#define TurnCommand_H

#include <WPILib.h>
#include "../CommandBase.h"

class TurnCommand: public CommandBase
{
public:
	TurnCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual void setTargetAngle(double angle);
	virtual double getTargetAngle();
protected:
	double targetAngle;
	double currentAngle;
	static double PROPORTIONAL_CONSTANT;
};

#endif
