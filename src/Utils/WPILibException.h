/*
 * WPILibException.h
 *
 *  Created on: Dec 25, 2015
 *      Author: Erik
 */

#ifndef SRC_UTILS_WPILIBEXCEPTION_H_
#define SRC_UTILS_WPILIBEXCEPTION_H_

#include <WPILib.h>
#include <exception>

/**
 * This macro throws an exception if there is currently an error in the specified WPILib object
 */
#define THROW_IF_ERROR(errorBase) Error& MACRO_THROW_IF_ERROR_Error = errorBase->GetError();\
	if(MACRO_THROW_IF_ERROR_Error.GetCode() != 0){\
		throw WPILibException(&MACRO_THROW_IF_ERROR_Error);\
	}
// Terrible name to avoid name conflicts

/**
 * This macro throws a std::runtime_exception if the parameter is null
 */
#define THROW_IF_NULL(pointer) if(pointer == NULL){\
		throw std::runtime_error("Failed to initialize object (pointer is null)");\
	}

/**
 * This macro takes 2 code blocks, wraps the first in a try block and puts the second in the catch block.
 * The catch block automatically prints the error and reports it to DriverStation
 */
#define TRY_AND_REPORT_ERROR(code, catchCode) try { code; } catch (const std::exception &ex) {\
		std::string err_string = "Caught exception ";\
		err_string += ex.what();\
		std::printf(err_string.c_str());\
		DriverStation::ReportError(err_string);\
		catchCode;\
	}

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
