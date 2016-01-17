#ifndef SRC_UTILS_NTPARAMETER_H_
#define SRC_UTILS_NTPARAMETER_H_

#include <WPILib.h>
#include "IParameter.h"
#include "NTUpdater.h"


template<typename Parameter_Type> class Parameter: public IParameter {
protected:
	std::string key;
	Parameter_Type value;
public:
	explicit Parameter(std::string key) :
			key(key) {
		NTUpdater::registerNTUpdater();
		NTUpdater::addParameter(key, this);
		updateValue();
	}

	virtual ~Parameter(){
		NTUpdater::removeParameter(key, this);
	}

	void set(Parameter_Type val);
	void updateValue();
};

template<> void Parameter<int>::set(int val) {
	value = val;
	NTUpdater::NETWORK_TABLE->PutNumber(key, value);
}

template<> void Parameter<double>::set(double val) {
	value = val;
	NTUpdater::NETWORK_TABLE->PutNumber(key, value);
}

template<> void Parameter<bool>::set(bool val) {
	value = val;
	NTUpdater::NETWORK_TABLE->PutBoolean(key, value);
}

template<> void Parameter<std::string>::set(std::string val) {
	value = val;
	NTUpdater::NETWORK_TABLE->PutString(key, value);
}

template<> void Parameter<int>::updateValue() {
	value = NTUpdater::NETWORK_TABLE->GetNumber(key, value);
}

template<> void Parameter<double>::updateValue() {
	value = NTUpdater::NETWORK_TABLE->GetNumber(key, value);
}

template<> void Parameter<bool>::updateValue() {
	value = NTUpdater::NETWORK_TABLE->GetBoolean(key, value);
}

template<> void Parameter<std::string>::updateValue() {
	value = NTUpdater::NETWORK_TABLE->GetString(key, value);
}
#endif /* SRC_UTILS_NTPARAMETER_H_ */
