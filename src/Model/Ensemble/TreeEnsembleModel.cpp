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

/**
 * Loads a tree ensemble model such as Random Forest model or Bagging model from an input model file.
 * @param outputFile Model file.
 */
void TreeEnsembleModel::serialize(ostream &outputFile) {
    outputFile << forest.size() << "\n";
    for (DecisionTree* tree : forest){
        tree->serialize(outputFile);
    }
}

/**
 * Loads a tree ensemble model such as Random Forest model or Bagging model from an input model file.
 * @param inputFile Model file.
 */
TreeEnsembleModel::TreeEnsembleModel(ifstream &inputFile) {
    load(inputFile);
}

/**
 * Calculates the posterior probability distribution for the given instance according to ensemble tree model.
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
map<string, double> TreeEnsembleModel::predictProbability(Instance *instance) {
    DiscreteDistribution distribution = DiscreteDistribution();
    for (DecisionTree* tree : forest) {
        distribution.addItem(tree->predict(instance));
    }
    return distribution.getProbabilityDistribution();
}

void TreeEnsembleModel::load(ifstream& inputFile){
    int size;
    inputFile >> size;
    for (int i = 0; i < size; i++){
        DecisionTree* tree = new DecisionTree(inputFile);
        forest.push_back(tree);
    }
}