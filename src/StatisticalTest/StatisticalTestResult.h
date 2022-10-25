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
    StatisticalTestResultType oneTailed(double alpha) const;
    StatisticalTestResultType twoTailed(double alpha) const;
    double getPValue() const;
};


#endif //CLASSIFICATION_STATISTICALTESTRESULT_H
