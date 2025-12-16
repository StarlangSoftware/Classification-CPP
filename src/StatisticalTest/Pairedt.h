//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_PAIREDT_H
#define CLASSIFICATION_PAIREDT_H
#include "PairedTest.h"

class Pairedt : public PairedTest {
private:
    [[nodiscard]] double testStatistic(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2) const;
public:
    [[nodiscard]] StatisticalTestResult compare(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2) const override;
};


#endif //CLASSIFICATION_PAIREDT_H
