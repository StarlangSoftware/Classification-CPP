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
    [[nodiscard]] int numberOfExperiments() const;
    [[nodiscard]] double getErrorRate(int index) const;
    [[nodiscard]] double getAccuracy(int index) const;
    [[nodiscard]] Performance* meanPerformance() const;
    [[nodiscard]] ClassificationPerformance* meanClassificationPerformance() const;
    [[nodiscard]] DetailedClassificationPerformance* meanDetailedPerformance() const;
    [[nodiscard]] Performance* standardDeviationPerformance() const;
    [[nodiscard]] ClassificationPerformance* standardDeviationClassificationPerformance() const;
    bool isBetter(ExperimentPerformance* experimentPerformance) const;
};


#endif //CLASSIFICATION_EXPERIMENTPERFORMANCE_H
