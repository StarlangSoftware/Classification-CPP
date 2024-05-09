//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include <fstream>
#include "DeepNetwork.h"
#include "../InstanceList/Partition.h"
#include "../Parameter/DeepNetworkParameter.h"
#include "../Model/DeepNetworkModel.h"
#include "DiscreteFeaturesNotAllowed.h"

/**
 * Training algorithm for deep network classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters Parameters of the deep network algorithm. crossValidationRatio and seed are used as parameters.
 * @throws DiscreteFeaturesNotAllowed Exception for discrete features.
 */
void DeepNetwork::train(InstanceList &trainSet, Parameter *parameters) {
    if (!discreteCheck(trainSet.get(0))){
        throw DiscreteFeaturesNotAllowed();
    }
    Partition partition = Partition(trainSet, ((DeepNetworkParameter*) parameters)->getCrossValidationRatio(), parameters->getSeed(), true);
    model = new DeepNetworkModel(*(partition.get(1)), *(partition.get(0)), (DeepNetworkParameter*) parameters);
}

/**
 * Loads the deep network model from an input file.
 * @param fileName File name of the deep network model.
 */
void DeepNetwork::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new DeepNetworkModel(inputFile);
    inputFile.close();
}
