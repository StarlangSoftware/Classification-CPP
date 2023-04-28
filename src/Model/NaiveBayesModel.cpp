//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <cmath>
#include <fstream>
#include "NaiveBayesModel.h"
#include "../Attribute/ContinuousAttribute.h"
#include "../Attribute/DiscreteAttribute.h"

/**
 * The calculateMetric method takes an {@link Instance} and a String as inputs and it returns the log likelihood of
 * these inputs.
 *
 * @param instance {@link Instance} input.
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
 * The logLikelihoodContinuous method takes an {@link Instance} and a class label as inputs. First it gets the logarithm
 * of given class label's probability via prior distribution as logLikelihood. Then it loops times of given instance attribute size, and accumulates the
 * logLikelihood by calculating -0.5 * ((xi - mi) / si )** 2).
 *
 * @param classLabel String input class label.
 * @param instance   {@link Instance} input.
 * @return The log likelihood of given class label and {@link Instance}.
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
 * The logLikelihoodDiscrete method takes an {@link Instance} and a class label as inputs. First it gets the logarithm
 * of given class label's probability via prior distribution as logLikelihood and gets the class attribute distribution of given class label.
 * Then it loops times of given instance attribute size, and accumulates the logLikelihood by calculating the logarithm of
 * corresponding attribute distribution's smoothed probability by using laplace smoothing on xi.
 *
 * @param classLabel String input class label.
 * @param instance   {@link Instance} input.
 * @return The log likelihood of given class label and {@link Instance}.
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
 * @param priorDistribution {@link DiscreteDistribution} input.
 * @param classMeans        A {@link HashMap} of String and {@link Vector}.
 * @param classDeviations   A {@link HashMap} of String and {@link Vector}.
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
 * @param priorDistribution           {@link DiscreteDistribution} input.
 * @param classAttributeDistributions {@link HashMap} of String and {@link ArrayList} of {@link DiscreteDistribution}s.
 */
NaiveBayesModel::NaiveBayesModel(const DiscreteDistribution& priorDistribution,
                                 const map<string, vector<DiscreteDistribution>>& classAttributeDistributions) {
    this->priorDistribution = priorDistribution;
    this->classAttributeDistributions = classAttributeDistributions;
}

void NaiveBayesModel::serialize(ostream &outputFile) {
    GaussianModel::serialize(outputFile);
    outputFile << classMeans.size() << "\n";
    for (auto& iterator : classMeans){
        outputFile << iterator.first << "\n";
        iterator.second.serialize(outputFile);
    }
    for (auto& iterator : classDeviations){
        outputFile << iterator.first << "\n";
        iterator.second.serialize(outputFile);
    }
}

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
