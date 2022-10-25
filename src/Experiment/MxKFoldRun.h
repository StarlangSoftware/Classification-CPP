//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_MXKFOLDRUN_H
#define CLASSIFICATION_MXKFOLDRUN_H
#include "KFoldRun.h"

class MxKFoldRun : virtual KFoldRun {
protected:
    int M;
public:
    MxKFoldRun(int M, int K);
    ExperimentPerformance* execute(const Experiment& experiment) override;
};


#endif //CLASSIFICATION_MXKFOLDRUN_H
