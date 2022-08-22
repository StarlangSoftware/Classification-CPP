//
// Created by olcay on 6.02.2019.
//

#include <KFoldCrossValidation.h>
#include "MxKFoldRun.h"

/**
 * Constructor for MxKFoldRun class. Basically sets K parameter of the K-fold cross-validation and M for the number of times.
 *
 * @param M number of cross-validation times.
 * @param K K of the K-fold cross-validation.
 */
MxKFoldRun::MxKFoldRun(int M, int K) : KFoldRun(K){
    this->M = M;
}

/**
 * Execute the MxKFold run with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th bootstrap run.
 */
ExperimentPerformance *MxKFoldRun::execute(Experiment experiment) {
    ExperimentPerformance* result = new ExperimentPerformance();
    for (int j = 0; j < M; j++) {
        KFoldCrossValidation<Instance*>* crossValidation = new KFoldCrossValidation<Instance*>(experiment.getDataSet().getInstances(), K, experiment.getParameter()->getSeed());
        runExperiment(experiment.getClassifier(), experiment.getParameter(), result, crossValidation);
    }
    return result;
}
