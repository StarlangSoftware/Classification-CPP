//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#include "QMatrix.h"

/**
 * Constructor that sets problem, parameter and double array y.
 *
 * @param problem   {@link Problem} input.
 * @param parameter {@link SvmParameter} input.
 * @param y         A double array input.
 */
QMatrix::QMatrix(const Problem& problem, SvmParameter *parameter, const vector<double>& y) {
    kernel = Kernel(problem.getL(), problem.getX(), parameter->getKernelType(), parameter->getDegree(), parameter->getGamma(), parameter->getCoefficient0());
    this->y.reserve(problem.getL());
    for (int i = 0; i < problem.getL(); i++) {
        this->y.push_back(y[i]);
    }
}

/**
 * The getQ method calculates y[i] * y[j] * kernel.function(i, j) and returns a new array with new values.
 *
 * @param i      Index to multiply values.
 * @param length Length of array.
 * @return A new array with new calculated values.
 */
vector<double> QMatrix::getQ(int i, int length) const{
    vector<double> data;
    data.reserve(length);
    for (int j = 0; j < length; j++) {
        data.push_back(y[i] * y[j] * kernel.function(i, j));
    }
    return data;
}

/**
 * The swapIndex method swaps the ith element with jth element of array y.
 *
 * @param i First index to swap.
 * @param j Second index to swap.
 */
void QMatrix::swapIndex(int i, int j) {
    kernel.swapIndex(i, j);
    double tmp = y[i];
    y[i] = y[j];
    y[j] = tmp;
}

QMatrix::QMatrix() = default;
