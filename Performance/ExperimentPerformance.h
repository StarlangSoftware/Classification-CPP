//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_EXPERIMENTPERFORMANCE_H
#define CLASSIFICATION_EXPERIMENTPERFORMANCE_H

#include <vector>
#include "Performance.h"
#include "ClassificationPerformance.h"
#include "DetailedClassificationPerformance.h"

using namespace std;

class ExperimentPerformance {
private:
    vector<Performance*> results;
    bool containsDetails = true;
    bool classification = true;
public:
    ExperimentPerformance();
    ExperimentPerformance(string fileName);
    void add(Performance* performance);
    int numberOfExperiments();
    double getErrorRate(int index);
    double getAccuracy(int index);
    Performance* meanPerformance();
    ClassificationPerformance* meanClassificationPerformance();
    DetailedClassificationPerformance* meanDetailedPerformance();
    Performance* standardDeviationPerformance();
    ClassificationPerformance* standardDeviationClassificationPerformance();
    bool isBetter(ExperimentPerformance experimentPerformance);
};


#endif //CLASSIFICATION_EXPERIMENTPERFORMANCE_H
