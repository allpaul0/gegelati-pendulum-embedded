#include "INA219Bench.h"

INA219Bench::INA219Bench(void (*fun)(void), INA219_t *ina219t,
	TIM_HandleTypeDef *tim, TimeUnit timUnit, float timMultiplier, uint32_t nbcyclesInCompute)
	: Bench(fun), monitor(new INA219Monitor(ina219t, tim, timUnit, timMultiplier)) {}

INA219Bench::~INA219Bench() {
	delete this->monitor;
}