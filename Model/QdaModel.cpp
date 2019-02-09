//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <cfloat>
#include <VectorSizeMismatch.h>
#include <MatrixRowMismatch.h>
#include "QdaModel.h"

/**
 * The calculateMetric method takes an {@link Instance} and a String as inputs. It multiplies Matrix Wi with Vector xi
 * then calculates the dot product of it with xi. Then, again it finds the dot product of wi and xi and returns the summation with w0i.
 *
 * @param instance {@link Instance} input.
 * @param Ci       String input.
 * @return The result of Wi.multiplyWithVectorFromLeft(xi).dotProduct(xi) + wi.dotProduct(xi) + w0i.
 */
double QdaModel::calculateMetric(Instance *instance, string Ci) {
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
 * @param priorDistribution {@link DiscreteDistribution} input.
 * @param W                 {@link HashMap} of String and Matrix.
 * @param w                 {@link HashMap} of String and Vectors.
 * @param w0                {@link HashMap} of String and Double.
 */
QdaModel::QdaModel(DiscreteDistribution priorDistribution, map<string, Matrix> W, map<string, Vector> w,
                   map<string, double> w0) : LdaModel(move(priorDistribution), move(w), move(w0)) {
    this->W = move(W);
}
