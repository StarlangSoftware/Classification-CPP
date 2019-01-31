//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_PAIREDT_H
#define CLASSIFICATION_PAIREDT_H
#include "PairedTest.h"

class Pairedt : public PairedTest {
private:
    double testStatistic(ExperimentPerformance classifier1, ExperimentPerformance classifier2);
public:
    StatisticalTestResult compare(ExperimentPerformance classifier1, ExperimentPerformance classifier2) override;
};


#endif //CLASSIFICATION_PAIREDT_H
