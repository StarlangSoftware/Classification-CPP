//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#ifndef CLASSIFICATION_MULTILAYERPERCEPTRONPARAMETER_H
#define CLASSIFICATION_MULTILAYERPERCEPTRONPARAMETER_H


#include "LinearPerceptronParameter.h"

class MultiLayerPerceptronParameter : public LinearPerceptronParameter{
private:
    int hiddenNodes;
public:
    MultiLayerPerceptronParameter(int seed, double learningRate, double etaDecrease, double crossValidationRatio, int epoch, int hiddenNodes);
    int getHiddenNodes();
};


#endif //CLASSIFICATION_MULTILAYERPERCEPTRONPARAMETER_H
