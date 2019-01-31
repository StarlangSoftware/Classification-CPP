//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_PAIRED5X2T_H
#define CLASSIFICATION_PAIRED5X2T_H

#include "PairedTest.h"

class Paired5x2t : public PairedTest{
private:
    double testStatistic(ExperimentPerformance classifier1, ExperimentPerformance classifier2);
public:
    StatisticalTestResult compare(ExperimentPerformance classifier1, ExperimentPerformance classifier2) override;
};


#endif //CLASSIFICATION_PAIRED5X2T_H
