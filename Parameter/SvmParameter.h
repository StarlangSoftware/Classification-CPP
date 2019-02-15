//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_SVMPARAMETER_H
#define CLASSIFICATION_SVMPARAMETER_H
#include "Parameter.h"
#include "../Model/Svm/KernelType.h"

class SvmParameter : public Parameter {
private:
    KernelType kernelType;
    int degree;
    double gamma;
    double coefficient0;
    double C;
    bool shrinking = true;
public:
    SvmParameter(int seed, KernelType kernelType, int degree, double gamma, double coefficient0, double C);
    KernelType getKernelType();
    int getDegree();
    double getGamma();
    double getCoefficient0();
    double getC();
    bool isShrinking();
};


#endif //CLASSIFICATION_SVMPARAMETER_H
