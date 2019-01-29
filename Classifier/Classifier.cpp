//
// Created by olcay on 29.01.2019.
//

#include <CounterHashMap.h>
#include "Classifier.h"

/**
 * Given an array of class labels, returns the maximum occurred one.
 *
 * @param classLabels An array of class labels.
 * @return The class label that occurs most in the array of class labels (mod of class label list).
 */
string Classifier::getMaximum(vector<string> classLabels) {
    CounterHashMap<string> frequencies;
    for (const string &label : classLabels) {
        frequencies.put(label);
    }
    return frequencies.max();
}
