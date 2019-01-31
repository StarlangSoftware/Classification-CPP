//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_COMBINED5X2F_H
#define CLASSIFICATION_COMBINED5X2F_H


#include "PairedTest.h"

class Combined5x2f : public PairedTest{
private:
    double testStatistic(ExperimentPerformance classifier1, ExperimentPerformance classifier2);
public:
    StatisticalTestResult compare(ExperimentPerformance classifier1, ExperimentPerformance classifier2);
};


#endif //CLASSIFICATION_COMBINED5X2F_H
