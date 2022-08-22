//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include "AutoEncoder.h"
#include "../InstanceList/Partition.h"
#include "../Model/AutoEncoderModel.h"
#include "DiscreteFeaturesNotAllowed.h"

/**
 * Training algorithm for auto encoders. An auto encoder is a neural network which attempts to replicate its input at its output.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters Parameters of the auto encoder.
 * @throws DiscreteFeaturesNotAllowed Exception for discrete features.
 */
void AutoEncoder::train(InstanceList &trainSet, Parameter *parameters) {
    if (!discreteCheck(trainSet.get(0))){
        throw DiscreteFeaturesNotAllowed();
    }
    Partition partition = Partition(trainSet, 0.2, parameters->getSeed(), true);
    model = new AutoEncoderModel(*(partition.get(1)), *(partition.get(0)), (MultiLayerPerceptronParameter*) parameters);
}

/**
 * A performance test for an auto encoder with the given test set..
 *
 * @param testSet Test data (list of instances) to be tested.
 * @return Error rate.
 */
Performance *AutoEncoder::test(InstanceList testSet) {
    return ((AutoEncoderModel*) model)->testAutoEncoder(testSet);
}
