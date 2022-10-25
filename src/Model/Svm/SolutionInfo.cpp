//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#include "SolutionInfo.h"

/**
 * Constructor that sets rho and alpha values.
 *
 * @param rho   Double input rho.
 * @param alpha Double array of alpha values.
 */
SolutionInfo::SolutionInfo(double rho, const vector<double>& alpha) {
    this->rho = rho;
    this->alpha = alpha;
}

/**
 * Accessor for rho value.
 *
 * @return Rho value.
 */
double SolutionInfo::getRho() const{
    return rho;
}

/**
 * Accessor for alpha value. Returns the alpha at given index.
 *
 * @param index Index to retrieve alpha.
 * @return The alpha at given index.
 */
double SolutionInfo::getAlpha(int index) const{
    return alpha[index];
}

/**
 * Mutator for alpha values.
 *
 * @param index Index to change alpha value.
 * @param value Value to be set as new alpha value at given index.
 */
void SolutionInfo::setAlpha(int index, double value) {
    alpha[index] = value;
}
