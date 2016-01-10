/*
 * Parameter.h
 *
 *  Created on: Dec 18, 2015
 *      Author: Erik
 */

#ifndef SRC_UTILS_PARAMETER_H_
#define SRC_UTILS_PARAMETER_H_

#include <stdexcept>
#include <Utils/LigerbotsPreferences.h>
#include <Utils/IParameter.h>
#include <cstring>
#include "Debug.h"

/**
 * Template class for an element of LigerbotPreferences.
 * Use LigerbotPreferences->createParameter() to create one
 */
template<typename Parameter_Type> class Parameter: public IParameter {
protected:
	char* key;
	Parameter_Type value;
	Preferences* pParent;
public:
	/**
	 * Should not be called from anywhere other than LigerbotsPreferences
	 * @param key The name of this parameter
	 * @param parent The LigerbotsPreferences calling this
	 */
	Parameter(std::string key, Preferences* parent) {
		// key came from caller stack, so we need a copy
		this->key = new char[sizeof(key.c_str())];
		std::strcpy(this->key, key.c_str());
		this->pParent = parent;
	}
	virtual ~Parameter() {
		delete[] key;
	}

	/**
	 * Retrieves the cached value of the parameter
	 * @return The value
	 */
	Parameter_Type get() const {
		return value;
	}
	/**
	 * Sets a new value for this parameter and notifies Preferences to save/transmit the value
	 * @param newValue The new value
	 */
	virtual void set(Parameter_Type newValue) {
		// this really shouldn't happen
		printf("Parameter: Default set(Parameter_Type) called");
		assert(false);
	}

	/**
	 * Retrieves the value from Preferences
	 * Called on ITableListener updates
	 */
	virtual void notifyUpdatedValue() {
		// this really shouldn't happen either
		printf("Parameter: Default notifyUpdatedValue() called");
		assert(false);
	}
};

// specialized classes to handle each type we want
// they implement the methods that get and set the value with NetworkTables

class StringParameter: public Parameter<std::string> {
public:
	StringParameter(std::string key, Preferences* parent) :
			Parameter<std::string>(key, parent) {
		// load in initial values
		notifyUpdatedValue();
	}
	void notifyUpdatedValue() {
		// XXX: debug code; remove
		printf("StringParameter notifyUpdatedValue() called");
		this->value = this->pParent->GetString(key);
	}
	void set(std::string value) {
		// XXX: debug code; remove
		printf("StringParameter set(std::string) called");
		this->value = value;
		this->pParent->PutString(key, value.c_str());
	}
};

class IntParameter: public Parameter<int> {
public:
	IntParameter(std::string key, Preferences* parent) :
			Parameter<int>(key, parent) {
		// load in initial values
		notifyUpdatedValue();
	}
	void notifyUpdatedValue() {
		this->value = this->pParent->GetInt(key);
	}
	void set(int value) {
		this->value = value;
		this->pParent->PutInt(key, value);
	}
};

class DoubleParameter: public Parameter<double> {
public:
	DoubleParameter(std::string key, Preferences* parent) :
			Parameter<double>(key, parent) {
		// load in initial values
		notifyUpdatedValue();
	}
	void notifyUpdatedValue() {
		this->value = this->pParent->GetDouble(key);
	}
	void set(double value) {
		this->value = value;
		this->pParent->PutDouble(key, value);
	}
};

class BoolParameter: public Parameter<bool> {
public:
	BoolParameter(std::string key, Preferences* parent) :
			Parameter<bool>(key, parent) {
		// load in initial values
		notifyUpdatedValue();
	}
	void notifyUpdatedValue() {
		this->value = this->pParent->GetBoolean(key);
	}
	void set(bool value) {
		this->value = value;
		this->pParent->PutBoolean(key, value);
	}
};

#endif /* SRC_UTILS_PARAMETER_H_ */
