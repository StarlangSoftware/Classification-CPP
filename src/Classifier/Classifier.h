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
    static string getMaximum(const vector<string>& classLabels);
    virtual void train(InstanceList& trainSet, Parameter* parameters) = 0;
    virtual void loadModel(const string& fileName) = 0;
    bool discreteCheck(Instance* instance) const;
    virtual Performance* test(const InstanceList& testSet) const;
    Performance* singleRun(Parameter* parameter, InstanceList& trainSet, const InstanceList& testSet);
    Model* getModel() const;
};


#endif //CLASSIFICATION_CLASSIFIER_H
