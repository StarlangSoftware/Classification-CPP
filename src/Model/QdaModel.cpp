//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <cfloat>
#include <fstream>
#include <VectorSizeMismatch.h>
#include <MatrixRowMismatch.h>
#include "QdaModel.h"

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
 * The constructor which sets the priorDistribution, w w1 and HashMap of String Matrix.
 *
 * @param priorDistribution DiscreteDistribution input.
 * @param W                 HashMap of String and Matrix.
 * @param w                 HashMap of String and Vectors.
 * @param w0                HashMap of String and Double.
 */
QdaModel::QdaModel(const DiscreteDistribution& priorDistribution, const map<string, Matrix>& W, const map<string, Vector>& w,
                   const map<string, double>& w0) : LdaModel(priorDistribution, w, w0) {
    this->W = W;
}

/**
 * Loads a quadratic discriminant analysis model from an input model file.
 * @param inputFile Model file.
 */
QdaModel::QdaModel(ifstream &inputFile) : LdaModel(inputFile) {
    string classLabel;
    for (int i = 0; i < priorDistribution.size(); i++){
        inputFile >> classLabel;
        auto matrix = Matrix(inputFile);
        W.emplace(classLabel, matrix);
    }
}
