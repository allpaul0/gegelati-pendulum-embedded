#ifndef INC_BENCHMARK_PENDULUMINA219MONITOR_H_
#define INC_BENCHMARK_PENDULUMINA219MONITOR_H_

#include <vector>
#include <iostream>

#include <INA219Monitor.h>
#include <PendulumExecutionEnvironment.h>

/**
 * \brief Specification of the INA219Monitor class for the Pendulum environment, add record of the Pendulum current step.
 */
class PendulumINA219Monitor: public INA219Monitor {

	/// The PendulumExecutionEnvironment instance used.
	PendulumExecutionEnvironment *pendulumEE;

	/// Record the step number in the PendulumExecutionEnvironment for each current/power measure.
	std::vector<int> vecStep;

	/// number of cycles in interrupt mode, fetch from the Cycle Counter
	uint32_t nbcyclesInInterrupt; 

	//values used to store the initial parameters of the PendulumEE
	double initAngle = 0.0;

	double initVelocity = 0.0;

public:
	/**
	 * \brief Base constructor.
	 * 
	 * \param[out] ina219t the INA219_t * handler to be used for measurements.
	 * \param[in] pendulumEE the PendulumExecutionEnvironement used.
	 * \param[out] tim the TIM_HandleTypeDef * of the timer used for auto measurement when this is the activeMonitor, give nullptr for no auto measurement.
	 * \param[in] timUnit the TimeUnit corresponding to the timer time step between recordActveMonitor() calls.
	 * \param[in] timMultiplier a float multiplier applied on timUnit to get the timer time step between recordActveMonitor() calls.
	 */
	PendulumINA219Monitor(INA219_t *ina219t, PendulumExecutionEnvironment *pendulumEE,
			TIM_HandleTypeDef *tim = nullptr, TimeUnit timUnit = TimeUnit::None, float timMultiplier = 0.f,
			uint32_t nbcyclesInInterrupt = 0);
	
	virtual ~PendulumINA219Monitor() {};

	// reset cycles in interrupt history
	void resetNbCycleInInterrupt();

	uint32_t getNbCycleInInterrupt();

	/// Inherited from Monitor.
	virtual void record() override;

	/// Inherited from Monitor.
	virtual void flushHistory() override;

	/// Clear the measurement history. Inherited from Monitor.
	virtual void clearHistory() override;

	// write header to stdout
	virtual void writeHeader();

	// Pendulum Execution Environment state before calling the bench function
	void storeInitialParameters();
};

#endif /* INC_BENCHMARK_PENDULUMINA219MONITOR_H_ */
