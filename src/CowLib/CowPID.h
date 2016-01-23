/*
 * CowPID.h
 *
 *  Created on: Jan 11, 2016
 *      Author: kchau
 */

#ifndef SRC_COWLIB_COWPID_H_
#define SRC_COWLIB_COWPID_H_

#include <cmath>
#include <cfloat>

namespace CowLib {

class CowPID {
public:
	CowPID();
	virtual ~CowPID();
private:
    double m_P;            // factor for "proportional" control
    double m_I;            // factor for "integral" control
    double m_D;            // factor for "derivative" control
    double m_maximumOutput = 1.0;    // |maximum output|
    double m_minimumOutput = -1.0;    // |minimum output|
    double m_maximumInput = 0.0;        // maximum input - limit setpoint to this
    double m_minimumInput = 0.0;        // minimum input - limit setpoint to this
    bool m_continuous = false;    // do the endpoints wrap around? eg. Absolute encoder
    double m_prevError = 0.0;    // the prior sensor input (used to compute velocity)
    double m_totalError = 0.0; //the sum of the errors for use in the integral calc
    double m_setpoint = 0.0;
    double m_error = 0.0;
    double m_result = 0.0;
   //` double m_last_input = std::nan;
};

} /* namespace CowLib */

#endif /* SRC_COWLIB_COWPID_H_ */
