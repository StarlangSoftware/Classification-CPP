//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_MODEL_H
#define CLASSIFICATION_MODEL_H


#include <map>
#include <vector>
#include "../Instance/Instance.h"
#include "../InstanceList/InstanceList.h"
#include "../Parameter/Parameter.h"
#include "../Performance/Performance.h"
#include "../Model/Model.h"

using namespace std;

class Model {
public:
    Model() = default;
    explicit Model(ifstream& inputFile) {};
    virtual string predict(Instance* instance) {return "";};
    virtual map<string, double> predictProbability(Instance* instance) {return map<string, double>();};
    virtual void serialize(ostream &outputFile) {};
    static string getMaximum(const vector<string>& classLabels);
    virtual void train(InstanceList& trainSet, Parameter* parameters) = 0;
    virtual void loadModel(const string& fileName) = 0;
    bool discreteCheck(Instance* instance) const;
    virtual Performance* test(const InstanceList& testSet);
    Performance* singleRun(Parameter* parameter, InstanceList& trainSet, const InstanceList& testSet);
};

#endif //CLASSIFICATION_MODEL_H
