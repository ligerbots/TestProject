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
 * Throws a std::runtime_error if the specified pointer is null
 */
#define THROW_IF_NULL(pointer) if(pointer == NULL){\
		printf("Object " #pointer " is null!\n");\
		throw std::runtime_error("Pointer " #pointer " is null");\
	}

/**
 * This macro takes 2 code blocks, wraps the first in a try block and puts the second in the catch block.
 * The catch block automatically prints the error and reports it to DriverStation
 */
#define TRY_AND_REPORT_ERROR(code, catchCode) try { code; } catch (const std::exception &ex) {\
		std::string err_string = "Caught exception ";\
		err_string += ex.what();\
		err_string += "\n";\
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
	 * @param pWpiObject The WPILib Error object, from an ErrorBase
	 */
	explicit WPILibException(Error* pWpiError);
	explicit WPILibException(ErrorBase* pWpiObject);
	virtual ~WPILibException() throw ();

	/**
	 * Get an error message for this exception.
	 * Includes all the information the WPILib Error object has: message, file, line number, and function
	 * @return The information
	 */
	virtual const char* what() const throw ();

	/**
	 * Checks if the pointer is not null and there is no error
	 * @param pWpiObject The pointer to check
	 * @return True if you can use the object, false if not
	 */
	static bool isWPIObjectOK(ErrorBase* pWpiObject);

	/**
	 * This function throws an exception if there is currently an error in the specified WPILib object
	 * Warning: Calls ClearError() if there is an error
	 * @param pWpiObject The object to check
	 * @throws WPILibException
	 */
	static void throwIfError(ErrorBase* pWpiObject);

	/**
	 * Reports and clears the error on a WPI object if there is one.
	 * Warning: Calls ClearError() if there is an error
	 * @param pWpiObject The object to check
	 */
	static void reportIfError(ErrorBase* pWpiObject);
protected:
	std::string errorDescription;
};

#endif /* SRC_UTILS_WPILIBEXCEPTION_H_ */
