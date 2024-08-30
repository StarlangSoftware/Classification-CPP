//
// Created by olcay on 6.02.2019.
//

#include "KFoldCrossValidation.h"
#include "SingleRunWithK.h"

/**
 * Constructor for SingleRunWithK class. Basically sets K parameter of the K-fold cross-validation.
 *
 * @param K K of the K-fold cross-validation.
 */
SingleRunWithK::SingleRunWithK(int K) {
    this->K = K;
}

/**
 * Runs first fold of a K fold cross-validated experiment for the given classifier with the given parameters.
 * The experiment result will be returned.
 * @param classifier Classifier for the experiment
 * @param parameter Hyperparameters of the classifier of the experiment
 * @param crossValidation K-fold crossvalidated dataset.
 * @return The experiment result of the first fold of the K-fold cross-validated experiment.
 */
Performance *SingleRunWithK::runExperiment(Model *classifier, Parameter *parameter,
                                           CrossValidation<Instance *> *crossValidation) {
    InstanceList trainSet = InstanceList(crossValidation->getTrainFold(0));
    InstanceList testSet = InstanceList(crossValidation->getTestFold(0));
    return classifier->singleRun(parameter, trainSet, testSet);
}

/**
 * Execute Single K-fold cross-validation with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th fold.
 */
Performance *SingleRunWithK::execute(const Experiment& experiment) {
    auto* crossValidation = new KFoldCrossValidation<Instance*>(experiment.getDataSet().getInstances(), K, experiment.getParameter()->getSeed());
    return runExperiment(experiment.getModel(), experiment.getParameter(), crossValidation);
}
