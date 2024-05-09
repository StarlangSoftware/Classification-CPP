//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include <fstream>
#include "C45Stump.h"
#include "../Model/DecisionTree/DecisionTree.h"

/**
 * Training algorithm for C4.5 Stump univariate decision tree classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void C45Stump::train(InstanceList &trainSet, Parameter *parameters) {
    model = new DecisionTree(DecisionNode(trainSet, DecisionCondition(), nullptr, true));
}

/**
 * Loads the decision tree model from an input file.
 * @param fileName File name of the decision tree model.
 */
void C45Stump::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new DecisionTree(inputFile);
    inputFile.close();
}
