/*
 * IParameter.h
 *
 *  Created on: Dec 25, 2015
 *      Author: Erik
 */

#ifndef SRC_UTILS_IPARAMETER_H_
#define SRC_UTILS_IPARAMETER_H_

class IParameter {
public:
	IParameter() {
	}
	virtual ~IParameter() {
	}
	virtual void notifyUpdatedValue() = 0;
};

#endif /* SRC_UTILS_IPARAMETER_H_ */
