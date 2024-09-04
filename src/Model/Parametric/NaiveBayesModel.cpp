//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <cmath>
#include <fstream>
#include "NaiveBayesModel.h"
#include "../../Attribute/ContinuousAttribute.h"
#include "../../Attribute/DiscreteAttribute.h"
#include "../../InstanceList/InstanceListOfSameClass.h"

/**
 * The calculateMetric method takes an Instance and a String as inputs and it returns the log likelihood of
 * these inputs.
 *
 * @param instance Instance input.
 * @param Ci       String input.
 * @return The log likelihood of inputs.
 */
double NaiveBayesModel::calculateMetric(Instance *instance, const string& Ci) const{
    if (classAttributeDistributions.empty()) {
        return logLikelihoodContinuous(Ci, instance);
    } else {
        return logLikelihoodDiscrete(Ci, instance);
    }
}

/**
 * The logLikelihoodContinuous method takes an Instance and a class label as inputs. First it gets the logarithm
 * of given class label's probability via prior distribution as logLikelihood. Then it loops times of given instance attribute size, and accumulates the
 * logLikelihood by calculating -0.5 * ((xi - mi) / si )** 2).
 *
 * @param classLabel String input class label.
 * @param instance   Instance input.
 * @return The log likelihood of given class label and Instance.
 */
double NaiveBayesModel::logLikelihoodContinuous(const string& classLabel, Instance *instance) const{
    double xi, mi, si;
    double logLikelihood = log(priorDistribution.getProbability(classLabel));
    for (int i = 0; i < instance->attributeSize(); i++) {
        xi = ((ContinuousAttribute*)(instance->getAttribute(i)))->getValue();
        mi = classMeans.find(classLabel)->second.getValue(i);
        si = classDeviations.find(classLabel)->second.getValue(i);
        logLikelihood += -0.5 * pow((xi - mi) / si, 2);
    }
    return logLikelihood;
}

/**
 * The logLikelihoodDiscrete method takes an Instance and a class label as inputs. First it gets the logarithm
 * of given class label's probability via prior distribution as logLikelihood and gets the class attribute distribution of given class label.
 * Then it loops times of given instance attribute size, and accumulates the logLikelihood by calculating the logarithm of
 * corresponding attribute distribution's smoothed probability by using laplace smoothing on xi.
 *
 * @param classLabel String input class label.
 * @param instance   Instance input.
 * @return The log likelihood of given class label and Instance.
 */
double NaiveBayesModel::logLikelihoodDiscrete(const string& classLabel, Instance *instance) const{
    string xi;
    double logLikelihood = log(priorDistribution.getProbability(classLabel));
    vector<DiscreteDistribution> attributeDistributions = classAttributeDistributions.find(classLabel)->second;
    for (int i = 0; i < instance->attributeSize(); i++) {
        xi = ((DiscreteAttribute*)(instance->getAttribute(i)))->getValue();
        logLikelihood += log(attributeDistributions.at(i).getProbabilityLaplaceSmoothing(xi));
    }
    return logLikelihood;
}

/**
 * Saves the Naive Bayes model to an output file.
 * @param outputFile Output file.
 */
void NaiveBayesModel::serialize(ostream &outputFile) {
    GaussianModel::serialize(outputFile);
    for (auto& iterator : classMeans){
        outputFile << iterator.first << "\n";
        iterator.second.serialize(outputFile);
    }
    for (auto& iterator : classDeviations){
        outputFile << iterator.first << "\n";
        iterator.second.serialize(outputFile);
    }
}

/**
 * Loads a naive Bayes model from an input model file.
 * @param inputFile Model file.
 */
NaiveBayesModel::NaiveBayesModel(ifstream &inputFile) : GaussianModel(inputFile) {
    load(inputFile);
}

/**
 * Training algorithm for Naive Bayes algorithm with a continuous data set.
 *
 * @param priorDistribution Probability distribution of classes P(C_i)
 * @param classLists        Instances are divided into K lists, where each list contains only instances from a single class
 */
void NaiveBayesModel::trainContinuousVersion(const Partition& classLists) {
    string classLabel;
    for (int i = 0; i < classLists.size(); i++){
        classLabel = ((InstanceListOfSameClass*)(classLists.get(i)))->getClassLabel();
        Vector averageVector = classLists.get(i)->average()->toVector();
        classMeans.emplace(classLabel, averageVector);
        Vector standardDeviationVector = classLists.get(i)->standardDeviation()->toVector();
        classDeviations.emplace(classLabel, standardDeviationVector);
    }
}

/**
 * Training algorithm for Naive Bayes algorithm with a discrete data set.
 * @param priorDistribution Probability distribution of classes P(C_i)
 * @param classLists Instances are divided into K lists, where each list contains only instances from a single class
 */
void NaiveBayesModel::trainDiscreteVersion(const Partition& classLists) {
    for (int i = 0; i < classLists.size(); i++){
        classAttributeDistributions.emplace(((InstanceListOfSameClass*)(classLists.get(i)))->getClassLabel(), classLists.get(i)->allAttributesDistribution());
    }
}

/**
 * Training algorithm for Naive Bayes algorithm. It basically calls trainContinuousVersion for continuous data sets,
 * trainDiscreteVersion for discrete data sets.
 * @param trainSet Training data given to the algorithm
 * @param parameters -
 */
void NaiveBayesModel::train(InstanceList &trainSet, Parameter *parameters) {
    priorDistribution = trainSet.classDistribution();
    Partition classLists = Partition(trainSet);
    if (classLists.get(0)->get(0)->getAttribute(0)->isDiscrete()){
        trainDiscreteVersion(classLists);
    } else {
        trainContinuousVersion(classLists);
    }
}

/**
 * Loads the naive Bayes model from an input file.
 * @param fileName File name of the naive Bayes model.
 */
void NaiveBayesModel::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    GaussianModel::load(inputFile);
    load(inputFile);
    inputFile.close();
}

/**
 * Loads a naive Bayes model from an input model file.
 * @param inputFile Model file.
 */
void NaiveBayesModel::load(ifstream& inputFile){
    string classLabel;
    for (int i = 0; i < priorDistribution.size(); i++){
        inputFile >> classLabel;
        Vector vector = Vector(inputFile);
        classMeans.emplace(classLabel, vector);
    }
    for (int i = 0; i < priorDistribution.size(); i++){
        inputFile >> classLabel;
        Vector vector = Vector(inputFile);
        classDeviations.emplace(classLabel, vector);
    }
}