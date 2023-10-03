//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include <fstream>
#include "TreeEnsembleModel.h"

/**
 * The predict method takes an Instance as an input and loops through the ArrayList of DecisionTrees.
 * Makes prediction for the items of that ArrayList and returns the maximum item of that ArrayList.
 *
 * @param instance Instance to make prediction.
 * @return The maximum prediction of a given Instance.
 */
string TreeEnsembleModel::predict(Instance *instance) {
    DiscreteDistribution distribution = DiscreteDistribution();
    for (DecisionTree* tree : forest) {
        distribution.addItem(tree->predict(instance));
    }
    return distribution.getMaxItem();
}

/**
 * A constructor which sets the vector of DecisionTree with given input.
 *
 * @param forest An vector of DecisionTree.
 */
TreeEnsembleModel::TreeEnsembleModel(const vector<DecisionTree*>& forest) {
    this->forest = forest;
}

void TreeEnsembleModel::serialize(ostream &outputFile) {
    outputFile << forest.size() << "\n";
    for (DecisionTree* tree : forest){
        tree->serialize(outputFile);
    }
}

TreeEnsembleModel::TreeEnsembleModel(ifstream &inputFile) {
    int size;
    inputFile >> size;
    for (int i = 0; i < size; i++){
        DecisionTree* tree = new DecisionTree(inputFile);
        forest.push_back(tree);
    }
}

map<string, double> TreeEnsembleModel::predictProbability(Instance *instance) {
    DiscreteDistribution distribution = DiscreteDistribution();
    for (DecisionTree* tree : forest) {
        distribution.addItem(tree->predict(instance));
    }
    return distribution.getProbabilityDistribution();
}
