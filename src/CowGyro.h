/*
 * CowGyro.h
 *
 *  Created on: Jan 22, 2016
 *      Author: kchau
 */

#ifndef SRC_COWGYRO_H_
#define SRC_COWGYRO_H_

#include <thread>
#include <WPILib.h>

namespace CowLib {

class CowGyro {
private:
	std::thread *m_Thread;
	static void Handle();
public:
	CowGyro();
	virtual ~CowGyro();
	float GetAngle();
};

} /* namespace CowLib */

#endif /* SRC_COWGYRO_H_ */
