//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#include <cfloat>
#include <fstream>
#include "KMeansModel.h"
#include "../../DistanceMetric/EuclidianDistance.h"
#include "../../InstanceList/Partition.h"
#include "../../Parameter/KMeansParameter.h"

/**
 * The calculateMetric method takes an Instance and a String as inputs. It loops through the class means, if
 * the corresponding class label is same as the given String it returns the negated distance between given instance and the
 * current item of class means. Otherwise it returns the smallest negative number.
 *
 * @param instance Instance input.
 * @param Ci       String input.
 * @return The negated distance between given instance and the current item of class means.
 */
double KMeansModel::calculateMetric(Instance *instance, const string& Ci) const{
    for (int i = 0; i < classMeans.size(); i++) {
        if (classMeans.get(i)->getClassLabel() == Ci) {
            return -distanceMetric->distance(instance, classMeans.get(i));
        }
    }
    return -DBL_MAX;
}

/**
 * Saves the K-Means model to an output file.
 * @param outputFile Output file.
 */
void KMeansModel::serialize(ostream &outputFile) {
    GaussianModel::serialize(outputFile);
    classMeans.serialize(outputFile);
}

/**
 * Loads a K-means model from an input model file.
 * @param inputFile Model file.
 */
KMeansModel::KMeansModel(ifstream &inputFile) : GaussianModel(inputFile) {
    load(inputFile);
}

/**
 * Training algorithm for KMeans classifier. KMeans finds the mean of each class for training.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters distanceMetric: distance metric used to calculate the distance between two instances.
 */
void KMeansModel::train(InstanceList &trainSet, Parameter *parameters) {
    priorDistribution = trainSet.classDistribution();
    classMeans = InstanceList();
    Partition classLists = Partition(trainSet);
    for (int i = 0; i < classLists.size(); i++) {
        classMeans.add(classLists.get(i)->average());
    }
    this->distanceMetric = ((KMeansParameter*)(parameters))->getDistanceMetric();
}

/**
 * Loads the K-means model from an input file.
 * @param fileName File name of the K-means model.
 */
void KMeansModel::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    GaussianModel::load(inputFile);
    load(inputFile);
    inputFile.close();
}

/**
 * Loads a K-means model from an input model file.
 * @param inputFile Model file.
 */
 void KMeansModel::load(ifstream& inputFile){
    classMeans = InstanceList(inputFile);
    distanceMetric = new EuclidianDistance();
}