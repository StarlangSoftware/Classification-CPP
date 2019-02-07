//
// Created by Olcay Taner Yıldız on 7.02.2019.
//

#ifndef CLASSIFICATION_STRATIFIEDMXKFOLDRUNSEPARATETEST_H
#define CLASSIFICATION_STRATIFIEDMXKFOLDRUNSEPARATETEST_H


#include "StratifiedMxKFoldRun.h"
#include "StratifiedKFoldRunSeparateTest.h"

class StratifiedMxKFoldRunSeparateTest : public StratifiedMxKFoldRun, public StratifiedKFoldRunSeparateTest {
public:
    StratifiedMxKFoldRunSeparateTest(int M, int K);
    ExperimentPerformance* execute(Experiment experiment);
};


#endif //CLASSIFICATION_STRATIFIEDMXKFOLDRUNSEPARATETEST_H
