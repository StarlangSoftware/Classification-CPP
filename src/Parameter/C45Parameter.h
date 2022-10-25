//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#ifndef CLASSIFICATION_C45PARAMETER_H
#define CLASSIFICATION_C45PARAMETER_H
#include "Parameter.h"

class C45Parameter : public Parameter {
private:
    bool prune;
    double crossValidationRatio;
public:
    C45Parameter(int seed, bool prune, double crossValidationRatio);
    bool isPrune() const;
    double getCrossValidationRatio() const;
};


#endif //CLASSIFICATION_C45PARAMETER_H
