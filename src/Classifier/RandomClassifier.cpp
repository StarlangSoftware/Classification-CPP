//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <fstream>
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

void RandomClassifier::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new RandomModel(inputFile);
    inputFile.close();
}
