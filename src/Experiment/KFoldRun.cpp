//
// Created by olcay on 6.02.2019.
//

#include "KFoldCrossValidation.h"
#include "KFoldRun.h"

/**
 * Constructor for KFoldRun class. Basically sets K parameter of the K-fold cross-validation.
 *
 * @param K K of the K-fold cross-validation.
 */
KFoldRun::KFoldRun(int K) {
    this->K = K;
}

void KFoldRun::runExperiment(Classifier *classifier, Parameter *parameter, ExperimentPerformance *experimentPerformance,
                             CrossValidation<Instance *>* crossValidation) {
    for (int i = 0; i < K; i++) {
        InstanceList trainSet = InstanceList(crossValidation->getTrainFold(i));
        InstanceList testSet = InstanceList(crossValidation->getTestFold(i));
        classifier->train(trainSet, parameter);
        experimentPerformance->add(classifier->test(testSet));
    }
}

/**
 * Execute K-fold cross-validation with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th fold.
 */
ExperimentPerformance *KFoldRun::execute(Experiment experiment) {
    auto* result = new ExperimentPerformance();
    auto* crossValidation = new KFoldCrossValidation<Instance*>(experiment.getDataSet().getInstances(), K, experiment.getParameter()->getSeed());
    runExperiment(experiment.getClassifier(), experiment.getParameter(), result, crossValidation);
    return result;
}
