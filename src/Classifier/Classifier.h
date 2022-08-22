//
// Created by olcay on 29.01.2019.
//

#ifndef CLASSIFICATION_CLASSIFIER_H
#define CLASSIFICATION_CLASSIFIER_H

#include <vector>
#include "../InstanceList/InstanceList.h"
#include "../Parameter/Parameter.h"
#include "../Performance/Performance.h"
#include "../Model/Model.h"

using namespace std;

class Classifier {
protected:
    Model* model = nullptr;
public:
    static string getMaximum(vector<string> classLabels);
    virtual void train(InstanceList& trainSet, Parameter* parameters) = 0;
    bool discreteCheck(Instance* instance);
    virtual Performance* test(InstanceList testSet);
    Performance* singleRun(Parameter* parameter, InstanceList& trainSet, InstanceList& testSet);
    Model* getModel();
};


#endif //CLASSIFICATION_CLASSIFIER_H
