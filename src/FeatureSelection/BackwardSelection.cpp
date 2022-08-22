//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include "BackwardSelection.h"

/**
 * Constructor that creates a new {@link FeatureSubSet} and initializes indexList with given number of features.
 *
 * @param numberOfFeatures Indicates the indices of indexList.
 */
BackwardSelection::BackwardSelection(int numberOfFeatures) : SubSetSelection(numberOfFeatures) {
}

/**
 * The operator method calls backward method which starts with all the features and removes the least significant feature at each iteration.
 *
 * @param current          FeatureSubset that will be added to new ArrayList.
 * @param numberOfFeatures Indicates the indices of indexList.
 * @return ArrayList of FeatureSubSets created from backward.
 */
vector<FeatureSubSet> BackwardSelection::operatorToModify(FeatureSubSet &current, int numberOfFeatures) {
    vector<FeatureSubSet> result;
    backward(result, current);
    return result;
}
