//
// Created by Olcay Taner Yıldız on 7.02.2019.
//

#ifndef CLASSIFICATION_STRATIFIEDKFOLDRUNSEPARATETEST_H
#define CLASSIFICATION_STRATIFIEDKFOLDRUNSEPARATETEST_H

#include "StratifiedKFoldRun.h"
#include "KFoldRunSeparateTest.h"

class StratifiedKFoldRunSeparateTest : public StratifiedKFoldRun, public KFoldRunSeparateTest {
public:
    explicit StratifiedKFoldRunSeparateTest(int K);
    ExperimentPerformance* execute(Experiment experiment) override;
};


#endif //CLASSIFICATION_STRATIFIEDKFOLDRUNSEPARATETEST_H
