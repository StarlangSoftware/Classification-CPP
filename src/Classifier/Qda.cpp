//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <fstream>
#include <DeterminantZero.h>
#include <iostream>
#include <cmath>
#include <VectorSizeMismatch.h>
#include <MatrixRowMismatch.h>
#include "Qda.h"
#include "../InstanceList/Partition.h"
#include "../InstanceList/InstanceListOfSameClass.h"
#include "../Model/QdaModel.h"
#include "DiscreteFeaturesNotAllowed.h"

/**
 * Training algorithm for the quadratic discriminant analysis classifier (Introduction to Machine Learning, Alpaydin, 2015).
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void Qda::train(InstanceList& trainSet, Parameter *parameters) {
    if (!discreteCheck(trainSet.get(0))){
        throw DiscreteFeaturesNotAllowed();
    }
    string Ci;
    double determinant, w0i;
    map<string, double> w0;
    map<string, Vector> w;
    map<string, Matrix> W;
    Partition classLists = Partition(trainSet);
    DiscreteDistribution priorDistribution = trainSet.classDistribution();
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
    model = new QdaModel(priorDistribution, W, w, w0);
}

void Qda::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new QdaModel(inputFile);
    inputFile.close();
}
