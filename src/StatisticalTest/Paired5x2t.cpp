//
// Created by olcay on 31.01.2019.
//
#include <cmath>
#include "Distribution.h"
#include "StatisticalTestNotApplicable.h"
#include "Paired5x2t.h"

double Paired5x2t::testStatistic(ExperimentPerformance classifier1, ExperimentPerformance classifier2) {
    if (classifier1.numberOfExperiments() != classifier2.numberOfExperiments()){
        throw StatisticalTestNotApplicable("5x2 t test", "In order to apply a paired test, you need to have the same number of experiments in both algorithms.");
    }
    if (classifier1.numberOfExperiments() != 10){
        throw StatisticalTestNotApplicable("5x2 t test", "In order to apply a 5x2 test, you need to have 10 experiments.");
    }
    double* difference;
    difference = new double[classifier1.numberOfExperiments()];
    for (int i = 0; i < classifier1.numberOfExperiments(); i++){
        difference[i] = classifier1.getErrorRate(i) - classifier2.getErrorRate(i);
    }
    double denominator = 0;
    for (int i = 0; i < classifier1.numberOfExperiments() / 2; i++){
        double mean = (difference[2 * i] + difference[2 * i + 1]) / 2;
        double variance = (difference[2 * i] - mean) * (difference[2 * i] - mean) + (difference[2 * i + 1] - mean) * (difference[2 * i + 1] - mean);
        denominator += variance;
    }
    delete difference;
    denominator = sqrt(denominator / 5);
    if (denominator == 0){
        throw StatisticalTestNotApplicable("5x2 t test", "Variance is 0.");
    }
    return difference[0] / denominator;
}

StatisticalTestResult Paired5x2t::compare(ExperimentPerformance classifier1, ExperimentPerformance classifier2) {
    double statistic = testStatistic(classifier1, classifier2);
    int degreeOfFreedom = classifier1.numberOfExperiments() / 2;
    return StatisticalTestResult(Distribution::tDistribution(statistic, degreeOfFreedom), false);
}
