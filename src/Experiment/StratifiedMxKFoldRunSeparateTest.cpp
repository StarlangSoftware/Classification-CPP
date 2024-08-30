//
// Created by Olcay Taner Yıldız on 7.02.2019.
//

#include <StratifiedKFoldCrossValidation.h>
#include "StratifiedMxKFoldRunSeparateTest.h"

/**
 * Constructor for StratifiedMxKFoldRunSeparateTest class. Basically sets K parameter of the K-fold cross-validation and M for the number of times.
 *
 * @param M number of cross-validation times.
 * @param K K of the K-fold cross-validation.
 */
StratifiedMxKFoldRunSeparateTest::StratifiedMxKFoldRunSeparateTest(int M, int K) : StratifiedMxKFoldRun(M, K), StratifiedKFoldRunSeparateTest(K), KFoldRun(K) {
}

/**
 * Execute the Stratified MxK-fold cross-validation with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th bootstrap run.
 */
ExperimentPerformance *StratifiedMxKFoldRunSeparateTest::execute(const Experiment& experiment) {
    auto * result = new ExperimentPerformance();
    InstanceList instanceList = experiment.getDataSet().getInstanceList();
    Partition partition = Partition(instanceList, 0.25, experiment.getParameter()->getSeed(), true);
    for (int j = 0; j < M; j++) {
        Partition classPartition = Partition(*(partition.get(1)));
        auto* crossValidation = new StratifiedKFoldCrossValidation<Instance*>(classPartition.getLists(), classPartition.size(), StratifiedKFoldRunSeparateTest::K, experiment.getParameter()->getSeed());
        runExperiment(experiment.getModel(), experiment.getParameter(), result, crossValidation, *(partition.get(0)));
    }
    return result;
}
