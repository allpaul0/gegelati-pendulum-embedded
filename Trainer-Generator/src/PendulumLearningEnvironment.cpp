#define _USE_MATH_DEFINES // To get M_PI
#include <math.h>

#include "PendulumLearningEnvironment.h"

const double PendulumLearningEnvironment::MAX_SPEED = 8.0;
const double PendulumLearningEnvironment::MAX_TORQUE = 2.0;
const double PendulumLearningEnvironment::TIME_DELTA = 0.05;
const double PendulumLearningEnvironment::G = 9.81;
const double PendulumLearningEnvironment::MASS = 1.0;
const double PendulumLearningEnvironment::LENGTH = 1.0;
const double PendulumLearningEnvironment::STABILITY_THRESHOLD = 0.1;


void PendulumLearningEnvironment::setAngle(double newValue)
{
	this->currentState.setDataAt(typeid(double), 0, newValue);
	this->modifiedState.setDataAt(typeid(double), 0, newValue * COEFF_DYNAMIC_OPPENING);
}

void PendulumLearningEnvironment::setVelocity(double newValue)
{
	this->currentState.setDataAt(typeid(double), 1, newValue);
	this->modifiedState.setDataAt(typeid(double), 1, newValue * COEFF_DYNAMIC_OPPENING);
}

double PendulumLearningEnvironment::getAngle() const
{
	return *this->currentState.getDataAt(typeid(const double), 0).getSharedPointer<const double>();
}

double PendulumLearningEnvironment::getVelocity() const
{
	return *this->currentState.getDataAt(typeid(const double), 1).getSharedPointer<const double>();
}

std::vector<std::reference_wrapper<const Data::DataHandler>> PendulumLearningEnvironment::getDataSources()
{
	auto result = std::vector<std::reference_wrapper<const Data::DataHandler>>();
	result.emplace_back(this->modifiedState);
	return result;
}

void PendulumLearningEnvironment::reset(size_t seed, Learn::LearningMode mode)
{
	// Create seed from seed and mode
	size_t hash_seed = Data::Hash<size_t>()(seed) ^ Data::Hash<Learn::LearningMode>()(mode);

	// Reset the RNG
	this->rng.setSeed(hash_seed);

	// Set initial state
	this->setAngle(this->rng.getDouble(-M_PI, M_PI));
	this->setVelocity(this->rng.getDouble(-1.0, 1.0));
	this->nbActionsExecuted = 0;
	this->totalReward = 0.0;
}

void PendulumLearningEnvironment::reset(double initalAngle, double initialVelocity){
	this->setAngle(initalAngle);
	this->setVelocity(initialVelocity);
	this->nbActionsExecuted = 0;
	this->totalReward = 0.0;
}

double PendulumLearningEnvironment::getActionFromID(const uint64_t& actionID)
{
	double result = (actionID == 0) ? 0.0 : this->availableActions.at((actionID - 1) % availableActions.size());
	return (actionID <= availableActions.size()) ? result : -result;
}

void PendulumLearningEnvironment::doAction(uint64_t actionID)
{
	// Get the action
	double currentAction = getActionFromID(actionID);
	currentAction *= PendulumLearningEnvironment::MAX_TORQUE;

	// Get current state
	double angle = this->getAngle();
	double velocity = this->getVelocity();

	// Compute current reward
	double angleToUpward = fmod((angle + M_PI), (2.f * M_PI)) - M_PI;
	double reward = -((angleToUpward * angleToUpward) + 0.1f * (velocity * velocity) + 0.001f * (currentAction * currentAction));

	// Store and accumulate reward
	this->rewardHistory[this->nbActionsExecuted % REWARD_HISTORY_SIZE] = reward;
	this->nbActionsExecuted++;
	this->totalReward += reward;

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

bool PendulumLearningEnvironment::isCopyable() const
{
	return false;
}

Learn::LearningEnvironment* PendulumLearningEnvironment::clone() const
{
	return new PendulumLearningEnvironment(*this);
}

double PendulumLearningEnvironment::getScore() const
{
	if (isTerminal()) {
		// 10/ln(nbActions-MinimumNumberOfActionToConsiderStability)
		// The +2 is added to avoid dividing by ln(1) = 0.
		return 10.0 / std::log(((double)this->nbActionsExecuted - (double)PendulumLearningEnvironment::REWARD_HISTORY_SIZE + 2.0));
	}
	else {
		return this->totalReward / (double)this->nbActionsExecuted;
	}
}

bool PendulumLearningEnvironment::isTerminal() const
{
	bool result = false;

	// Is the history long enough to check stability
	if (this->nbActionsExecuted >= PendulumLearningEnvironment::REWARD_HISTORY_SIZE) {
		// Compute mean reward
		double accumulatedReward = 0.0;
		for (size_t idx = 0; idx < PendulumLearningEnvironment::REWARD_HISTORY_SIZE; idx++) {
			accumulatedReward += this->rewardHistory[idx];
		}
		accumulatedReward /= (double)PendulumLearningEnvironment::REWARD_HISTORY_SIZE;

		// Check stability
		result = (fabs(accumulatedReward) < PendulumLearningEnvironment::STABILITY_THRESHOLD);
	}

	// The history is too short, or the pendulum was not stabilized.
	return result;
}
