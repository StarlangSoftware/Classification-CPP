//
// Created by Olcay Taner Yıldız on 9.02.2019.
//
#include <cfloat>
#include "GaussianModel.h"

/**
 * The predict method takes an Instance as an input. First it gets the size of prior distribution and loops this size times.
 * Then it gets the possible class labels and and calculates metric value. At the end, it returns the class which has the
 * maximum value of metric.
 *
 * @param instance Instance to predict.
 * @return The class which has the maximum value of metric.
 */
string GaussianModel::predict(Instance *instance){
    string predictedClass;
    string Ci;
    vector<string> possibleLabels;
    double metric;
    double maxMetric = -DBL_MAX;
    int size;
    if (instance->isComposite()) {
        predictedClass = instance->getPossibleClassLabels().at(0);
        size = instance->getPossibleClassLabels().size();
    } else {
        predictedClass = priorDistribution.getMaxItem();
        size = priorDistribution.size();
        possibleLabels = priorDistribution.getItems();
    }
    for (int i = 0; i < size; i++) {
        if (instance->isComposite()) {
            Ci = instance->getPossibleClassLabels().at(i);
        } else {
            Ci = possibleLabels.at(i);
        }
        if (priorDistribution.contains(Ci)) {
            metric = calculateMetric(instance, Ci);
            if (metric > maxMetric) {
                maxMetric = metric;
                predictedClass = Ci;
            }
        }
    }
    return predictedClass;
}

/**
 * Saves the Gaussian model to an output file
 * @param outputFile Output file
 */
void GaussianModel::serialize(ostream &outputFile) {
    priorDistribution.serialize(outputFile);
}

/**
 * Loads a Gaussian mode from an input file
 * @param inputFile Input file
 */
GaussianModel::GaussianModel(ifstream &inputFile) {
    priorDistribution = DiscreteDistribution(inputFile);
}
