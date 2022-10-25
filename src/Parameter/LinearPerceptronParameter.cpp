//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#include "LinearPerceptronParameter.h"

/**
 * Parameters of the linear perceptron algorithm.
 *
 * @param seed                 Seed is used for random number generation.
 * @param learningRate         Double value for learning rate of the algorithm.
 * @param etaDecrease          Double value for decrease in eta of the algorithm.
 * @param crossValidationRatio Double value for cross validation ratio of the algorithm.
 * @param epoch                Integer value for epoch number of the algorithm.
 */
LinearPerceptronParameter::LinearPerceptronParameter(int seed, double learningRate, double etaDecrease,
                                                     double crossValidationRatio, int epoch) : Parameter(seed) {
    this->learningRate = learningRate;
    this->etaDecrease = etaDecrease;
    this->crossValidationRatio = crossValidationRatio;
    this->epoch = epoch;
}

/**
 * Accessor for the learningRate.
 *
 * @return The learningRate.
 */
double LinearPerceptronParameter::getLearningRate() const{
    return learningRate;
}

/**
 * Accessor for the etaDecrease.
 *
 * @return The etaDecrease.
 */
double LinearPerceptronParameter::getEtaDecrease() const{
    return etaDecrease;
}

/**
 * Accessor for the crossValidationRatio.
 *
 * @return The crossValidationRatio.
 */
double LinearPerceptronParameter::getCrossValidationRatio() const{
    return crossValidationRatio;
}

/**
 * Accessor for the epoch.
 *
 * @return The epoch.
 */
int LinearPerceptronParameter::getEpoch() const{
    return epoch;
}
