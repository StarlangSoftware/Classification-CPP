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
    ExperimentPerformance* execute(Experiment experiment) override;
protected:
    void runExperiment(Classifier* classifier, Parameter* parameter, ExperimentPerformance* experimentPerformance, CrossValidation<Instance*>* crossValidation, InstanceList testSet);
};


#endif //CLASSIFICATION_KFOLDRUNSEPARATETEST_H
