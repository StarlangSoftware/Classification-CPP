//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#include "KnnParameter.h"

/**
 * Parameters of the K-nearest neighbor classifier.
 *
 * @param seed           Seed is used for random number generation.
 * @param k              Parameter of the K-nearest neighbor algorithm.
 * @param distanceMetric Used to calculate the distance between two instances.
 */
KnnParameter::KnnParameter(int seed, int k, DistanceMetric *distanceMetric) : KMeansParameter(seed, distanceMetric){
    this->k = k;
}

/**
 * Parameters of the K-nearest neighbor classifier.
 *
 * @param seed           Seed is used for random number generation.
 * @param k              Parameter of the K-nearest neighbor algorithm.
 */
KnnParameter::KnnParameter(int seed, int k) : KMeansParameter(seed){
    this->k = k;
}

/**
 * Accessor for the k.
 *
 * @return Value of the k.
 */
int KnnParameter::getK() {
    return k;
}
