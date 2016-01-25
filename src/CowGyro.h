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

typedef enum
{
	INVALID_DATA,
	VALID_DATA,
	SELF_TEST_DATA,
	RW_RESPONSE,
	STATUS_FLAG_ERROR
} e_StatusFlag;

typedef enum
{
	PLL_FAILURE = 7,
	QUADRATURE_ERROR = 6,
	NONVOLATILE_MEMORY_FAULT = 5,
	RESET_INITIALIZE_FAILURE = 4,
	POWER_FAILURE = 3,
	CONTINUOUS_SELFTEST_FAILURE = 2,
	GENERATED_FAULTS = 1
} e_ErrorFlag;

class CowGyro
{
private:
	std::thread *m_Thread;
	static void Handle();
	static SPI* m_Spi;
	static std::vector<e_ErrorFlag> m_ALL_ERRORS;// = {PLL_FAILURE, QUADRATURE_ERROR, NONVOLATILE_MEMORY_FAULT, RESET_INITIALIZE_FAILURE, POWER_FAILURE, CONTINUOUS_SELFTEST_FAILURE, GENERATED_FAULTS};
	static const int SENSOR_DATA_CMD = 0x20000000;
	static const int CHK_GENERATE_FAULTS_BIT = 0x03;
	static const int32_t K_READING_RATE = 200;
	static const int32_t K_ZEROING_SAMPLES = 5 * K_READING_RATE;
	static const int32_t K_STARTUP_SAMPLES = 2 * K_READING_RATE;

	static std::atomic<bool> m_VolatileHasData;
	static double m_VolatileAngle;
	static double m_VolatileRate;
	static std::atomic<bool> m_VolatileShouldReZero;
	static double m_ZeroHeading;
	static int32_t m_RemainingStartupCycles;
	static bool m_IsZeroed;
	static double m_ZeroRatesSamples[K_ZEROING_SAMPLES];
	//static int32_t m_ZeroRateSampleIndex;
	//static bool m_HasEnoughZeroingSamples;
	static double m_ZeroBias;
	static double m_Angle;
	static double m_LastTime;
	static bool m_Calibrating;
	static uint16_t m_StartIndex;
	static uint16_t m_CurrentIndex;
	static CowGyro *m_Instance;
public:
	CowGyro();
	virtual ~CowGyro();
	static int16_t DoRead(int8_t address);
	static double ExtractAngleRate(int32_t result);
	float GetAngle();
	double GetRate();
	static bool InitializeGyro();
	static int16_t ReadPartId();
	int32_t ReadSerialNumber();
	static int32_t GetReading();
	static void Reset();
	static e_StatusFlag ExtractStatus(int32_t result);
	static std::vector<e_ErrorFlag> ExtractErrors(int32_t result);
	static void BeginCalibration();
	static void FinalizeCalibration();
	static CowGyro* GetInstance();
private:
	static int32_t DoTransaction(int32_t command);
	static bool IsOddParity(int32_t word);
};

} /* namespace CowLib */

#endif /* SRC_COWGYRO_H_ */
