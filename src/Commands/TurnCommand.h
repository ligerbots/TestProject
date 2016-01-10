#ifndef TurnCommand_H
#define TurnCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

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
	bool directionToTurn;
};

#endif
