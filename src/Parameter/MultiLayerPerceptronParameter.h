//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#ifndef CLASSIFICATION_MULTILAYERPERCEPTRONPARAMETER_H
#define CLASSIFICATION_MULTILAYERPERCEPTRONPARAMETER_H


#include "LinearPerceptronParameter.h"
#include "ActivationFunction.h"

class MultiLayerPerceptronParameter : public LinearPerceptronParameter{
private:
    int hiddenNodes;
    ActivationFunction activationFunction;
public:
    MultiLayerPerceptronParameter(int seed, double learningRate, double etaDecrease, double crossValidationRatio, int epoch, int hiddenNodes, ActivationFunction activationFunction);
    [[nodiscard]] int getHiddenNodes() const;
    [[nodiscard]] ActivationFunction getActivationFunction() const;
};


#endif //CLASSIFICATION_MULTILAYERPERCEPTRONPARAMETER_H
