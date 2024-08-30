//
// Created by olcay on 6.02.2019.
//

#include "KFoldCrossValidation.h"
#include "MxKFoldRunSeparateTest.h"
#include "../InstanceList/Partition.h"

/**
 * Constructor for KFoldRunSeparateTest class. Basically sets K parameter of the K-fold cross-validation and M for the number of times..
 *
 * @param M number of cross-validation times.
 * @param K K of the K-fold cross-validation.
 */
MxKFoldRunSeparateTest::MxKFoldRunSeparateTest(int M, int K) : MxKFoldRun(M, K), KFoldRunSeparateTest(K), KFoldRun(K) {
}

/**
 * Execute the KFold run with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th bootstrap run.
 */
ExperimentPerformance *MxKFoldRunSeparateTest::execute(const Experiment& experiment) {
    auto* result = new ExperimentPerformance();
    InstanceList instanceList = experiment.getDataSet().getInstanceList();
    Partition partition = Partition(instanceList, 0.25, experiment.getParameter()->getSeed(), false);
    for (int j = 0; j < M; j++) {
        auto* crossValidation = new KFoldCrossValidation<Instance*>(partition.get(1)->getInstances(), KFoldRunSeparateTest::K, experiment.getParameter()->getSeed());
        KFoldRunSeparateTest::runExperiment(experiment.getModel(), experiment.getParameter(), result, crossValidation, *(partition.get(0)));
    }
    return result;
}
