//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_PAIREDTEST_H
#define CLASSIFICATION_PAIREDTEST_H

#include "StatisticalTestResult.h"
#include "../Performance/ExperimentPerformance.h"

class PairedTest {
public:
    virtual StatisticalTestResult compare(ExperimentPerformance classifier1, ExperimentPerformance classifier2) = 0;
    int compare(ExperimentPerformance classifier1, ExperimentPerformance classifier2, double alpha);
};


#endif //CLASSIFICATION_PAIREDTEST_H
