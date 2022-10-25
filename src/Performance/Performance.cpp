//
// Created by olcay on 31.01.2019.
//

#include "Performance.h"

/**
 * Constructor that sets the error rate.
 *
 * @param errorRate Double input.
 */
Performance::Performance(double errorRate) {
    this->errorRate = errorRate;
}

/**
 * Accessor for the error rate.
 *
 * @return Double errorRate.
 */
double Performance::getErrorRate() const{
    return errorRate;
}

bool Performance::isClassification() const{
    return false;
}

bool Performance::containsDetails() const{
    return false;
}
