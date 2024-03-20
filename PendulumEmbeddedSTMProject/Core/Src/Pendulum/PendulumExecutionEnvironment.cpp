#include <PendulumExecutionEnvironment.h>

#ifndef STM32
#define _USE_MATH_DEFINES
#else
#define M_PI           3.14159265358979323846  // Pi constant because not always included in all cmath header implementations
#endif

#include <cmath>
#include <vector>
#include <cstdlib>
#include <cstdint>


#ifdef PENDULUM_TRACE
#include <iostream>
#endif


extern "C" {
    #include <TPGGraph.h>
    // Pointer shared with the TPG c code gen to access environment data
    #ifndef TYPE_INT
    double* in1;
    #else
    int* in1;
    #endif
}

const double PendulumExecutionEnvironment::MAX_SPEED = 8.0;
const double PendulumExecutionEnvironment::MAX_TORQUE = 2.0;
const double PendulumExecutionEnvironment::TIME_DELTA = 0.05;
const double PendulumExecutionEnvironment::G = 9.81;
const double PendulumExecutionEnvironment::MASS = 1.0;
const double PendulumExecutionEnvironment::LENGTH = 1.0;

double PendulumExecutionEnvironment::generateRandDouble(double min, double max){
	double r = (double)rand() / RAND_MAX;
	return (r * (max - min)) + min;
}

void PendulumExecutionEnvironment::setAngle(double newValue) {
    this->currentState[0] = newValue;
    this->modifiedState[0] = newValue * COEFF_DYNAMIC_OPPENING;
}

void PendulumExecutionEnvironment::setVelocity(double newValue) {
    this->currentState[1] = newValue;
    this->modifiedState[1] = newValue * COEFF_DYNAMIC_OPPENING;
}

double PendulumExecutionEnvironment::getAngle() const {
    return this->currentState[0];
}

double PendulumExecutionEnvironment::getVelocity() const {
    return this->currentState[1];
}

void PendulumExecutionEnvironment::reset(size_t seed) {
    srand(seed);
    setAngle(generateRandDouble(-M_PI, M_PI));
    setVelocity(generateRandDouble(-1.0, 1.0));
}

void PendulumExecutionEnvironment::reset(double initalAngle, double initialVelocity){
    this->setAngle(initalAngle);
    this->setVelocity(initialVelocity);
}

double PendulumExecutionEnvironment::getActionFromID(const uint64_t &actionID) {
    double result = (actionID == 0) ? 0.0 : this->availableActions.at((actionID - 1) % availableActions.size());
    return (actionID <= availableActions.size()) ? result : -result;
}

void PendulumExecutionEnvironment::doAction(uint64_t& actionID) {
    // Get the action
    double currentAction = getActionFromID(actionID);
    currentAction *= PendulumExecutionEnvironment::MAX_TORQUE;

    // Get current state
    double angle = this->getAngle();
    double velocity = this->getVelocity();

    // Update angular velocity
    velocity = velocity + ((-3.0) * G / (2.0 * LENGTH) * (sin(angle + M_PI)) +
                           (3.f / (MASS * LENGTH * LENGTH)) * currentAction) * TIME_DELTA;
    velocity = std::fmin(std::fmax(velocity, -MAX_SPEED), MAX_SPEED);

    // Update angle
    angle = angle + velocity * TIME_DELTA;

    // Save new pendulum state
    this->setAngle(angle);
    this->setVelocity(velocity);
}


void PendulumExecutionEnvironment::startInference(int nbSteps){

	for(int i = 0; i < nbSteps; i++){
		this->currentStep = i;
		uint64_t action = (uint64_t)inferenceTPG();
		this->doAction(action);

#ifdef PENDULUM_TRACE
		std::cout << *this << " === Step " << i << ", action : " << getActionFromID(action) << std::endl;
#endif
	}

	this->currentStep = -1;
}


#ifdef PENDULUM_TRACE
std::ostream& operator<<(std::ostream& os, const PendulumExecutionEnvironment& pendulum){
    return os << "Pendulum current state : { Angle = " << pendulum.getAngle() << ", Velocity = " << pendulum.getVelocity() << "}";
}
#endif
