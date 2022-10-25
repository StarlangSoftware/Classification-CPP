//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#include "BaggingParameter.h"

/**
 * Parameters of the bagging trees algorithm.
 *
 * @param seed         Seed is used for random number generation.
 * @param ensembleSize The number of trees in the bagged forest.
 */
BaggingParameter::BaggingParameter(int seed, int ensembleSize) : Parameter(seed) {
    this->ensembleSize = ensembleSize;
}

/**
 * Accessor for the ensemble size.
 *
 * @return The ensemble size.
 */
int BaggingParameter::getEnsembleSize() const{
    return ensembleSize;
}
