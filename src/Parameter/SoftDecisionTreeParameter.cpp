//
// Created by Oğuz Kerem Yıldız on 3.12.2025.
//

#include "SoftDecisionTreeParameter.h"

SoftDecisionTreeParameter::SoftDecisionTreeParameter(int seed, double learningRate, double etaDecrease, double crossValidationRatio, int epoch, double alpha) : LinearPerceptronParameter(seed, learningRate, etaDecrease, crossValidationRatio, epoch) {
    this->alpha = alpha;
}

double SoftDecisionTreeParameter::getAlpha() const {
    return alpha;
}
