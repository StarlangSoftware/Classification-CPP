//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#ifndef CLASSIFICATION_BAGGINGPARAMETER_H
#define CLASSIFICATION_BAGGINGPARAMETER_H
#include "Parameter.h"

class BaggingParameter : public Parameter{
protected:
    int ensembleSize;
public:
    BaggingParameter(int seed, int ensembleSize);
    int getEnsembleSize() const;
};


#endif //CLASSIFICATION_BAGGINGPARAMETER_H
