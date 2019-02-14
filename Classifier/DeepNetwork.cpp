//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include "DeepNetwork.h"
#include "../InstanceList/Partition.h"
#include "../Parameter/DeepNetworkParameter.h"
#include "../Model/DeepNetworkModel.h"

/**
 * Training algorithm for deep network classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters Parameters of the deep network algorithm. crossValidationRatio and seed are used as parameters.
 * @throws DiscreteFeaturesNotAllowed Exception for discrete features.
 */
void DeepNetwork::train(InstanceList &trainSet, Parameter *parameters) {
    Partition partition = Partition(trainSet, ((DeepNetworkParameter*) parameters)->getCrossValidationRatio(), parameters->getSeed(), true);
    model = new DeepNetworkModel(*(partition.get(1)), *(partition.get(0)), (DeepNetworkParameter*) parameters);
}
