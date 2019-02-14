//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include "ForwardSelection.h"

/**
 * Constructor that creates a new {@link FeatureSubSet}.
 */
ForwardSelection::ForwardSelection() : SubSetSelection(){
}

/**
 * The operator method calls forward method which starts with having no feature in the model. In each iteration,
 * it keeps adding the features that are not currently listed.
 *
 * @param current          FeatureSubset that will be added to new ArrayList.
 * @param numberOfFeatures Indicates the indices of indexList.
 * @return ArrayList of FeatureSubSets created from backward.
 */
vector<FeatureSubSet> ForwardSelection::operatorToModify(FeatureSubSet &current, int numberOfFeatures) {
    vector<FeatureSubSet> result;
    forward(result, current, numberOfFeatures);
    return result;
}
