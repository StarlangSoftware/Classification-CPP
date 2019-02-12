//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#include "KMeans.h"
#include "../InstanceList/Partition.h"
#include "../Model/KMeansModel.h"
#include "../Parameter/KMeansParameter.h"

/**
 * Training algorithm for KMeans classifier. KMeans finds the mean of each class for training.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters distanceMetric: distance metric used to calculate the distance between two instances.
 */
void KMeans::train(InstanceList &trainSet, Parameter *parameters) {
    DiscreteDistribution priorDistribution = trainSet.classDistribution();
    InstanceList classMeans = InstanceList();
    Partition classLists = Partition(trainSet);
    for (int i = 0; i < classLists.size(); i++) {
        classMeans.add(classLists.get(i)->average());
    }
    model = new KMeansModel(priorDistribution, classMeans, ((KMeansParameter*)(parameters))->getDistanceMetric());
}
