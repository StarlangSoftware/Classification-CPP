//
// Created by olcay on 12.02.2019.
//

#include <fstream>
#include "Knn.h"
#include "../Model/KnnModel.h"
#include "../Parameter/KnnParameter.h"

/**
 * Training algorithm for K-nearest neighbor classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters K: k parameter of the K-nearest neighbor algorithm
 *                   distanceMetric: distance metric used to calculate the distance between two instances.
 */
void Knn::train(InstanceList &trainSet, Parameter *parameters) {
    model = new KnnModel(trainSet, ((KnnParameter*) parameters)->getK(), ((KnnParameter*) parameters)->getDistanceMetric());
}

/**
 * Loads the K-nearest neighbor model from an input file.
 * @param fileName File name of the K-nearest neighbor model.
 */
void Knn::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new KnnModel(inputFile);
    inputFile.close();
}
