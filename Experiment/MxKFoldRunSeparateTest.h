//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_MXKFOLDRUNSEPARATETEST_H
#define CLASSIFICATION_MXKFOLDRUNSEPARATETEST_H


#include "MxKFoldRun.h"
#include "KFoldRunSeparateTest.h"

class MxKFoldRunSeparateTest : public MxKFoldRun, public KFoldRunSeparateTest {
public:
    MxKFoldRunSeparateTest(int M, int K);
    ExperimentPerformance* execute(Experiment experiment);
};


#endif //CLASSIFICATION_MXKFOLDRUNSEPARATETEST_H
