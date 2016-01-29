/*
 * ButtonUtils.h
 *
 *  Created on: Jan 28, 2016
 *      Author: Erik
 */

#ifndef SRC_UTILS_BUTTONUTILS_H_
#define SRC_UTILS_BUTTONUTILS_H_


class ButtonUtils {
public:
	static bool joystick0Buttons[12];

	static bool joystickButtonPressed(int btn);
};


#endif /* SRC_UTILS_BUTTONUTILS_H_ */
