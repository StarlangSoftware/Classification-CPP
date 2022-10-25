//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_COMBINED5X2T_H
#define CLASSIFICATION_COMBINED5X2T_H


#include "PairedTest.h"

class Combined5x2t : public PairedTest{
private:
    double testStatistic(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2) const;
public:
    StatisticalTestResult compare(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2) const override;
};


#endif //CLASSIFICATION_COMBINED5X2T_H
