//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_KFOLDRUNSEPARATETEST_H
#define CLASSIFICATION_KFOLDRUNSEPARATETEST_H

#include "CrossValidation.h"
#include "KFoldRun.h"

class KFoldRunSeparateTest : public KFoldRun {
public:
    explicit KFoldRunSeparateTest(int K);
protected:
    void runExperiment(Classifier* classifier, Parameter* parameter, ExperimentPerformance* experimentPerformance, CrossValidation<Instance*>* crossValidation, InstanceList testSet);
    ExperimentPerformance* execute(Experiment experiment) override;
};


#endif //CLASSIFICATION_KFOLDRUNSEPARATETEST_H
