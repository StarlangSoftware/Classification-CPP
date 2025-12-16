//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#ifndef CLASSIFICATION_LINEARPERCEPTRONPARAMETER_H
#define CLASSIFICATION_LINEARPERCEPTRONPARAMETER_H
#include "Parameter.h"

class LinearPerceptronParameter : public Parameter {
protected:
    double learningRate;
    double etaDecrease;
    double crossValidationRatio;
private:
    int epoch;
public:
    LinearPerceptronParameter(int seed, double learningRate, double etaDecrease, double crossValidationRatio, int epoch);
    [[nodiscard]] double getLearningRate() const;
    [[nodiscard]] double getEtaDecrease() const;
    [[nodiscard]] double getCrossValidationRatio() const;
    [[nodiscard]] int getEpoch() const;
};


#endif //CLASSIFICATION_LINEARPERCEPTRONPARAMETER_H
