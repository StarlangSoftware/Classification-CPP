//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#include "KMeansParameter.h"
#include "../DistanceMetric/EuclidianDistance.h"

/**
 * Parameters of the Rocchio classifier.
 *
 * @param seed Seed is used for random number generation.
 */
KMeansParameter::KMeansParameter(int seed) : Parameter(seed) {
    distanceMetric = new EuclidianDistance();
}

/**
 * * Parameters of the Rocchio classifier.
 *
 * @param seed           Seed is used for random number generation.
 * @param distanceMetric distance metric used to calculate the distance between two instances.
 */
KMeansParameter::KMeansParameter(int seed, DistanceMetric* distanceMetric) : Parameter(seed){
    this->distanceMetric = distanceMetric;
}

/**
 * Accessor for the distanceMetric.
 *
 * @return The distanceMetric.
 */
DistanceMetric *KMeansParameter::getDistanceMetric() {
    return distanceMetric;
}
