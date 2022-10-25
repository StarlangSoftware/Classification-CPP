//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <VectorSizeMismatch.h>
#include <cfloat>
#include <fstream>
#include "LdaModel.h"

/**
 * The calculateMetric method takes an {@link Instance} and a String as inputs. It returns the dot product of given Instance
 * and w0 plus w1.
 *
 * @param instance {@link Instance} input.
 * @param Ci       String input.
 * @return The dot product of given Instance and w0 plus w1.
 */
double LdaModel::calculateMetric(Instance *instance, const string& Ci) const{
    double w0i;
    Vector xi = instance->toVector();
    Vector wi = w.find(Ci)->second;
    w0i = w0.find(Ci)->second;
    try {
        return wi.dotProduct(xi) + w0i;
    } catch (VectorSizeMismatch& vectorSizeMismatch) {
        return DBL_MAX;
    }
}

/**
 * A constructor which sets the priorDistribution, w and w1 according to given inputs.
 *
 * @param priorDistribution {@link DiscreteDistribution} input.
 * @param w                 {@link HashMap} of String and Vectors.
 * @param w0                {@link HashMap} of String and Double.
 */
LdaModel::LdaModel(const DiscreteDistribution& priorDistribution, const map<string, Vector>& w, const map<string, double>& w0) {
    this->priorDistribution = priorDistribution;
    this->w = w;
    this->w0 = w0;
}

void LdaModel::serialize(ostream &outputFile) {
    GaussianModel::serialize(outputFile);
    outputFile << w0.size() << "\n";
    for (auto& iterator : w0){
        outputFile << iterator.first << "\n";
        outputFile << iterator.second << "\n";
    }
    for (auto& iterator : w){
        outputFile << iterator.first << "\n";
        iterator.second.serialize(outputFile);
    }
}

LdaModel::LdaModel(ifstream &inputFile) : GaussianModel(inputFile) {
    int size;
    double weight;
    string classLabel;
    inputFile >> size;
    for (int i = 0; i < size; i++){
        inputFile >> classLabel;
        inputFile >> weight;
        w0.emplace(classLabel, weight);
    }
    for (int i = 0; i < size; i++){
        inputFile >> classLabel;
        Vector vector = Vector(inputFile);
        w.emplace(classLabel, vector);
    }
}
