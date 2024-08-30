//
// Created by olcay on 12.02.2019.
//

#ifndef CLASSIFICATION_LINEARPERCEPTRONMODEL_H
#define CLASSIFICATION_LINEARPERCEPTRONMODEL_H
#include "NeuralNetworkModel.h"
#include "../../Parameter/LinearPerceptronParameter.h"

class LinearPerceptronModel : public NeuralNetworkModel{
protected:
    Matrix W = Matrix(0, 0);
    void calculateOutput() override;
    void load(ifstream& inputFile);
public:
    LinearPerceptronModel() = default;
    explicit LinearPerceptronModel(ifstream& inputFile);
    void train(InstanceList& train, Parameter* params) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_LINEARPERCEPTRONMODEL_H
