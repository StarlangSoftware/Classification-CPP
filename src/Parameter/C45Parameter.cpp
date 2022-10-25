//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#include "C45Parameter.h"

/**
 * Parameters of the C4.5 univariate decision tree classifier.
 *
 * @param seed                 Seed is used for random number generation.
 * @param prune                Boolean value for prune.
 * @param crossValidationRatio Double value for cross crossValidationRatio ratio.
 */
C45Parameter::C45Parameter(int seed, bool prune, double crossValidationRatio) : Parameter(seed) {
    this->prune = prune;
    this->crossValidationRatio = crossValidationRatio;
}

/**
 * Accessor for the prune.
 *
 * @return Prune.
 */
bool C45Parameter::isPrune() const{
    return prune;
}

/**
 * Accessor for the crossValidationRatio.
 *
 * @return crossValidationRatio.
 */
double C45Parameter::getCrossValidationRatio() const{
    return crossValidationRatio;
}
