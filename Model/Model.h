//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_MODEL_H
#define CLASSIFICATION_MODEL_H


#include "../Instance/Instance.h"
#include <map>
using namespace std;

class Model {
public:
    Model() = default;
    explicit Model(ifstream& inputFile) {};
    virtual string predict(Instance* instance) {return "";};
    virtual map<string, double> predictProbability(Instance* instance) {return map<string, double>();};
    virtual void serialize(ostream &outputFile) {};
};

#endif //CLASSIFICATION_MODEL_H
