//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_KFOLDRUN_H
#define CLASSIFICATION_KFOLDRUN_H

#include "MultipleRun.h"
#include "CrossValidation.h"

class KFoldRun : public MultipleRun{
protected:
    int K;
    void runExperiment(Classifier* classifier, Parameter* parameter, ExperimentPerformance* experimentPerformance, CrossValidation<Instance*>* crossValidation);
public:
    KFoldRun(int K);
    ExperimentPerformance* execute(Experiment experiment);
};


#endif //CLASSIFICATION_KFOLDRUN_H
