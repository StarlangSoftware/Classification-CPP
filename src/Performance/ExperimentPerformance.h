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
    explicit ExperimentPerformance(const string& fileName);
    void add(Performance* performance);
    int numberOfExperiments() const;
    double getErrorRate(int index) const;
    double getAccuracy(int index) const;
    Performance* meanPerformance() const;
    ClassificationPerformance* meanClassificationPerformance() const;
    DetailedClassificationPerformance* meanDetailedPerformance() const;
    Performance* standardDeviationPerformance() const;
    ClassificationPerformance* standardDeviationClassificationPerformance() const;
    bool isBetter(ExperimentPerformance* experimentPerformance) const;
};


#endif //CLASSIFICATION_EXPERIMENTPERFORMANCE_H
