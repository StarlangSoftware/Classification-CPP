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
    ClassificationPerformance(double accuracy);
    ClassificationPerformance(double accuracy, double errorRate);
    double getAccuracy();
    bool containsDetails();
    bool isClassification();
};


#endif //CLASSIFICATION_CLASSIFICATIONPERFORMANCE_H
