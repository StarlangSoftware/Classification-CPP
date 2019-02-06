//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_STRATIFIEDKFOLDRUN_H
#define CLASSIFICATION_STRATIFIEDKFOLDRUN_H

#include "KFoldRun.h"
#include "MultipleRun.h"

class StratifiedKFoldRun : public KFoldRun {
public:
    explicit StratifiedKFoldRun(int K);
    ExperimentPerformance* execute(Experiment experiment) override;
};


#endif //CLASSIFICATION_STRATIFIEDKFOLDRUN_H
