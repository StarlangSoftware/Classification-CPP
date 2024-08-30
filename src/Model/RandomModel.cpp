//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <fstream>
#include "RandomModel.h"

/**
 * A constructor that sets the class labels.
 *
 * @param classLabels An ArrayList of class labels.
 */
RandomModel::RandomModel(const vector<string>& classLabels) {
    this->classLabels = classLabels;
}

/**
 * The predict method gets an Instance as an input and retrieves the possible class labels as an ArrayList. Then selects a
 * random number as an index and returns the class label at this selected index.
 *
 * @param instance Instance to make prediction.
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

/**
 * Saves the random classifier model to an output file.
 * @param outputFile Output file.
 */
void RandomModel::serialize(ostream &outputFile) {
    outputFile << classLabels.size() << "\n";
    for (const string& classLabel : classLabels){
        outputFile << classLabel << "\n";
    }
}

/**
 * Loads a random classifier model from an input model file.
 * @param inputFile Model file.
 */
RandomModel::RandomModel(ifstream &inputFile) {
    load(inputFile);
}

/**
 * Calculates the posterior probability distribution for the given instance according to random model.
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
map<string, double> RandomModel::predictProbability(Instance *instance) {
    map<string, double> result;
    for (const string& classLabel : classLabels){
        result.insert_or_assign(classLabel, 1.0 / classLabels.size());
    }
    return result;
}

/**
 * Training algorithm for random classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void RandomModel::train(InstanceList &trainSet, Parameter *parameters) {
    this->classLabels = trainSet.classDistribution().getItems();
}

/**
 * Loads the random classifier model from an input file.
 * @param fileName File name of the random classifier model.
 */
void RandomModel::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    load(inputFile);
    inputFile.close();
}

/**
 * Loads a random classifier model from an input model file.
 * @param inputFile Model file.
 */
void RandomModel::load(ifstream& inputFile){
    int size;
    string classLabel;
    inputFile >> seed;
    inputFile >> size;
    for (int i = 0; i < size; i++){
        inputFile >> classLabel;
        classLabels.push_back(classLabel);
    }
}