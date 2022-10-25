//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#ifndef CLASSIFICATION_DEEPNETWORKPARAMETER_H
#define CLASSIFICATION_DEEPNETWORKPARAMETER_H

#include <vector>
#include "LinearPerceptronParameter.h"
#include "ActivationFunction.h"

using namespace std;

class DeepNetworkParameter : public LinearPerceptronParameter {
private:
    vector<int> hiddenLayers;
    ActivationFunction activationFunction;
public:
    DeepNetworkParameter(int seed, double learningRate, double etaDecrease, double crossValidationRatio, int epoch, const vector<int>& hiddenLayers, ActivationFunction activationFunction);
    int layerSize() const;
    int getHiddenNodes(int layerIndex) const;
    ActivationFunction getActivationFunction() const;
};


#endif //CLASSIFICATION_DEEPNETWORKPARAMETER_H
