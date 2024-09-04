//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <VectorSizeMismatch.h>
#include <cfloat>
#include <fstream>
#include <iostream>
#include <cmath>
#include "LdaModel.h"
#include "MatrixDimensionMismatch.h"
#include "DeterminantZero.h"
#include "MatrixColumnMismatch.h"
#include "../../InstanceList/Partition.h"
#include "../../InstanceList/InstanceListOfSameClass.h"
#include "../DiscreteFeaturesNotAllowed.h"

/**
 * The calculateMetric method takes an Instance and a String as inputs. It returns the dot product of given Instance
 * and w0 plus w1.
 *
 * @param instance Instance input.
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
 * Saves the Linear discriminant analysis model to an output file.
 * @param outputFile Output file.
 */
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

/**
 * Loads a Linear Discriminant Analysis model from an input model file.
 * @param inputFile Model file.
 */
LdaModel::LdaModel(ifstream &inputFile) : GaussianModel(inputFile) {
    load(inputFile);
}

/**
 * Training algorithm for the linear discriminant analysis classifier (Introduction to Machine Learning, Alpaydin, 2015).
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void LdaModel::train(InstanceList &trainSet, Parameter *parameters) {
    if (!discreteCheck(trainSet.get(0))){
        throw DiscreteFeaturesNotAllowed();
    }
    string Ci;
    double w0i;
    priorDistribution = trainSet.classDistribution();
    Partition classLists = Partition(trainSet);
    Matrix covariance = Matrix(trainSet.get(0)->continuousAttributeSize(), trainSet.get(0)->continuousAttributeSize());
    for (int i = 0; i < classLists.size(); i++) {
        Vector averageVector = Vector(classLists.get(i)->continuousAttributeAverage());
        Matrix classCovariance = classLists.get(i)->covariance(averageVector);
        classCovariance.multiplyWithConstant(classLists.get(i)->size() - 1);
        try {
            covariance.add(classCovariance);
        } catch (MatrixDimensionMismatch& matrixDimensionMismatch) {
        }
    }
    covariance.divideByConstant(trainSet.size() - classLists.size());
    try {
        covariance.inverse();
    } catch (DeterminantZero& determinantZero) {
        cout << determinantZero.what();
    }
    for (int i = 0; i < classLists.size(); i++) {
        Ci = ((InstanceListOfSameClass*)(classLists.get(i)))->getClassLabel();
        Vector averageVector = Vector(classLists.get(i)->continuousAttributeAverage());
        try {
            Vector wi = covariance.multiplyWithVectorFromRight(averageVector);
            w.emplace(Ci, wi);
            w0i = -0.5 * wi.dotProduct(averageVector) + log(priorDistribution.getProbability(Ci));
            w0.emplace(Ci, w0i);
        } catch (MatrixColumnMismatch& mismatch1) {
        } catch (VectorSizeMismatch& mismatch2){
        }
    }
}

/**
 * Loads the Lda model from an input file.
 * @param fileName File name of the Lda model.
 */
void LdaModel::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    GaussianModel::load(inputFile);
    load(inputFile);
    inputFile.close();
}

/**
 * Loads the Lda model from an input file.
 * @param fileName File name of the Lda model.
 */
void LdaModel::load(ifstream& inputFile){
    double weight;
    string classLabel;
    for (int i = 0; i < priorDistribution.size(); i++){
        inputFile >> classLabel;
        inputFile >> weight;
        w0.emplace(classLabel, weight);
    }
    for (int i = 0; i < priorDistribution.size(); i++){
        inputFile >> classLabel;
        Vector vector = Vector(inputFile);
        w.emplace(classLabel, vector);
    }
}