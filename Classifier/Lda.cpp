//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <iostream>
#include <VectorSizeMismatch.h>
#include <cmath>
#include "Lda.h"
#include "MatrixDimensionMismatch.h"
#include "DeterminantZero.h"
#include "MatrixColumnMismatch.h"
#include "../InstanceList/Partition.h"
#include "../InstanceList/InstanceListOfSameClass.h"
#include "../Model/LdaModel.h"

/**
 * Training algorithm for the linear discriminant analysis classifier (Introduction to Machine Learning, Alpaydin, 2015).
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void Lda::train(InstanceList &trainSet, Parameter *parameters) {
    string Ci;
    double w0i;
    map<string, double> w0;
    map<string, Vector> w;
    DiscreteDistribution priorDistribution = trainSet.classDistribution();
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
        Ci = dynamic_cast<InstanceListOfSameClass*>(classLists.get(i))->getClassLabel();
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
    model = new LdaModel(priorDistribution, w, w0);
}
