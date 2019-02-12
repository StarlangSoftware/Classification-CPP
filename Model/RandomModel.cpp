//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include "RandomModel.h"
#include "../Instance/CompositeInstance.h"

/**
 * A constructor that sets the class labels.
 *
 * @param classLabels An ArrayList of class labels.
 */
RandomModel::RandomModel(vector<string> classLabels) {
    this->classLabels = classLabels;
}

/**
 * The predict method gets an Instance as an input and retrieves the possible class labels as an ArrayList. Then selects a
 * random number as an index and returns the class label at this selected index.
 *
 * @param instance {@link Instance} to make prediction.
 * @return The class label at the randomly selected index.
 */
string RandomModel::predict(Instance *instance) {
    if (instance->isComposite()) {
        vector<string> possibleClassLabels = instance->getPossibleClassLabels();
        int size = possibleClassLabels.size();
        int index = random() % size;
        return possibleClassLabels.at(index);
    } else {
        int size = classLabels.size();
        int index = random() % size;
        return classLabels.at(index);
    }
}
