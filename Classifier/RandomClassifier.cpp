//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include "RandomClassifier.h"
#include "../Model/RandomModel.h"

/**
 * Training algorithm for random classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void RandomClassifier::train(InstanceList &trainSet, Parameter *parameters) {
    model = new RandomModel(trainSet.classDistribution().getItems());
}
