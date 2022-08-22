//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <random>
#include <fstream>
#include "RandomModel.h"
#include "../Instance/CompositeInstance.h"

/**
 * A constructor that sets the class labels.
 *
 * @param classLabels An ArrayList of class labels.
 */
RandomModel::RandomModel(vector<string> classLabels) {
    this->classLabels = move(classLabels);
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
        unsigned long size = possibleClassLabels.size();
        unsigned long index = random() % size;
        return possibleClassLabels.at(index);
    } else {
        unsigned long size = classLabels.size();
        unsigned long index = random() % size;
        return classLabels.at(index);
    }
}

void RandomModel::serialize(ostream &outputFile) {
    outputFile << classLabels.size() << "\n";
    for (const string& classLabel : classLabels){
        outputFile << classLabel << "\n";
    }
}

RandomModel::RandomModel(ifstream &inputFile) {
    int size;
    string classLabel;
    inputFile >> size;
    for (int i = 0; i < size; i++){
        inputFile >> classLabel;
        classLabels.push_back(classLabel);
    }
}

map<string, double> RandomModel::predictProbability(Instance *instance) {
    map<string, double> result;
    for (const string& classLabel : classLabels){
        result.insert_or_assign(classLabel, 1.0 / classLabels.size());
    }
    return result;
}
