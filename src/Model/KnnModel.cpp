//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#include <cmath>
#include <fstream>
#include "KnnModel.h"
#include "../Instance/CompositeInstance.h"
#include "../Classifier/Classifier.h"
#include "../DistanceMetric/EuclidianDistance.h"

/**
 * Constructor that sets the data {@link InstanceList}, k value and the {@link DistanceMetric}.
 *
 * @param data           {@link InstanceList} input.
 * @param k              K value.
 * @param distanceMetric {@link DistanceMetric} input.
 */
KnnModel::KnnModel(const InstanceList &data, int k, DistanceMetric *distanceMetric) {
    this->data = data;
    this->k = k;
    this->distanceMetric = distanceMetric;
}

/**
 * The predict method takes an {@link Instance} as an input and finds the nearest neighbors of given instance. Then
 * it returns the first possible class label as the predicted class.
 *
 * @param instance {@link Instance} to make prediction.
 * @return The first possible class label as the predicted class.
 */
string KnnModel::predict(Instance *instance){
    InstanceList neighbors = nearestNeighbors(instance);
    string predictedClass;
    if (instance->isComposite() && neighbors.size() == 0) {
        predictedClass = instance->getPossibleClassLabels().at(0);
    } else {
        predictedClass = Classifier::getMaximum(neighbors.getClassLabels());
    }
    return predictedClass;
}

bool knnInstanceComparator(KnnInstance instanceA, KnnInstance instanceB) { return (instanceA.getDistance() < instanceB.getDistance()); }
/**
 * The nearestNeighbors method takes an {@link Instance} as an input. First it gets the possible class labels, then loops
 * through the data {@link InstanceList} and creates new {@link ArrayList} of {@link KnnInstance}s and adds the corresponding data with
 * the distance between data and given instance. After sorting this newly created ArrayList, it loops k times and
 * returns the first k instances as an {@link InstanceList}.
 *
 * @param instance {@link Instance} to find nearest neighbors/
 * @return The first k instances which are nearest to the given instance as an {@link InstanceList}.
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

void KnnModel::serialize(ostream &outputFile) {
    outputFile << k << "\n";
    data.serialize(outputFile);
}

KnnModel::KnnModel(ifstream &inputFile) {
    inputFile >> k;
    data = InstanceList(inputFile);
    distanceMetric = new EuclidianDistance();
}

map<string, double> KnnModel::predictProbability(Instance *instance){
    InstanceList neighbors = nearestNeighbors(instance);
    return neighbors.classDistribution().getProbabilityDistribution();
}
