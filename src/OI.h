#ifndef OI_H
#define OI_H

#include <WPILib.h>

class OI {
public:
	typedef std::map<uintptr_t, std::vector<JoystickButton*>> JoystickMap_t;
	enum ButtonEvent {
		ACTIVE, INACTIVE, PRESSED, RELEASED
	};

	OI();
	OI(const OI& other);
	DriverStation* pDriverStation;
	LiveWindow* pLiveWindow;
	Joystick* pXboxController;
	Joystick* pLogitechJoystick;
	/**
	 * Registers commands to controller buttons
	 */
	void registerCommands();
protected:
	JoystickMap_t controllerButtons;
	void registerButton(Joystick* joystick, int buttonNumber,
			ButtonEvent when, Command* command);
};

#endif
