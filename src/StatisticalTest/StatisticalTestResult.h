//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_STATISTICALTESTRESULT_H
#define CLASSIFICATION_STATISTICALTESTRESULT_H


#include "StatisticalTestResultType.h"

class StatisticalTestResult {
private:
    double pValue;
    bool onlyTwoTailed;
public:
    StatisticalTestResult(double pValue, bool onlyTwoTailed);
    [[nodiscard]] StatisticalTestResultType oneTailed(double alpha) const;
    [[nodiscard]] StatisticalTestResultType twoTailed(double alpha) const;
    [[nodiscard]] double getPValue() const;
};


#endif //CLASSIFICATION_STATISTICALTESTRESULT_H
