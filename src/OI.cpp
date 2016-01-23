#include <TestProject.h>

OI::OI() :
		controllerButtons() {
	pDriverStation = &DriverStation::GetInstance();
	pLiveWindow = LiveWindow::GetInstance();
	pXboxController = new Joystick(0);
	pLogitechJoystick = new Joystick(1);
}

OI::OI(const OI& other) :
		controllerButtons(other.controllerButtons) {
	pDriverStation = &DriverStation::GetInstance();
	pLiveWindow = LiveWindow::GetInstance();
	pXboxController = new Joystick(0);
	pLogitechJoystick = new Joystick(1);
}

void OI::registerCommands() {
	registerButton(pXboxController, 2, PRESSED, CommandBase::pTurn90Command);
	// xxx: rename command to pLedToggleCommand
	registerButton(pXboxController, 4, PRESSED, CommandBase::pAutonomousCommand);
}

void OI::registerButton(Joystick* pJoystick, int buttonNumber, ButtonEvent when,
		Command* pCommand) {
	JoystickButton* button = NULL;

	// find the map to use
	JoystickMap_t::iterator cIt = controllerButtons.find((uintptr_t) pJoystick);
	if (cIt == controllerButtons.end()) {
		std::vector<JoystickButton*> apButtons(13);
		controllerButtons.insert(
				std::pair<uintptr_t, std::vector<JoystickButton*>>(
						(uintptr_t) pJoystick, apButtons));
	}

	cIt = controllerButtons.find((uintptr_t) pJoystick);

	// check if joystick is there
	if (cIt->second.at(buttonNumber) != NULL) {
		button = cIt->second.at(buttonNumber);
	} else {
		button = new JoystickButton(pJoystick, buttonNumber);
		cIt->second.at(buttonNumber) = button;
	}

	// attach the command to the correct event
	switch (when) {
	case ACTIVE:
		button->WhenActive(pCommand);
		break;
	case INACTIVE:
		button->WhenInactive(pCommand);
		break;
	case PRESSED:
		button->WhenPressed(pCommand);
		break;
	case RELEASED:
		button->WhenReleased(pCommand);
		break;
	}
}
