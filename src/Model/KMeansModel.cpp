//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#include <cfloat>
#include "KMeansModel.h"

/**
 * The constructor that sets the classMeans, priorDistribution and distanceMetric according to given inputs.
 *
 * @param priorDistribution {@link DiscreteDistribution} input.
 * @param classMeans        {@link InstanceList} of class means.
 * @param distanceMetric    {@link DistanceMetric} input.
 */
KMeansModel::KMeansModel(DiscreteDistribution priorDistribution, InstanceList &classMeans,
                         DistanceMetric *distanceMetric) {
    this->classMeans = classMeans;
    this->priorDistribution = move(priorDistribution);
    this->distanceMetric = distanceMetric;
}

/**
 * The calculateMetric method takes an {@link Instance} and a String as inputs. It loops through the class means, if
 * the corresponding class label is same as the given String it returns the negated distance between given instance and the
 * current item of class means. Otherwise it returns the smallest negative number.
 *
 * @param instance {@link Instance} input.
 * @param Ci       String input.
 * @return The negated distance between given instance and the current item of class means.
 */
double KMeansModel::calculateMetric(Instance *instance, string Ci) {
    for (int i = 0; i < classMeans.size(); i++) {
        if (classMeans.get(i)->getClassLabel() == Ci) {
            return -distanceMetric->distance(instance, classMeans.get(i));
        }
    }
    return -DBL_MAX;
}

void KMeansModel::serialize(ostream &outputFile) {
    GaussianModel::serialize(outputFile);
    classMeans.serialize(outputFile);
}

KMeansModel::KMeansModel(ifstream &inputFile) : GaussianModel(inputFile) {
    classMeans = InstanceList(inputFile);
}
