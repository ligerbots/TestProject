/*
 * WPILibException.h
 *
 *  Created on: Dec 25, 2015
 *      Author: Erik
 */

#ifndef SRC_UTILS_WPILIBEXCEPTION_H_
#define SRC_UTILS_WPILIBEXCEPTION_H_

#include <exception>
#include "WPILib.h"

/**
 * Wraps a WPILib Error object as a std::exception
 * Use with <code>throw WPILibException(ErrorBase->GetError())</code>
 */
class WPILibException: public std::exception {
public:

	/**
	 * Returns a description for the specified WPI Error
	 * @param pWpiError The Error
	 * @return A string description, identical to the
	 * 		result of what() if a new WPILibException was constructed from the Error
	 */
	static std::string describeError(Error* pWpiError);

	/**
	 * Create a new WPILibException with the specified Error
	 * @param wpiError_ The WPILib Error object, from an ErrorBase
	 */
	explicit WPILibException(Error* pWpiError_);
	virtual ~WPILibException() throw ();
	/**
	 * Get an error message for this exception.
	 * Includes all the info the WPILib Error object has: message, file, line number, and function
	 * @return The info
	 */
	virtual const char* what() const throw ();

	/**
	 * The WPILib error object wrapped by this exception
	 */
	Error* pWpiError;
protected:
	std::string errorDescription;
};

#endif /* SRC_UTILS_WPILIBEXCEPTION_H_ */
