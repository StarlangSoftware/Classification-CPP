//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <cmath>
#include <fstream>
#include "NaiveBayesModel.h"
#include "../Attribute/ContinuousAttribute.h"
#include "../Attribute/DiscreteAttribute.h"

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
 * A constructor that sets the priorDistribution, classMeans and classDeviations.
 *
 * @param priorDistribution DiscreteDistribution input.
 * @param classMeans        A HashMap of String and Vector.
 * @param classDeviations   A HashMap of String and Vector.
 */
NaiveBayesModel::NaiveBayesModel(const DiscreteDistribution& priorDistribution, const map<string, Vector>& classMeans,
                                 const map<string, Vector>& classDeviations) {
    this->priorDistribution = priorDistribution;
    this->classMeans = classMeans;
    this->classDeviations = classDeviations;
}

/**
 * A constructor that sets the priorDistribution and classAttributeDistributions.
 *
 * @param priorDistribution           DiscreteDistribution input.
 * @param classAttributeDistributions HashMap of String and ArrayList of DiscreteDistributions.
 */
NaiveBayesModel::NaiveBayesModel(const DiscreteDistribution& priorDistribution,
                                 const map<string, vector<DiscreteDistribution>>& classAttributeDistributions) {
    this->priorDistribution = priorDistribution;
    this->classAttributeDistributions = classAttributeDistributions;
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
