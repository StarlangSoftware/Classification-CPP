//
// Created by Olcay Taner Yıldız on 16.02.2019.
//
#include "../InstanceList/Partition.h"
#include "../Parameter/BaggingParameter.h"
#include "../Model/DecisionTree/DecisionTree.h"
#include "../Model/TreeEnsembleModel.h"
#include "Bagging.h"

/**
 * Bagging bootstrap ensemble method that creates individuals for its ensemble by training each classifier on a random
 * redistribution of the training set.
 * This training method is for a bagged decision tree classifier. 20 percent of the instances are left aside for pruning of the trees
 * 80 percent of the instances are used for training the trees. The number of trees (forestSize) is a parameter, and basically
 * the method will learn an ensemble of trees as a model.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters Parameters of the bagging trees algorithm. ensembleSize returns the number of trees in the bagged forest.
 */
void Bagging::train(InstanceList &trainSet, Parameter *parameters) {
    int forestSize = ((BaggingParameter*) parameters)->getEnsembleSize();
    vector<DecisionTree> forest;
    for (int i = 0; i < forestSize; i++){
        Bootstrap<Instance*> bootstrap = trainSet.bootstrap(i);
        forest.emplace_back(DecisionTree(DecisionNode(InstanceList(bootstrap.getSample()), DecisionCondition(), nullptr, false)));
    }
    model = new TreeEnsembleModel(forest);
}
