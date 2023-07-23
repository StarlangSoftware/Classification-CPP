//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <fstream>
#include "NaiveBayes.h"
#include "../InstanceList/InstanceListOfSameClass.h"
#include "../Model/NaiveBayesModel.h"

/**
 * Training algorithm for Naive Bayes algorithm with a continuous data set.
 *
 * @param priorDistribution Probability distribution of classes P(C_i)
 * @param classLists        Instances are divided into K lists, where each list contains only instances from a single class
 */
void NaiveBayes::trainContinuousVersion(const DiscreteDistribution& priorDistribution, const Partition& classLists) {
    string classLabel;
    map<string, Vector> classMeans;
    map<string, Vector> classDeviations;
    for (int i = 0; i < classLists.size(); i++){
        classLabel = ((InstanceListOfSameClass*)(classLists.get(i)))->getClassLabel();
        Vector averageVector = classLists.get(i)->average()->toVector();
        classMeans.emplace(classLabel, averageVector);
        Vector standardDeviationVector = classLists.get(i)->standardDeviation()->toVector();
        classDeviations.emplace(classLabel, standardDeviationVector);
    }
    model = new NaiveBayesModel(priorDistribution, classMeans, classDeviations);
}

/**
 * Training algorithm for Naive Bayes algorithm with a discrete data set.
 * @param priorDistribution Probability distribution of classes P(C_i)
 * @param classLists Instances are divided into K lists, where each list contains only instances from a single class
 */
void NaiveBayes::trainDiscreteVersion(const DiscreteDistribution& priorDistribution, const Partition& classLists) {
    map<string, vector<DiscreteDistribution>> classAttributeDistributions;
    for (int i = 0; i < classLists.size(); i++){
        classAttributeDistributions.emplace(((InstanceListOfSameClass*)(classLists.get(i)))->getClassLabel(), classLists.get(i)->allAttributesDistribution());
    }
    model = new NaiveBayesModel(priorDistribution, classAttributeDistributions);
}

/**
 * Training algorithm for Naive Bayes algorithm. It basically calls trainContinuousVersion for continuous data sets,
 * trainDiscreteVersion for discrete data sets.
 * @param trainSet Training data given to the algorithm
 * @param parameters -
 */
void NaiveBayes::train(InstanceList &trainSet, Parameter *parameters) {
    DiscreteDistribution priorDistribution = trainSet.classDistribution();
    Partition classLists = Partition(trainSet);
    if (classLists.get(0)->get(0)->getAttribute(0)->isDiscrete()){
        trainDiscreteVersion(priorDistribution, classLists);
    } else {
        trainContinuousVersion(priorDistribution, classLists);
    }
}

void NaiveBayes::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new NaiveBayesModel(inputFile);
    inputFile.close();
}
