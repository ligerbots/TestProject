#ifndef SRC_UTILS_IPARAMETER_H_
#define SRC_UTILS_IPARAMETER_H_

class IParameter {
public:
	std::mutex lock;
	virtual void updateValue() = 0;
	virtual ~IParameter(){
	}
};

#endif /* SRC_UTILS_IPARAMETER_H_ */
