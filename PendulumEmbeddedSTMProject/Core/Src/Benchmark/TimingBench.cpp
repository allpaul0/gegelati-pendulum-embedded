#include "TimingBench.h"

#include <algorithm>
#include <iostream>
#include "main.h"
#include "TimeUnit.h"

TimingBench::TimingBench(void (*fun)(void), TIM_HandleTypeDef * timer, TimeUnit unit, float unitMultiplier)
	: Bench(fun), tim(timer), timerUnit(unit), timerMultiplier(unitMultiplier), result(-1)
{
	HAL_TIM_Base_Stop(timer);
}

void TimingBench::startBench(){

	this->state = BenchState::Working;

	// Reset results
	this->result = 0;
	this->attemptResults.clear();

	for(int i = 0; i < this->nbAttempts; i++){
		

		// Reset counter and start timer
		__HAL_TIM_SET_COUNTER(this->tim, (int32_t)(0x0));
		HAL_TIM_Base_Start(this->tim);

		(*this->benchFunction)();

		HAL_TIM_Base_Stop(this->tim);
		uint32_t raw = (uint32_t)(__HAL_TIM_GET_COUNTER(this->tim));
		int timing = (int)raw;
		this->attemptResults.push_back(timing);
		this->result += timing;
	}

	// Compute final result
	this->result = this->result / this->nbAttempts;

	this->state = BenchState::Ok;
}

int TimingBench::getResult() { return this->result; }


void TimingBench::printResult(){

	if(this->state == BenchState::Ok){

		int maxTime = *std::max_element(this->attemptResults.cbegin(), this->attemptResults.cend());
		int minTime = *std::min_element(this->attemptResults.cbegin(), this->attemptResults.cend());

		// Choose unit string
		const char * unitStr;
		unitStr = getTimeUnitString(this->timerUnit);

		std::cout << "=== T_min : " << std::fixed << (minTime * this->timerMultiplier) << ' ' << unitStr << std::endl;
		std::cout << "=== T_avg : " << (this->result * this->timerMultiplier) << ' ' << unitStr << std::endl;
		std::cout << "=== T_max : " << (maxTime * this->timerMultiplier) << ' ' << unitStr << std::defaultfloat << std::endl;

	}

}



