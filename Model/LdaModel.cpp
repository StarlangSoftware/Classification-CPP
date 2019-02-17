//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <VectorSizeMismatch.h>
#include <cfloat>
#include "LdaModel.h"

/**
 * The calculateMetric method takes an {@link Instance} and a String as inputs. It returns the dot product of given Instance
 * and w0 plus w1.
 *
 * @param instance {@link Instance} input.
 * @param Ci       String input.
 * @return The dot product of given Instance and w0 plus w1.
 */
double LdaModel::calculateMetric(Instance *instance, string Ci) {
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
LdaModel::LdaModel(DiscreteDistribution priorDistribution, map<string, Vector> w, map<string, double> w0) {
    this->priorDistribution = move(priorDistribution);
    this->w = move(w);
    this->w0 = move(w0);
}
