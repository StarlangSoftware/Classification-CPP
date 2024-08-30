//
// Created by olcay on 6.02.2019.
//

#include "BootstrapRun.h"
#include "Bootstrap.h"

/**
 * Constructor for BootstrapRun class. Basically sets the number of bootstrap runs.
 *
 * @param numberOfBootstraps Number of bootstrap runs.
 */
BootstrapRun::BootstrapRun(int numberOfBootstraps) {
    this->numberOfBootstraps = numberOfBootstraps;
}

/**
 * Execute the bootstrap run with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th bootstrap run.
 */
ExperimentPerformance* BootstrapRun::execute(const Experiment& experiment) {
    auto* result = new ExperimentPerformance();
    for (int i = 0; i < numberOfBootstraps; i++) {
        Bootstrap<Instance*> bootstrap = Bootstrap<Instance*>(experiment.getDataSet().getInstances(), i + experiment.getParameter()->getSeed());
        InstanceList bootstrapSample = InstanceList(bootstrap.getSample());
        experiment.getModel()->train(bootstrapSample, experiment.getParameter());
        result->add(experiment.getModel()->test(experiment.getDataSet().getInstanceList()));
    }
    return result;
}
