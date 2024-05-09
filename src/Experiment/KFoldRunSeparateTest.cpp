//
// Created by olcay on 6.02.2019.
//

#include "KFoldCrossValidation.h"
#include "KFoldRunSeparateTest.h"
#include "../InstanceList/Partition.h"

/**
 * Constructor for KFoldRunSeparateTest class. Basically sets K parameter of the K-fold cross-validation.
 *
 * @param K K of the K-fold cross-validation.
 */
KFoldRunSeparateTest::KFoldRunSeparateTest(int K) : KFoldRun(K) {
}

/**
 * Runs a K fold cross-validated experiment for the given classifier with the given parameters. Testing will be
 * done on the separate test set. The experiment results will be added to the experimentPerformance.
 * @param classifier Classifier for the experiment
 * @param parameter Hyperparameters of the classifier of the experiment
 * @param experimentPerformance Storage to add experiment results
 * @param crossValidation K-fold crossvalidated dataset.
 * @param testSet Test set on which experiment performance is calculated.
 */
void KFoldRunSeparateTest::runExperiment(Classifier* classifier, Parameter *parameter,
                                         ExperimentPerformance *experimentPerformance,
                                         CrossValidation<Instance *>* crossValidation, const InstanceList& testSet) {
    for (int i = 0; i < K; i++) {
        InstanceList trainSet = InstanceList(crossValidation->getTrainFold(i));
        classifier->train(trainSet, parameter);
        experimentPerformance->add(classifier->test(testSet));
    }
}

/**
 * Execute K-fold cross-validation with separate test set with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th fold.
 */
ExperimentPerformance *KFoldRunSeparateTest::execute(const Experiment& experiment) {
    auto* result = new ExperimentPerformance();
    InstanceList instanceList = experiment.getDataSet().getInstanceList();
    Partition partition = Partition(instanceList, 0.25, experiment.getParameter()->getSeed(), false);
    auto* crossValidation = new KFoldCrossValidation<Instance*>(partition.get(1)->getInstances(), K, experiment.getParameter()->getSeed());
    runExperiment(experiment.getClassifier(), experiment.getParameter(), result, crossValidation, *(partition.get(0)));
    return result;
}
