//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#include <cmath>
#include <fstream>
#include "algorithm"
#include "KnnModel.h"
#include "../../DistanceMetric/EuclidianDistance.h"
#include "../../Parameter/KnnParameter.h"

/**
 * Constructor that sets the data InstanceList, k value and the DistanceMetric.
 *
 * @param data           InstanceList input.
 * @param k              K value.
 * @param distanceMetric DistanceMetric input.
 */
KnnModel::KnnModel(const InstanceList &data, int k, DistanceMetric *distanceMetric) {
    this->data = data;
    this->k = k;
    this->distanceMetric = distanceMetric;
}

/**
 * The predict method takes an Instance as an input and finds the nearest neighbors of given instance. Then
 * it returns the first possible class label as the predicted class.
 *
 * @param instance Instance to make prediction.
 * @return The first possible class label as the predicted class.
 */
string KnnModel::predict(Instance *instance){
    InstanceList neighbors = nearestNeighbors(instance);
    string predictedClass;
    if (instance->isComposite() && neighbors.size() == 0) {
        predictedClass = instance->getPossibleClassLabels().at(0);
    } else {
        predictedClass = Model::getMaximum(neighbors.getClassLabels());
    }
    return predictedClass;
}

bool knnInstanceComparator(KnnInstance instanceA, KnnInstance instanceB) { return (instanceA.getDistance() < instanceB.getDistance()); }
/**
 * The nearestNeighbors method takes an Instance as an input. First it gets the possible class labels, then loops
 * through the data InstanceList and creates new ArrayList of KnnInstances and adds the corresponding data with
 * the distance between data and given instance. After sorting this newly created ArrayList, it loops k times and
 * returns the first k instances as an InstanceList.
 *
 * @param instance Instance to find nearest neighbors/
 * @return The first k instances which are nearest to the given instance as an InstanceList.
 */
InstanceList KnnModel::nearestNeighbors(Instance *instance) const{
    InstanceList result = InstanceList();
    vector<KnnInstance> instances;
    vector<string> possibleClassLabels;
    if (instance->isComposite()) {
        possibleClassLabels = instance->getPossibleClassLabels();
    }
    for (int i = 0; i < data.size(); i++) {
        if (!instance->isComposite() || find(possibleClassLabels.begin(), possibleClassLabels.end(), data.get(i)->getClassLabel()) != possibleClassLabels.end()) {
            instances.emplace_back(KnnInstance(data.get(i), distanceMetric->distance(data.get(i), instance)));
        }
    }
    stable_sort(instances.begin(), instances.end(), knnInstanceComparator);
    for (int i = 0; i < fmin(k, instances.size()); i++) {
        result.add(instances.at(i).getInstance());
    }
    return result;
}

/**
 * Saves the K-nearest neighbor model to an output file.
 * @param outputFile Output file.
 */
void KnnModel::serialize(ostream &outputFile) {
    outputFile << k << "\n";
    data.serialize(outputFile);
}

/**
 * Loads a K-nearest neighbor model from an input model file.
 * @param inputFile Model file.
 */
KnnModel::KnnModel(ifstream &inputFile) {
    load(inputFile);
}

/**
 * Calculates the posterior probability distribution for the given instance according to K-means model.
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
map<string, double> KnnModel::predictProbability(Instance *instance){
    InstanceList neighbors = nearestNeighbors(instance);
    return neighbors.classDistribution().getProbabilityDistribution();
}

/**
 * Training algorithm for K-nearest neighbor classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters K: k parameter of the K-nearest neighbor algorithm
 *                   distanceMetric: distance metric used to calculate the distance between two instances.
 */
void KnnModel::train(InstanceList &trainSet, Parameter *parameters) {
    this->data = trainSet;
    this->k = ((KnnParameter*) parameters)->getK();
    this->distanceMetric = ((KnnParameter*) parameters)->getDistanceMetric();
}

/**
 * Loads the K-nearest neighbor model from an input file.
 * @param fileName File name of the K-nearest neighbor model.
 */
void KnnModel::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    load(inputFile);
    inputFile.close();
}

/**
 * Loads a K-nearest neighbor model from an input model file.
 * @param inputFile Model file.
 */
 void KnnModel::load(ifstream& inputFile){
    inputFile >> k;
    data = InstanceList(inputFile);
    distanceMetric = new EuclidianDistance();
}