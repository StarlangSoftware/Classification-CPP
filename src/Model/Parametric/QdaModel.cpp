//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <iostream>
#include <cmath>
#include <cfloat>
#include <fstream>
#include <VectorSizeMismatch.h>
#include <MatrixRowMismatch.h>
#include <DeterminantZero.h>
#include "QdaModel.h"
#include "../DiscreteFeaturesNotAllowed.h"
#include "../../InstanceList/Partition.h"
#include "../../InstanceList/InstanceListOfSameClass.h"

/**
 * The calculateMetric method takes an Instance and a String as inputs. It multiplies Matrix Wi with Vector xi
 * then calculates the dot product of it with xi. Then, again it finds the dot product of wi and xi and returns the summation with w0i.
 *
 * @param instance Instance input.
 * @param Ci       String input.
 * @return The result of Wi.multiplyWithVectorFromLeft(xi).dotProduct(xi) + wi.dotProduct(xi) + w0i.
 */
double QdaModel::calculateMetric(Instance *instance, const string& Ci) const{
    double w0i;
    Vector xi = instance->toVector();
    Matrix Wi = W.find(Ci)->second;
    Vector wi = w.find(Ci)->second;
    w0i = w0.find(Ci)->second;
    try {
        return Wi.multiplyWithVectorFromLeft(xi).dotProduct(xi) + wi.dotProduct(xi) + w0i;
    } catch (VectorSizeMismatch& mismatch1) {
        return DBL_MAX;
    } catch (MatrixRowMismatch& mismatch2) {
        return DBL_MAX;
    }
}

/**
 * Loads a quadratic discriminant analysis model from an input model file.
 * @param inputFile Model file.
 */
QdaModel::QdaModel(ifstream &inputFile) : LdaModel(inputFile) {
    load(inputFile);
}

/**
 * Training algorithm for the quadratic discriminant analysis classifier (Introduction to Machine Learning, Alpaydin, 2015).
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void QdaModel::train(InstanceList& trainSet, Parameter *parameters) {
    if (!discreteCheck(trainSet.get(0))){
        throw DiscreteFeaturesNotAllowed();
    }
    string Ci;
    double determinant, w0i;
    Partition classLists = Partition(trainSet);
    priorDistribution = trainSet.classDistribution();
    for (int i = 0; i < classLists.size(); i++) {
        Ci = ((InstanceListOfSameClass*)(classLists.get(i)))->getClassLabel();
        Vector averageVector = Vector(classLists.get(i)->continuousAttributeAverage());
        Matrix classCovariance = classLists.get(i)->covariance(averageVector);
        determinant = classCovariance.determinant();
        try {
            classCovariance.inverse();
        } catch (DeterminantZero& determinantZero) {
            cout << determinantZero.what();
        }
        Matrix Wi = classCovariance.clone();
        Wi.multiplyWithConstant(-0.5);
        W.emplace(Ci, Wi);
        try {
            Vector wi = classCovariance.multiplyWithVectorFromLeft(averageVector);
            w.emplace(Ci, wi);
            w0i = -0.5 * (wi.dotProduct(averageVector) + log(determinant)) + log(priorDistribution.getProbability(Ci));
            w0.emplace(Ci, w0i);
        } catch (MatrixRowMismatch& mismatch1) {
        } catch (VectorSizeMismatch& mismatch2) {
        }
    }
}

/**
 * Loads the Qda model from an input file.
 * @param fileName File name of the Qda model.
 */
void QdaModel::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    GaussianModel::load(inputFile);
    LdaModel::load(inputFile);
    load(inputFile);
    inputFile.close();
}

/**
 * Loads a quadratic discriminant analysis model from an input model file.
 * @param inputFile Model file.
 */
void QdaModel::load(ifstream& inputFile){
    string classLabel;
    for (int i = 0; i < priorDistribution.size(); i++){
        inputFile >> classLabel;
        auto matrix = Matrix(inputFile);
        W.emplace(classLabel, matrix);
    }
}