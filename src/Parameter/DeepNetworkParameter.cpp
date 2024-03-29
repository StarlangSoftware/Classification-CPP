//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#include "DeepNetworkParameter.h"

/**
 * Parameters of the deep network classifier.
 *
 * @param seed                 Seed is used for random number generation.
 * @param learningRate         Double value for learning rate of the algorithm.
 * @param etaDecrease          Double value for decrease in eta of the algorithm.
 * @param crossValidationRatio Double value for cross validation ratio of the algorithm.
 * @param epoch                Integer value for epoch number of the algorithm.
 * @param hiddenLayers         An integer vector for hidden layers of the algorithm.
 * @param activationFunction   Activation function
 */
DeepNetworkParameter::DeepNetworkParameter(int seed, double learningRate, double etaDecrease,
                                           double crossValidationRatio, int epoch, const vector<int>& hiddenLayers,
                                           ActivationFunction activationFunction) : LinearPerceptronParameter(seed, learningRate, etaDecrease, crossValidationRatio, epoch) {
    this->hiddenLayers = hiddenLayers;
    this->activationFunction = activationFunction;
}

/**
 * The layerSize method returns the size of the hiddenLayers ArrayList.
 *
 * @return The size of the hiddenLayers ArrayList.
 */
int DeepNetworkParameter::layerSize() const{
    return hiddenLayers.size();
}

/**
 * The getHiddenNodes method takes a layer index as an input and returns the element at the given index of hiddenLayers
 * vector.
 *
 * @param layerIndex Index of the layer.
 * @return The element at the layerIndex of hiddenLayers vector.
 */
int DeepNetworkParameter::getHiddenNodes(int layerIndex) const{
    return hiddenLayers.at(layerIndex);
}

/**
 * Accessor for the activation function.
 *
 * @return The activation function.
 */
ActivationFunction DeepNetworkParameter::getActivationFunction() const{
    return activationFunction;
}
