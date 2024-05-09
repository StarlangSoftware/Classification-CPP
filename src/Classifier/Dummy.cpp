//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <fstream>
#include "Dummy.h"
#include "../Model/DummyModel.h"

/**
 * Training algorithm for the dummy classifier. Actually dummy classifier returns the maximum occurring class in
 * the training data, there is no training.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void Dummy::train(InstanceList &trainSet, Parameter *parameters) {
    model = new DummyModel(trainSet);
}

/**
 * Loads the dummy model from an input file.
 * @param fileName File name of the dummy model.
 */
void Dummy::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new DummyModel(inputFile);
    inputFile.close();
}
