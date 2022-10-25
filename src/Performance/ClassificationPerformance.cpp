//
// Created by olcay on 31.01.2019.
//

#include "ClassificationPerformance.h"

/**
 * A constructor that sets the accuracy and errorRate as 1 - accuracy via given accuracy.
 *
 * @param accuracy Double value input.
 */
ClassificationPerformance::ClassificationPerformance(double accuracy) : Performance(1 - accuracy) {
    this->accuracy = accuracy;
}

/**
 * A constructor that sets the accuracy and errorRate via given input.
 *
 * @param accuracy  Double value input.
 * @param errorRate Double value input.
 */
ClassificationPerformance::ClassificationPerformance(double accuracy, double errorRate) : Performance(errorRate){
    this->accuracy = accuracy;
}

/**
 * Accessor for the accuracy.
 *
 * @return Accuracy value.
 */
double ClassificationPerformance::getAccuracy() const{
    return accuracy;
}

bool ClassificationPerformance::containsDetails() const{
    return false;
}

bool ClassificationPerformance::isClassification() const{
    return true;
}
