//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include <fstream>
#include "MultiLayerPerceptron.h"
#include "../InstanceList/Partition.h"
#include "../Parameter/MultiLayerPerceptronParameter.h"
#include "../Model/MultiLayerPerceptronModel.h"
#include "DiscreteFeaturesNotAllowed.h"

/**
 * Training algorithm for the multilayer perceptron algorithm. 20 percent of the data is separated as cross-validation
 * data used for selecting the best weights. 80 percent of the data is used for training the multilayer perceptron with
 * gradient descent.
 *
 * @param trainSet   Training data given to the algorithm
 * @param parameters Parameters of the multilayer perceptron.
 */
void MultiLayerPerceptron::train(InstanceList &trainSet, Parameter *parameters) {
    if (!discreteCheck(trainSet.get(0))){
        throw DiscreteFeaturesNotAllowed();
    }
    Partition partition = Partition(trainSet, ((MultiLayerPerceptronParameter*) parameters)->getCrossValidationRatio(), parameters->getSeed(), true);
    model = new MultiLayerPerceptronModel(*(partition.get(1)), *(partition.get(0)), (MultiLayerPerceptronParameter*) parameters);
}

void MultiLayerPerceptron::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new MultiLayerPerceptronModel(inputFile);
    inputFile.close();
}
