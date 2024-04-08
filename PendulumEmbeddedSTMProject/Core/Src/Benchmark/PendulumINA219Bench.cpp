#include "PendulumINA219Bench.h"

PendulumINA219Bench::PendulumINA219Bench(
    void (*fun)(void), INA219_t *ina219t, PendulumExecutionEnvironment *pendulumEE,
	TIM_HandleTypeDef *tim, TimeUnit timUnit, float timMultiplier, uint32_t nbcyclesInCompute)
	: INA219Bench(fun, ina219t, tim, timUnit, timMultiplier, nbcyclesInCompute),
    pendulumINA219Monitor(new PendulumINA219Monitor(ina219t, pendulumEE, tim, timUnit, timMultiplier)) {}

PendulumINA219Bench::~PendulumINA219Bench() {
	delete this->pendulumINA219Monitor;
}

void PendulumINA219Bench::startBench(){

	// Benchmark is currently running.
	this->state = BenchState::Working;

	// Store the initial conditions of the PendulumEE
	this->pendulumINA219Monitor->storeInitialParameters();

    // Clear the cycles in compute history
    this->nbcyclesInCompute = 0;

	// Clear the measurement history.
	this->pendulumINA219Monitor->clearHistory();

	// Set this Monitor as the activeMonitor and starts auto measurement using its associated timer.
	this->pendulumINA219Monitor->makeActive();

	Cortex_M4_ResetCycleCounter(); /* reset cycle counter */

	// The function used for the benchmark.
	(*this->benchFunction)();

	this->nbcyclesInCompute = Cortex_M4_GetCycleCounter(); /* get cycle counter */

	// Set the activeMonitor to nullptr.
	//INA219Monitor::noActiveMonitor();
    this->pendulumINA219Monitor->noActiveMonitor();

	// Last benchmark succeeded, results are valid.
	this->state = BenchState::Ok;
}

void PendulumINA219Bench::printResult(){

	if(this->state == BenchState::Ok){

		// Writes a header for the results in stdout.
		this->pendulumINA219Monitor->writeHeader();

		// Send history values to stdout.
		this->pendulumINA219Monitor->flushHistory();

		auto nbcycles_interrupt = this->pendulumINA219Monitor->getNbCycleInInterrupt();
		auto ratio_interrupt_compute = ((double) nbcycles_interrupt/(double) this->nbcyclesInCompute)*100;
		std::cout << "=== C_nbcyclesInterrupt : " << nbcycles_interrupt << " cycles" << std::endl;
		std::cout << "=== C_nbcyclesCompute : " << this->nbcyclesInCompute << " cycles" << std::endl;
		std::cout << "=== C_ratioInterruptCompute : " << ratio_interrupt_compute << "%" << std::endl;
	}

}
