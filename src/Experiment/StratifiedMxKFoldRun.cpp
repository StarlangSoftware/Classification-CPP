//
// Created by Olcay Taner Yıldız on 7.02.2019.
//

#include "StratifiedMxKFoldRun.h"
#include "StratifiedKFoldCrossValidation.h"

/**
 * Constructor for StratifiedMxKFoldRun class. Basically sets K parameter of the K-fold cross-validation and M for the number of times.
 *
 * @param M number of cross-validation times.
 * @param K K of the K-fold cross-validation.
 */
StratifiedMxKFoldRun::StratifiedMxKFoldRun(int M, int K) : MxKFoldRun(M, K), StratifiedKFoldRun(K), KFoldRun(K) {
}

/**
 * Execute the Stratified MxK-fold cross-validation with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th bootstrap run.
 */
ExperimentPerformance *StratifiedMxKFoldRun::execute(Experiment experiment) {
    auto* result = new ExperimentPerformance();
    for (int j = 0; j < M; j++) {
        Partition partition = experiment.getDataSet().getClassInstances();
        auto* crossValidation = new StratifiedKFoldCrossValidation<Instance*>(partition.getLists(), partition.size(), StratifiedKFoldRun::K, experiment.getParameter()->getSeed());
        KFoldRun::runExperiment(experiment.getClassifier(), experiment.getParameter(), result, crossValidation);
    }
    return result;
}
