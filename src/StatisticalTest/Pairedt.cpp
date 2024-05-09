//
// Created by olcay on 31.01.2019.
//
#include <cmath>
#include "Distribution.h"
#include "Pairedt.h"
#include "StatisticalTestNotApplicable.h"

/**
 * Calculates the test statistic of the paired t test.
 * @param classifier1 Performance (error rate or accuracy) results of the first classifier.
 * @param classifier2 Performance (error rate or accuracy) results of the second classifier.
 * @return Given the performances of two classifiers, the test statistic of the paired t test.
 */
double Pairedt::testStatistic(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2) const{
    if (classifier1.numberOfExperiments() != classifier2.numberOfExperiments()){
        throw StatisticalTestNotApplicable("Paired test", "In order to apply a paired test, you need to have the same number of experiments in both algorithms.");
    }
    double* difference;
    difference = new double[classifier1.numberOfExperiments()];
    double sum = 0.0;
    for (int i = 0; i < classifier1.numberOfExperiments(); i++){
        difference[i] = classifier1.getErrorRate(i) - classifier2.getErrorRate(i);
        sum += difference[i];
    }
    double mean = sum / classifier1.numberOfExperiments();
    sum = 0.0;
    for (int i = 0; i < classifier1.numberOfExperiments(); i++){
        sum += (difference[i] - mean) * (difference[i] - mean);
    }
    delete difference;
    double standardDeviation = sqrt(sum / (classifier1.numberOfExperiments() - 1));
    if (standardDeviation == 0){
        throw StatisticalTestNotApplicable("Paired t test", "Variance is 0.");
    }
    return sqrt(classifier1.numberOfExperiments()) * mean / standardDeviation;
}

/**
 * Compares two classification algorithms based on their performances (accuracy or error rate) using paired t test.
 * @param classifier1 Performance (error rate or accuracy) results of the first classifier.
 * @param classifier2 Performance (error rate or accuracy) results of the second classifier.
 * @return Statistical test result of the comparison.
 */
StatisticalTestResult Pairedt::compare(const ExperimentPerformance& classifier1, const ExperimentPerformance& classifier2) const{
    double statistic = testStatistic(classifier1, classifier2);
    int degreeOfFreedom = classifier1.numberOfExperiments() - 1;
    return StatisticalTestResult(Distribution::tDistribution(statistic, degreeOfFreedom), false);
}
