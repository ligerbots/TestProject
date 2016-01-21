#include <TestProject.h>

OI::OI() : xboxButtons() {
	pDriverStation = &DriverStation::GetInstance();
	pLiveWindow = LiveWindow::GetInstance();
	pXboxController = new Joystick(0);
	pLogitechJoystick = new Joystick(1);
}

OI::OI(const OI& other) : xboxButtons(other.xboxButtons) {
	pDriverStation = &DriverStation::GetInstance();
	pLiveWindow = LiveWindow::GetInstance();
	pXboxController = new Joystick(0);
	pLogitechJoystick = new Joystick(1);
}

void OI::registerCommands() {
	registerButton(pXboxController, &xboxButtons, 2, PRESSED,
			CommandBase::pTurnCommand);
}

void OI::registerButton(Joystick* joystick,
		std::map<int, JoystickButton*>* buttonsMap, int buttonNumber,
		ButtonEvent when, Command* command) {
	JoystickButton* button = NULL;
	// check if button is already there
	std::map<int, JoystickButton*>::iterator it = buttonsMap->find(
			buttonNumber);
	if (it != buttonsMap->end()) {
		button = it->second;
	} else {
		button = new JoystickButton(joystick, buttonNumber);
		buttonsMap->insert(std::make_pair(buttonNumber, button));
	}

	// attach the command to the correct event
	switch (when) {
	case ACTIVE:
		button->WhenActive(command);
		break;
	case INACTIVE:
		button->WhenInactive(command);
		break;
	case PRESSED:
		button->WhenPressed(command);
		break;
	case RELEASED:
		button->WhenReleased(command);
		break;
	}
}
