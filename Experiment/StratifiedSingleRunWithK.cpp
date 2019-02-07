//
// Created by Olcay Taner Yıldız on 7.02.2019.
//

#include <StratifiedKFoldCrossValidation.h>
#include "StratifiedSingleRunWithK.h"

/**
 * Constructor for StratifiedSingleRunWithK class. Basically sets K parameter of the K-fold cross-validation.
 *
 * @param K K of the K-fold cross-validation.
 */
StratifiedSingleRunWithK::StratifiedSingleRunWithK(int K) : SingleRunWithK(K) {
}

/**
 * Execute Stratified Single K-fold cross-validation with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th fold.
 * @throws DiscreteFeaturesNotAllowed Exception for discrete features.
 */
Performance *StratifiedSingleRunWithK::execute(Experiment experiment) {
    StratifiedKFoldCrossValidation<Instance*>* crossValidation = new StratifiedKFoldCrossValidation<Instance*>(experiment.getDataSet().getClassInstances(), SingleRunWithK::K, SingleRunWithK::K, experiment.getParameter()->getSeed());
    InstanceList trainSet = InstanceList(crossValidation->getTrainFold(0));
    InstanceList testSet = InstanceList(crossValidation->getTestFold(0));
    return experiment.getClassifier()->singleRun(experiment.getParameter(), trainSet, testSet);
}
