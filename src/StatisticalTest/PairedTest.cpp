//
// Created by olcay on 31.01.2019.
//

#include "PairedTest.h"

int PairedTest::compare(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2, double alpha) const{
    StatisticalTestResult testResult1 = compare(classifier1, classifier2);
    StatisticalTestResult testResult2 = compare(classifier2, classifier1);
    StatisticalTestResultType testResultType1 = testResult1.oneTailed(alpha);
    StatisticalTestResultType testResultType2 = testResult2.oneTailed(alpha);
    if (testResultType1 == StatisticalTestResultType::REJECT){
        return 1;
    } else {
        if (testResultType2 == StatisticalTestResultType::REJECT){
            return -1;
        } else {
            return 0;
        }
    }
}
