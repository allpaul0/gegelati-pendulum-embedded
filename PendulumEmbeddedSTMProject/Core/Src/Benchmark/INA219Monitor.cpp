#include "INA219Monitor.h"
#include "ina219.h"
#include <cmath>
#include <iostream>
#include <vector>

INA219Monitor::INA219Monitor(INA219_t * ina219t,
	TIM_HandleTypeDef * tim, TimeUnit timUnit, float timMultiplier)
	: Monitor(tim, timUnit, timMultiplier), ina219t(ina219t){}

void INA219Monitor::clearHistory(){
	//clear the vectors
	this->vecCurrent.clear();
	this->vecPower.clear();
}

void INA219Monitor::flushHistory(){

	if (vecCurrent.size() != vecPower.size()){
		std::cerr << "Error: cannot display the log history\n"
				<<"INA219Monitor::flushHistory()\n"
				<< "vecCurrent.size() != vecPower.size()" << std::endl;
	}else{
		// no implementation
	}
}

void INA219Monitor::record(){
	//add measures to the vectors
	this->vecCurrent.push_back(INA219_ReadCurrent(this->ina219t));
	this->vecPower.push_back(INA219_ReadPower(this->ina219t));
}

