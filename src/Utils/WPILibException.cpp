#include <TestProject.h>

WPILibException::WPILibException(Error* pWpiError) :
		errorDescription(WPILibException::describeError(pWpiError)) {
}

WPILibException::WPILibException(ErrorBase* pWpiObject) :
		errorDescription(WPILibException::describeError(&(pWpiObject->GetError()))) {
}

WPILibException::~WPILibException() throw () {
}

bool WPILibException::isWPIObjectOK(ErrorBase* pWpiObject) {
	return pWpiObject != NULL && pWpiObject->GetError().GetCode() == 0;
}

void WPILibException::throwIfError(ErrorBase* pWpiObject) {
	if (pWpiObject != NULL) {
		Error& potentialError = pWpiObject->GetError();
		if (potentialError.GetCode() != 0) {
			throw WPILibException(pWpiObject);
		}
	}
}

void WPILibException::reportIfError(ErrorBase* pWpiObject) {
	if (pWpiObject != NULL) {
		Error& potentialError = pWpiObject->GetError();
		if (potentialError.GetCode() != 0) {
			std::string err_string = describeError(&potentialError);
			err_string += "\n";
			std::printf(err_string.c_str());
			DriverStation::ReportError(err_string);
			pWpiObject->ClearError();
		}
	}
}

std::string WPILibException::describeError(Error* pWpiError) {
	std::string what = "WPI Exception: ";
	what += pWpiError->GetMessage();
	what += "\nFile: ";
	what += pWpiError->GetFilename();
	what += "\nLine: ";
	what += pWpiError->GetLineNumber();
	what += "\nFunction: ";
	what += pWpiError->GetFunction();
	what += "\nTimestamp: ";
	what += pWpiError->GetTimestamp();
	what += "\nCode: ";
	what += pWpiError->GetCode();
	return what;
}

const char* WPILibException::what() const throw () {
	return errorDescription.c_str();
}
