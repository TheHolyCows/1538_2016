/*
 * CowPID.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: kchau
 */

#include <CowLib/CowPID.h>

namespace CowLib {

CowPID::CowPID(double Kp, double Ki, double Kd)
	:
		m_P(Kp),
		m_I(Ki),
		m_D(Kd),
		m_maximumOutput(1.0),
		m_minimumOutput(-1.0),
		m_maximumInput(0),
		m_minimumInput(0),
		m_continuous(false),
		m_prevError(0),
		m_totalError(0),
		m_setpoint(0),
		m_error(0),
		m_result(0),
		m_last_input(NAN)
{
	// TODO Auto-generated constructor stub

}

CowPID::~CowPID() {
	// TODO Auto-generated destructor stub
}

double CowPID::Calculate(double input)
{
    m_last_input = input;
    m_error = m_setpoint - input;
    if (m_continuous) {
        if (fabs(m_error) >
                (m_maximumInput - m_minimumInput) / 2) {
            if (m_error > 0) {
                m_error = m_error - m_maximumInput + m_minimumInput;
            } else {
                m_error = m_error +
                        m_maximumInput - m_minimumInput;
            }
        }
    }

    if ((m_error * m_P < m_maximumOutput) &&
            (m_error * m_P > m_minimumOutput)) {
        m_totalError += m_error;
    } else {
        m_totalError = 0;
    }

    m_result = (m_P * m_error + m_I * m_totalError + m_D * (m_error - m_prevError));
    m_prevError = m_error;

    if (m_result > m_maximumOutput) {
        m_result = m_maximumOutput;
    } else if (m_result < m_minimumOutput) {
        m_result = m_minimumOutput;
    }
    return m_result;
}

double CowPID::GetError()
{
	return m_error;
}
double CowPID::GetSetpoint()
{
	return m_setpoint;
}

void CowPID::SetSetpoint(double setpoint)
{
    if (m_maximumInput > m_minimumInput) {
        if (setpoint > m_maximumInput) {
            m_setpoint = m_maximumInput;
        } else if (setpoint < m_minimumInput) {
            m_setpoint = m_minimumInput;
        } else {
            m_setpoint = setpoint;
        }
    } else {
        m_setpoint = setpoint;
    }
}

void CowPID::Reset()
{
    m_last_input = NAN;
    m_prevError = 0;
    m_totalError = 0;
    m_result = 0;
    m_setpoint = 0;
}

bool CowPID::OnTarget(double tolerance)
{
    return m_last_input != NAN && fabs(m_last_input - m_setpoint) < tolerance;
}
std::string CowPID::GetState()
{
//    std::string lState = "";
//
//    lState += "Kp: " + m_P + "\n";
//    lState += "Ki: " + m_I + "\n";
//    lState += "Kd: " + m_D + "\n";

    //return lState;
}

void CowPID::SetContinuous(bool continuous)
{
	m_continuous = continuous;
}

void CowPID::SetInputRange(double min, double max)
{
    m_minimumInput = min;
    m_maximumInput = max;
    SetSetpoint(m_setpoint);
}

void CowPID::SetOutputRange(double min, double max)
{
    m_minimumOutput = min;
    m_maximumOutput = max;
}

void CowPID::ResetIntegrator() {
    m_totalError = 0;
}

} /* namespace CowLib */
