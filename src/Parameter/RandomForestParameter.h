//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#ifndef CLASSIFICATION_RANDOMFORESTPARAMETER_H
#define CLASSIFICATION_RANDOMFORESTPARAMETER_H
#include "Parameter.h"
#include "BaggingParameter.h"

class RandomForestParameter : public BaggingParameter {
private:
    int attributeSubsetSize;
public:
    RandomForestParameter(int seed, int ensembleSize, int attributeSubsetSize);
    int getAttributeSubsetSize();
};


#endif //CLASSIFICATION_RANDOMFORESTPARAMETER_H
