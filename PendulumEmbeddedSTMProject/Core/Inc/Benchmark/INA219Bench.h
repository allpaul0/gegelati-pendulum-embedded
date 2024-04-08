#ifndef SRC_BENCHMARK_INA219BENCH_H_
#define SRC_BENCHMARK_INA219BENCH_H_

#include <Bench.h>

#include "main.h"
#include "INA219Monitor.h"
#include "ina219.h"

/**
 * \brief Specification of the Bench class for current and power benchmarks using an INA219 sensor. 
 */
class INA219Bench: public Bench {

	/// Pointer to the used INA219Monitor
	INA219Monitor *monitor;

	uint32_t nbcyclesInCompute;

public:

	/// Constructor using its own INA219Monitor instance.
	INA219Bench(void (*fun)(void), INA219_t *ina219t,
		TIM_HandleTypeDef *tim, TimeUnit timUnit = TimeUnit::None, float timMultiplier = 0.f,
		uint32_t nbcyclesInCompute = 0);

	virtual ~INA219Bench();

};
#endif /* SRC_BENCHMARK_INA219BENCH_H_ */