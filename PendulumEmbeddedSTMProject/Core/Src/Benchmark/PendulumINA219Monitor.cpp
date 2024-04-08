#include <PendulumINA219Monitor.h>

PendulumINA219Monitor::PendulumINA219Monitor(INA219_t *ina219t, PendulumExecutionEnvironment *pendulumEE,
        TIM_HandleTypeDef *tim, TimeUnit timUnit, float timMultiplier, 
		uint32_t nbcyclesInInterrupt)
        : INA219Monitor(ina219t, tim, timUnit, timMultiplier),
          pendulumEE(pendulumEE),
          nbcyclesInInterrupt(nbcyclesInInterrupt) {}

void PendulumINA219Monitor::record() {

	uint32_t entry = Cortex_M4_GetCycleCounter(); /* get cycle counter */
 	
	/* call function and count cycles */
	this->vecStep.push_back(pendulumEE->getCurrentStep());

	INA219Monitor::record();

	uint32_t exit = Cortex_M4_GetCycleCounter(); /* get cycle counter */

	nbcyclesInInterrupt = nbcyclesInInterrupt + (exit-entry);
}

void PendulumINA219Monitor::clearHistory(){
	INA219Monitor::clearHistory();
	this->resetNbCycleInInterrupt();
	this->vecStep.clear();
}


void PendulumINA219Monitor::resetNbCycleInInterrupt(){
	this->nbcyclesInInterrupt = 0;
}

uint32_t PendulumINA219Monitor::getNbCycleInInterrupt(){
	return this->nbcyclesInInterrupt;
}

void PendulumINA219Monitor::flushHistory() {
	if ((vecCurrent.size() != vecPower.size()) || (vecCurrent.size() != vecStep.size())){
		std::cerr << "Error: cannot display the log history\n"
				<<"INA219Monitor::flushHistory()\n"
				<< "vecCurrent.size() != vecPower.size()" << std::endl;
	}else{
		while (!vecCurrent.empty()) {
		
			std::cout << vecStep.front() << "\t"		
					<< vecCurrent.front() << "\t"
					<< vecPower.front() << std::endl;

			vecStep.erase(vecStep.begin());
			vecCurrent.erase(vecCurrent.begin());
			vecPower.erase(vecPower.begin());
		}
	}
}

void PendulumINA219Monitor::writeHeader() {
	std::cout << "dataTimeUnit : " << getTimeUnitString(this->timerUnit)
			<< "\tdataTimerMultiplier : " << this->timerMultiplier
			<< "\tStartAngle : " << this->initAngle // Environment state before calling the bench function
			<< "\tStartVelocity : " << this->initVelocity
			<< std::endl;
	std::cout << "Step\tCurrent\tPower" << std::endl;
}


void PendulumINA219Monitor::storeInitialParameters() {
	this->initAngle = this->pendulumEE->getAngle();
	this->initVelocity = this->pendulumEE->getVelocity();
}