//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

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
    vector<DecisionTree> forest;
    for (int i = 0; i < forestSize; i++){
        Bootstrap bootstrap = trainSet.bootstrap(i);
        forest.emplace_back(DecisionTree(DecisionNode(InstanceList(bootstrap.getSample()), DecisionCondition(), (RandomForestParameter*) parameters, false)));
    }
    model = new TreeEnsembleModel(forest);
}
