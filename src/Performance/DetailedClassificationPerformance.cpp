//
// Created by olcay on 31.01.2019.
//

#include "DetailedClassificationPerformance.h"
#include "ConfusionMatrix.h"

/**
 * A constructor that  sets the accuracy and errorRate as 1 - accuracy via given {@link ConfusionMatrix} and also sets the confusionMatrix.
 *
 * @param confusionMatrix {@link ConfusionMatrix} input.
 */
DetailedClassificationPerformance::DetailedClassificationPerformance(ConfusionMatrix confusionMatrix) : ClassificationPerformance(confusionMatrix.getAccuracy()) {
    this->confusionMatrix = confusionMatrix;
}

/**
 * Accessor for the confusionMatrix.
 *
 * @return ConfusionMatrix.
 */
ConfusionMatrix DetailedClassificationPerformance::getConfusionMatrix() {
    return confusionMatrix;
}

bool DetailedClassificationPerformance::containsDetails() {
    return true;
}
