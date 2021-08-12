//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#include "MultiLayerPerceptronParameter.h"

/**
 * Parameters of the multi layer perceptron algorithm.
 *
 * @param seed                 Seed is used for random number generation.
 * @param learningRate         Double value for learning rate of the algorithm.
 * @param etaDecrease          Double value for decrease in eta of the algorithm.
 * @param crossValidationRatio Double value for cross validation ratio of the algorithm.
 * @param epoch                Integer value for epoch number of the algorithm.
 * @param hiddenNodes          Integer value for the number of hidden nodes.
 * @param activationFunction   Activation function
 */
MultiLayerPerceptronParameter::MultiLayerPerceptronParameter(int seed, double learningRate, double etaDecrease,
                                                             double crossValidationRatio, int epoch, int hiddenNodes,
                                                             ActivationFunction activationFunction) : LinearPerceptronParameter(seed, learningRate, etaDecrease, crossValidationRatio, epoch){
    this->hiddenNodes = hiddenNodes;
    this->activationFunction = activationFunction;
}

/**
 * Accessor for the hiddenNodes.
 *
 * @return The hiddenNodes.
 */
int MultiLayerPerceptronParameter::getHiddenNodes() {
    return hiddenNodes;
}

/**
 * Accessor for the activation function.
 *
 * @return The activation function.
 */
ActivationFunction MultiLayerPerceptronParameter::getActivationFunction() {
    return activationFunction;
}
