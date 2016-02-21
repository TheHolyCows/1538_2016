/*
 * CowLatch.h
 *
 *  Created on: Feb 20, 2016
 *      Author: kchau
 */

#ifndef SRC_COWLIB_COWLATCH_H_
#define SRC_COWLIB_COWLATCH_H_

namespace CowLib {

class CowLatch {
private:
	bool m_State;
	bool m_Latched;
public:
	CowLatch();
	bool Latch(bool value);
	void ResetLatch();
	virtual ~CowLatch();
};

} /* namespace CowLib */

#endif /* SRC_COWLIB_COWLATCH_H_ */
