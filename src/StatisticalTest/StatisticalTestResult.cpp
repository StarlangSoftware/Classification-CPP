//
// Created by olcay on 31.01.2019.
//

#include "StatisticalTestResult.h"
#include "StatisticalTestNotApplicable.h"

StatisticalTestResult::StatisticalTestResult(double pValue, bool onlyTwoTailed) {
    this->pValue = pValue;
    this->onlyTwoTailed = onlyTwoTailed;
}

StatisticalTestResultType StatisticalTestResult::oneTailed(double alpha) const{
    if (onlyTwoTailed){
        throw StatisticalTestNotApplicable("The test", "One tailed option is not available for this test. The distribution is one tailed distribution.");
    }
    if (pValue < alpha){
        return StatisticalTestResultType::REJECT;
    } else {
        return StatisticalTestResultType::FAILED_TO_REJECT;
    }
}

StatisticalTestResultType StatisticalTestResult::twoTailed(double alpha) const{
    if (onlyTwoTailed){
        if (pValue < alpha){
            return StatisticalTestResultType::REJECT;
        } else {
            return StatisticalTestResultType::FAILED_TO_REJECT;
        }
    } else {
        if (pValue < alpha / 2 || pValue > 1 - alpha / 2){
            return StatisticalTestResultType::REJECT;
        } else {
            return StatisticalTestResultType::FAILED_TO_REJECT;
        }
    }
}

double StatisticalTestResult::getPValue() const{
    return pValue;
}
