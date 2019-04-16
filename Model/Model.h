//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_MODEL_H
#define CLASSIFICATION_MODEL_H


#include "../Instance/Instance.h"

class Model {
public:
    Model() = default;
    explicit Model(ifstream& inputFile) {};
    virtual string predict(Instance* instance) = 0;
    virtual void serialize(ostream &outputFile) = 0;
};


#endif //CLASSIFICATION_MODEL_H
