//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include <fstream>
#include "RandomForest.h"
#include "../Parameter/RandomForestParameter.h"
#include "../Model/DecisionTree/DecisionTree.h"
#include "../Model/TreeEnsembleModel.h"

/**
 * Training algorithm for random forest classifier. Basically the algorithm creates K distinct decision trees from
 * K bootstrap samples of the original training set.
 *
 * @param trainSet   Training data given to the algorithm
 * @param parameters Parameters of the bagging trees algorithm. ensembleSize returns the number of trees in the random forest.
 */
void RandomForest::train(InstanceList &trainSet, Parameter *parameters) {
    int forestSize = ((RandomForestParameter*) parameters)->getEnsembleSize();
    vector<DecisionTree*> forest;
    for (int i = 0; i < forestSize; i++){
        Bootstrap<Instance*> bootstrap = trainSet.bootstrap(i);
        forest.emplace_back(new DecisionTree(DecisionNode(InstanceList(bootstrap.getSample()), DecisionCondition(), (RandomForestParameter*) parameters, false)));
    }
    model = new TreeEnsembleModel(forest);
}

/**
 * Loads the random forest model from an input file.
 * @param fileName File name of the random forest model.
 */
void RandomForest::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new TreeEnsembleModel(inputFile);
    inputFile.close();
}
