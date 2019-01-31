//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_SIGN_H
#define CLASSIFICATION_SIGN_H


#include "PairedTest.h"

class Sign : public PairedTest{
private:
    int factorial(int n);
    int binomial(int m, int n);
    StatisticalTestResult compare(ExperimentPerformance classifier1, ExperimentPerformance classifier2) override;
};


#endif //CLASSIFICATION_SIGN_H
