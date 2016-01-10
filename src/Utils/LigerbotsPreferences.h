/*
 * LigerbotsPreferences.h
 *
 *  Created on: Dec 20, 2015
 *      Author: Erik
 */

#ifndef SRC_UTILS_LIGERBOTSPREFERENCES_H_
#define SRC_UTILS_LIGERBOTSPREFERENCES_H_

#include <Preferences.h>
#include "Utils/Parameter.h"
#include "Utils/IParameter.h"

// hacky forward declaration because circular references don't work
template<typename Parameter_Type> class Parameter;

class LigerbotsPreferences: protected Preferences {
public:
	virtual ~LigerbotsPreferences();
	static LigerbotsPreferences* GetInstance();
	/**
	 * Register a new boolean parameter
	 * @param parameterName The name of the parameter
	 * @return A Parameter object that holds the parameter value
	 */
	Parameter<bool>* createBoolParameter(std::string parameterName);
	/**
	 * Register a new integer parameter
	 * @param parameterName The name of the parameter
	 * @return A Parameter object that holds the parameter value
	 */
	Parameter<int>* createIntParameter(std::string parameterName);
	/**
	 * Register a new decimal parameter
	 * @param parameterName The name of the parameter
	 * @return A Parameter object that holds the parameter value
	 */
	Parameter<double>* createDoubleParameter(std::string parameterName);
	/**
	 * Register a new string parameter
	 * @param parameterName The name of the parameter
	 * @return A Parameter object that holds the parameter value
	 */
	Parameter<std::string>* createStringParameter(std::string parameterName);
	/**
	 * Removes the specified parameter. This deletes the parameter object, so make sure to clean up pointers
	 * @param parameterName The name of the parameter
	 */
	void removeParameter(std::string parameterName);
	void ValueChanged(ITable* source, const std::string &key, EntryValue value,
			bool isNew) override;

protected:
	LigerbotsPreferences();
	ITable* pNetworkTable;
	std::map<std::string, IParameter*> parametersMap;

	static LigerbotsPreferences* instance;
};

#endif /* SRC_UTILS_LIGERBOTSPREFERENCES_H_ */
