//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#include "SvmParameter.h"

/**
 * Parameters of the Support Vector Machine classifier.
 *
 * @param seed         Seed is used for random number generation.
 * @param kernelType   Specifies the KernelType to be used in the algorithm. It can be ona of the LINEAR, POLYNOM, RBF or SIGMOID.
 * @param degree       Degree of the polynomial kernel function.
 * @param gamma        Kernel coefficient for ?RBF, POLYNOM and SIGMOID.
 * @param coefficient0 Independent term in kernel function. It is only significant in POLYNOM and SIGMOID.
 * @param C            C is a regularization parameter which controls the trade off between the achieving a low
 *                     training error and a low testing error.
 */
SvmParameter::SvmParameter(int seed, KernelType kernelType, int degree, double gamma, double coefficient0, double C) : Parameter(seed){
    this->kernelType = kernelType;
    this->degree = degree;
    this->gamma = gamma;
    this->coefficient0 = coefficient0;
    this->C = C;
}

/**
 * Accessor for the kernelType.
 *
 * @return The kernelType.
 */
KernelType SvmParameter::getKernelType() const{
    return kernelType;
}

/**
 * Accessor for the degree.
 *
 * @return The degree.
 */
int SvmParameter::getDegree() const{
    return degree;
}

/**
 * Accessor for the gamma.
 *
 * @return The gamma.
 */
double SvmParameter::getGamma() const{
    return gamma;
}

/**
 * Accessor for the coefficient0.
 *
 * @return The coefficient0.
 */
double SvmParameter::getCoefficient0() const{
    return coefficient0;
}

/**
 * Accessor for the C.
 *
 * @return The C.
 */
double SvmParameter::getC() const{
    return C;
}

/**
 * Accessor for the shrinking.
 *
 * @return The shrinking.
 */
bool SvmParameter::isShrinking() const{
    return shrinking;
}
