#ifndef OI_H
#define OI_H

#include "WPILib.h"

// cppcheck-suppress noCopyConstructor
class OI {
public:
	enum ButtonEvent {
		ACTIVE, INACTIVE, PRESSED, RELEASED
	};

	OI();
	DriverStation* pDriverStation;
	LiveWindow* pLiveWindow;
	Joystick* pXboxController;
	Joystick* pLogitechJoystick;
	/**
	 * Registers commands to controller buttons
	 */
	void registerCommands();
protected:
	std::map<int, JoystickButton*> xboxButtons;
	void registerButton(Joystick* joystick,
			std::map<int, JoystickButton*>* buttonsMap, int buttonNumber,
			ButtonEvent when, Command* command);
};

#endif
