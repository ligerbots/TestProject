/*
 * LigerbotsPreferences.cpp
 *
 *  Created on: Dec 20, 2015
 *      Author: Erik
 */

#include <Utils/LigerbotsPreferences.h>

static const std::string TABLE_NAME = "Preferences";

LigerbotsPreferences* LigerbotsPreferences::instance = NULL;

LigerbotsPreferences::LigerbotsPreferences() :
		parametersMap() {
	pNetworkTable = NetworkTable::GetTable(TABLE_NAME);
	pNetworkTable->AddTableListener(this);
}

LigerbotsPreferences::~LigerbotsPreferences() {
	std::map<std::string, IParameter*>::iterator it;

	// delete all of our parameter objects
	for (it = parametersMap.begin(); it != parametersMap.end(); ++it) {
		delete it->second;
	}

	parametersMap.clear();
}

// returns a singleton instance, like Preferences

LigerbotsPreferences* LigerbotsPreferences::GetInstance() {
	if (instance == NULL)
		instance = new LigerbotsPreferences();
	return instance;
}

// NetworkTables calls this method when a preference was changed (from smartdashboard)
void LigerbotsPreferences::ValueChanged(ITable* source, const std::string &key,
		EntryValue value, bool isNew) {
	// check if key exists in the map
	if (parametersMap.count(key) > 0) {
		parametersMap[key]->notifyUpdatedValue();
	} else {
		// maybe do something here
	}
}

// Since NetworkTables has different methods for getting and setting different value types,
//  we need subclasses of Parameter<type> to deal with calling each method
// It's not possible (afaik) to template creating subclasses like this, so there is a
//  separate method for each type
Parameter<bool>* LigerbotsPreferences::createBoolParameter(
		std::string parameterName) {
	Parameter<bool>* newParameter = new BoolParameter(parameterName, this);
	parametersMap.insert(std::make_pair(parameterName, newParameter));
	return newParameter;
}

Parameter<int>* LigerbotsPreferences::createIntParameter(
		std::string parameterName) {
	Parameter<int>* newParameter = new IntParameter(parameterName, this);
	parametersMap.insert(std::make_pair(parameterName, newParameter));
	return newParameter;
}

Parameter<double>* LigerbotsPreferences::createDoubleParameter(
		std::string parameterName) {
	Parameter<double>* newParameter = new DoubleParameter(parameterName, this);
	parametersMap.insert(std::make_pair(parameterName, newParameter));
	return newParameter;
}

Parameter<std::string>* LigerbotsPreferences::createStringParameter(
		std::string parameterName) {
	Parameter<std::string>* newParameter = new StringParameter(parameterName,
			this);
	parametersMap.insert(std::make_pair(parameterName, newParameter));
	return newParameter;
}

void LigerbotsPreferences::removeParameter(std::string parameterName) {
	std::map<std::string, IParameter*>::iterator it;

	it = parametersMap.find(parameterName);
	if (it != parametersMap.end()) {
		delete it->second;
		parametersMap.erase(it);
	}
}
