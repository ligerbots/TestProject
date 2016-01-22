#ifndef TurnCommand_H
#define TurnCommand_H

#include <WPILib.h>
#include "../CommandBase.h"

class TurnCommand: public CommandBase
{
public:
	explicit TurnCommand(double targetDeltaAngle);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual void setTargetAngle(double angle);
	virtual double getTargetAngle();
protected:
	double targetDeltaAngle;
	double startAngle;
	double currentAngle;
	static /*Parameter<*/double/*>*/ PROPORTIONAL_CONSTANT;
};

#endif
