//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_PAIREDTEST_H
#define CLASSIFICATION_PAIREDTEST_H

#include "StatisticalTestResult.h"
#include "../Performance/ExperimentPerformance.h"

class PairedTest {
public:
    [[nodiscard]] virtual StatisticalTestResult compare(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2) const = 0;
    [[nodiscard]] int compare(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2, double alpha) const;
};


#endif //CLASSIFICATION_PAIREDTEST_H
