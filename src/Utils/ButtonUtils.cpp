#include <TestProject.h>

bool ButtonUtils::joystick0Buttons[12] = {};

bool ButtonUtils::joystickButtonPressed(int btn) {
	bool dsPressed = Robot::instance->pOperatorInterface->pDriverStation->GetStickButton(0, btn);
	bool retval = false;
	if(!joystick0Buttons[btn - 1] && dsPressed){
		retval = true;
	}
	joystick0Buttons[btn - 1] = dsPressed;
	return retval;
}
