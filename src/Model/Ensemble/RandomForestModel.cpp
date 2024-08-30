//
// Created by Olcay Taner YILDIZ on 30.08.2024.
//

#include <fstream>
#include "RandomForestModel.h"

/**
 * Training algorithm for random forest classifier. Basically the algorithm creates K distinct decision trees from
 * K bootstrap samples of the original training set.
 *
 * @param trainSet   Training data given to the algorithm
 * @param parameters Parameters of the bagging trees algorithm. ensembleSize returns the number of trees in the random forest.
 */
void RandomForestModel::train(InstanceList &trainSet, Parameter *parameters) {
    int forestSize = ((RandomForestParameter*) parameters)->getEnsembleSize();
    for (int i = 0; i < forestSize; i++){
        Bootstrap<Instance*> bootstrap = trainSet.bootstrap(i);
        forest.emplace_back(new DecisionTree(DecisionNode(InstanceList(bootstrap.getSample()), DecisionCondition(), (RandomForestParameter*) parameters, false)));
    }
}

/**
 * Loads the random forest model from an input file.
 * @param fileName File name of the random forest model.
 */
void RandomForestModel::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    load(inputFile);
    inputFile.close();
}
