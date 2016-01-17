#include <WPILib.h>
#include <Utils/NTUpdater.h>

std::string NTUpdater::TABLE_NAME = "Preferences";
NTUpdater* NTUpdater::instance = NULL;
std::shared_ptr<NetworkTable> NTUpdater::NETWORK_TABLE;
std::map<std::string, NTParameterVector> NTUpdater::parametersMap;

NTUpdater::NTUpdater() {
}

NTUpdater::~NTUpdater() {
}

void NTUpdater::registerNTUpdater() {
	if (instance != NULL)
		return;
	instance = new NTUpdater();
	NETWORK_TABLE = NetworkTable::GetTable(TABLE_NAME);
	NETWORK_TABLE->AddTableListener(instance);
}

void NTUpdater::addParameter(std::string key,
		std::shared_ptr<IParameter> parameter) {
	std::map<std::string, NTParameterVector>::iterator it = parametersMap.find(
			key);
	if (it == parametersMap.end()) {
		NTParameterVector parameterVector;
		parameterVector.push_back(parameter);
		parametersMap.insert(std::make_pair(key, parameterVector));
	} else {
		it->second.push_back(parameter);
	}
}

void NTUpdater::removeParameter(std::string key,
		std::shared_ptr<IParameter> parameter) {
	std::map<std::string, NTParameterVector>::iterator it = parametersMap.find(
			key);
	if (it != parametersMap.end()) {
		for (NTParameterVector::iterator it2 = it->second.begin();
						it2 != it->second.end(); ++it2) {
			if(*(*it2) == *(parameter)){
				it->second.erase(it2);
			}
		}
	}
}

void NTUpdater::ValueChanged(ITable* source, llvm::StringRef key,
		std::shared_ptr<nt::Value> value,
		bool isNew) {
	std::map<std::string, NTParameterVector>::iterator it = parametersMap.find(
			key);
	if (it != parametersMap.end()) {
		for (NTParameterVector::iterator it2 = it->second.begin();
				it2 != it->second.end(); ++it2) {
			(*it2)->updateValue();
		}
	}
}
