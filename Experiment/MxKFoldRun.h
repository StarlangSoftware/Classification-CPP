//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_MXKFOLDRUN_H
#define CLASSIFICATION_MXKFOLDRUN_H
#include "KFoldRun.h"

class MxKFoldRun : KFoldRun {
protected:
    int M;
public:
    MxKFoldRun(int M, int K);
    ExperimentPerformance* execute(Experiment experiment) override;
};


#endif //CLASSIFICATION_MXKFOLDRUN_H
