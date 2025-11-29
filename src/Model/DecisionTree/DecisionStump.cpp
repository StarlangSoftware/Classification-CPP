//
// Created by Olcay Taner YILDIZ on 30.08.2024.
//

#include "DecisionStump.h"
#include <fstream>
#include "DecisionTree.h"

/**
 * Training algorithm for C4.5 Stump univariate decision tree classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void DecisionStump::train(InstanceList &trainSet, Parameter *parameters) {
    root = new DecisionNode(trainSet, DecisionCondition(), nullptr, true);
}

/**
 * Loads the decision tree model from an input file.
 * @param fileName File name of the decision tree model.
 */
void DecisionStump::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    root = new DecisionNode(inputFile);
    inputFile.close();
}
