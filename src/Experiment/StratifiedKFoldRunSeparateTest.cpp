//
// Created by Olcay Taner Yıldız on 7.02.2019.
//

#include <StratifiedKFoldCrossValidation.h>
#include "StratifiedKFoldRunSeparateTest.h"
#include "../InstanceList/Partition.h"

/**
 * Constructor for StratifiedKFoldRunSeparateTest class. Basically sets K parameter of the K-fold cross-validation.
 *
 * @param K K of the K-fold cross-validation.
 */
StratifiedKFoldRunSeparateTest::StratifiedKFoldRunSeparateTest(int K) : StratifiedKFoldRun(K), KFoldRunSeparateTest(K), KFoldRun(K) {
}

/**
 * Execute Stratified K-fold cross-validation with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th fold.
 * @throws DiscreteFeaturesNotAllowed Exception for discrete features.
 */
ExperimentPerformance *StratifiedKFoldRunSeparateTest::execute(const Experiment& experiment) {
    auto* result = new ExperimentPerformance();
    InstanceList instanceList = experiment.getDataSet().getInstanceList();
    Partition partition = Partition(instanceList, 0.25, experiment.getParameter()->getSeed(), true);
    Partition classPartition = Partition(*(partition.get(1)));
    auto* crossValidation = new StratifiedKFoldCrossValidation<Instance*>(classPartition.getLists(), classPartition.size(), StratifiedKFoldRun::K, experiment.getParameter()->getSeed());
    KFoldRunSeparateTest::runExperiment(experiment.getClassifier(), experiment.getParameter(), result, crossValidation, *(partition.get(0)));
    return result;
}
