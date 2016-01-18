/*
 * NTUpdater.h
 *
 *  Created on: Jan 16, 2016
 *      Author: Erik
 */

#ifndef SRC_UTILS_NTUPDATER_H_
#define SRC_UTILS_NTUPDATER_H_

#include <WPILib.h>
#include "llvm/StringRef.h"
#include "IParameter.h"

typedef std::vector<std::shared_ptr<IParameter>> NTParameterVector;

class NTUpdater: public ITableListener {
protected:
	static NTUpdater* instance;
	static std::map<std::string, NTParameterVector> parametersMap;
	static std::mutex lock;
public:
	static std::string TABLE_NAME;
	static std::shared_ptr<NetworkTable> NETWORK_TABLE;

	NTUpdater();
	virtual ~NTUpdater();
	void ValueChanged(ITable* source,
	                            llvm::StringRef key,
	                            std::shared_ptr<nt::Value> value,
	                            bool isNew);
	static void registerNTUpdater();
	static void addParameter(std::string key, std::shared_ptr<IParameter> parameter);
	static void removeParameter(std::string key, std::shared_ptr<IParameter> parameter);
};

#endif /* SRC_UTILS_NTUPDATER_H_ */
