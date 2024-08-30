//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_KFOLDRUNSEPARATETEST_H
#define CLASSIFICATION_KFOLDRUNSEPARATETEST_H

#include "CrossValidation.h"
#include "KFoldRun.h"

class KFoldRunSeparateTest : virtual public KFoldRun {
public:
    explicit KFoldRunSeparateTest(int K);
    ExperimentPerformance* execute(const Experiment& experiment) override;
protected:
    void runExperiment(Model* model, Parameter* parameter, ExperimentPerformance* experimentPerformance, CrossValidation<Instance*>* crossValidation, const InstanceList& testSet);
};


#endif //CLASSIFICATION_KFOLDRUNSEPARATETEST_H
