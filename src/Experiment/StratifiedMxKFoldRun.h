//
// Created by Olcay Taner Yıldız on 7.02.2019.
//

#ifndef CLASSIFICATION_STRATIFIEDMXKFOLDRUN_H
#define CLASSIFICATION_STRATIFIEDMXKFOLDRUN_H


#include "MxKFoldRun.h"
#include "StratifiedKFoldRun.h"

class StratifiedMxKFoldRun : public MxKFoldRun, public StratifiedKFoldRun{
public:
    StratifiedMxKFoldRun(int M, int K);
    ExperimentPerformance* execute(const Experiment& experiment) override;
};


#endif //CLASSIFICATION_STRATIFIEDMXKFOLDRUN_H
