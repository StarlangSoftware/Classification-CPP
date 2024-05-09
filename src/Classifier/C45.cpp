//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include <fstream>
#include "C45.h"
#include "../Model/DecisionTree/DecisionTree.h"
#include "../Parameter/C45Parameter.h"
#include "../InstanceList/Partition.h"

/**
 * Training algorithm for C4.5 univariate decision tree classifier. 20 percent of the data are left aside for pruning
 * 80 percent of the data is used for constructing the tree.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void C45::train(InstanceList &trainSet, Parameter *parameters) {
    DecisionTree* tree;
    if (((C45Parameter*) parameters)->isPrune()) {
        Partition partition = Partition(trainSet, ((C45Parameter*) parameters)->getCrossValidationRatio(), parameters->getSeed(), true);
        tree = new DecisionTree(DecisionNode(*(partition.get(1)), DecisionCondition(), nullptr, false));
        tree->prune(*(partition.get(0)));
    } else {
        tree = new DecisionTree(DecisionNode(trainSet, DecisionCondition(), nullptr, false));
    }
    model = tree;
}

/**
 * Loads the decision tree model from an input file.
 * @param fileName File name of the decision tree model.
 */
void C45::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new DecisionTree(inputFile);
    inputFile.close();
}
