#include <TestProject.h>

WPILibException::WPILibException(Error* pWPIError_) :
		pWpiError(pWPIError_) {
	errorDescription = WPILibException::describeError(pWpiError);
}

WPILibException::~WPILibException() throw () {
}

/**
 * Utility function to return a description string from a WPILib error object
 * @param pWpiError A pointer to the WPILib error object
 * @return A string describing the WPILib error
 */
std::string WPILibException::describeError(Error* pWpiError) {
	std::string what = "WPI Exception: ";
	what += pWpiError->GetMessage();
	what += "\nFile: ";
	what += pWpiError->GetFilename();
	what += "\nLine: ";
	what += pWpiError->GetLineNumber();
	what += "\nFunction: ";
	what += pWpiError->GetFunction();
	return what;
}

/**
 * Describes this exception.
 * @return A char array describing this exception
 */
const char* WPILibException::what() const throw () {
	return errorDescription.c_str();
}
