//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include "FloatingSelection.h"

/**
 * Constructor that creates a new {@link FeatureSubSet}.
 */
FloatingSelection::FloatingSelection() : SubSetSelection(){
}

/**
 * The operator method calls forward and backward methods.
 *
 * @param current          {@link FeatureSubSet} input.
 * @param numberOfFeatures Indicates the indices of indexList.
 * @return ArrayList of FeatureSubSet.
 */
vector<FeatureSubSet> FloatingSelection::operatorToModify(FeatureSubSet &current, int numberOfFeatures) {
    vector<FeatureSubSet> result;
    forward(result, current, numberOfFeatures);
    backward(result, current);
    return result;
}
