#ifndef SRC_BENCHMARK_INA219MONITOR_H_
#define SRC_BENCHMARK_INA219MONITOR_H_

#include "Monitor.h"

#include <vector>
#include <iostream>

#include "main.h"
#include "ina219.h"
#include "TimeUnit.h"

/**
 * \brief Specification of the Monitor class for current and power records using an INA219 current sensor.
 */
class INA219Monitor: public Monitor {

protected:
	/// stores Current measurements
	std::vector<float> vecCurrent;

	/// stores Power measurements
	std::vector<float> vecPower;
	
private:

	/// ina219 handler used for measurements.
	INA219_t *ina219t = NULL;

public:

	/**
	 * \brief Basic constructor.
	 *
	 * \param[in] ina219t the INA219_t * handler to be used for measurements.
	 * \param[out] tim the TIM_HandleTypeDef * of the timer used for auto measurement when this is the activeMonitor, give nullptr for no auto measurement.
	 * \param[in] timUnit the TimeUnit corresponding to the timer time step between recordActveMonitor() calls.
	 * \param[in] timMultiplier a float multiplier applied on timUnit to get the timer time step between recordActveMonitor() calls.
	 */
	INA219Monitor(INA219_t * ina219t, TIM_HandleTypeDef * tim = nullptr, TimeUnit timUnit = TimeUnit::None, float timMultiplier = 0.f);
	
	virtual ~INA219Monitor() {}

	/// Clear the measurement history. Inherited from Monitor.
	virtual void clearHistory() override;

	/// Inherited from Monitor.
	virtual void record() override;

	/// Inherited from Monitor.
    virtual void flushHistory() override;

};

#endif /* SRC_BENCHMARK_INA219MONITOR_H_ */

