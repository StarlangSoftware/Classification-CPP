//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include "FloatingSelection.h"

/**
 * Constructor that creates a new FeatureSubSet.
 */
FloatingSelection::FloatingSelection() : SubSetSelection(){
}

/**
 * The operator method calls forward and backward methods.
 *
 * @param current          FeatureSubSet input.
 * @param numberOfFeatures Indicates the indices of indexList.
 * @return ArrayList of FeatureSubSet.
 */
vector<FeatureSubSet> FloatingSelection::operatorToModify(const FeatureSubSet &current, int numberOfFeatures) {
    vector<FeatureSubSet> result;
    forward(result, current, numberOfFeatures);
    backward(result, current);
    return result;
}
