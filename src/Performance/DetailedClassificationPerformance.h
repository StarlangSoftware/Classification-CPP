//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_DETAILEDCLASSIFICATIONPERFORMANCE_H
#define CLASSIFICATION_DETAILEDCLASSIFICATIONPERFORMANCE_H


#include "ClassificationPerformance.h"
#include "ConfusionMatrix.h"

class DetailedClassificationPerformance : public ClassificationPerformance {
private:
    ConfusionMatrix confusionMatrix = ConfusionMatrix();
public:
    explicit DetailedClassificationPerformance(ConfusionMatrix confusionMatrix);
    ConfusionMatrix getConfusionMatrix() const;
    bool containsDetails() const override;
};


#endif //CLASSIFICATION_DETAILEDCLASSIFICATIONPERFORMANCE_H
