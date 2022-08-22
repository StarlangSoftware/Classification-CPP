//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_CLASSIFICATIONPERFORMANCE_H
#define CLASSIFICATION_CLASSIFICATIONPERFORMANCE_H
#include "Performance.h"

class ClassificationPerformance : public Performance {
private:
    double accuracy;
public:
    explicit ClassificationPerformance(double accuracy);
    ClassificationPerformance(double accuracy, double errorRate);
    double getAccuracy();
    bool containsDetails() override;
    bool isClassification() override;
};


#endif //CLASSIFICATION_CLASSIFICATIONPERFORMANCE_H
