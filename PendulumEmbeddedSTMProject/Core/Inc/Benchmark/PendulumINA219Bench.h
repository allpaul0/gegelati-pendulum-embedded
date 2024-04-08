#ifndef PENDULUM_INA219_MONITOR_H
#define PENDULUM_INA219_MONITOR_H

#include "INA219Bench.h"
#include "PendulumINA219Monitor.h"

/**
 * \brief Specification of the PendulumINA219Bench class
 */
class PendulumINA219Bench: public INA219Bench {

	/// Pointer to the used INA219Monitor
	PendulumINA219Monitor *pendulumINA219Monitor;

	uint32_t nbcyclesInCompute;

public:

	/// Constructor using its own INA219Monitor instance.
	PendulumINA219Bench(void (*fun)(void), INA219_t *ina219t, PendulumExecutionEnvironment *pendulumEE,
		TIM_HandleTypeDef *tim, TimeUnit timUnit = TimeUnit::None, float timMultiplier = 0.f,
		uint32_t nbcyclesInCompute = 0);

	virtual ~PendulumINA219Bench();

	/// Inherited from Bench.
	virtual void startBench() override;

	void printResult();

};

#endif /* PENDULUM_INA219_MONITOR_H */