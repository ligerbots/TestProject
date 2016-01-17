#ifndef SRC_UTILS_IPARAMETER_H_
#define SRC_UTILS_IPARAMETER_H_

class IParameter {
public:
	virtual void updateValue();
	virtual ~IParameter();
};

#endif /* SRC_UTILS_IPARAMETER_H_ */
