//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_SIGN_H
#define CLASSIFICATION_SIGN_H


#include "PairedTest.h"

class Sign : public PairedTest{
private:
    [[nodiscard]] int factorial(int n) const;
    [[nodiscard]] int binomial(int m, int n) const;
    [[nodiscard]] StatisticalTestResult compare(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2) const override;
};


#endif //CLASSIFICATION_SIGN_H
