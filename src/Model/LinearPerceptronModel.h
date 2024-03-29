//
// Created by olcay on 12.02.2019.
//

#ifndef CLASSIFICATION_LINEARPERCEPTRONMODEL_H
#define CLASSIFICATION_LINEARPERCEPTRONMODEL_H
#include "NeuralNetworkModel.h"
#include "../Parameter/LinearPerceptronParameter.h"

class LinearPerceptronModel : public NeuralNetworkModel{
protected:
    Matrix W = Matrix(0, 0);
    void calculateOutput() override;
public:
    explicit LinearPerceptronModel(InstanceList& trainSet);
    explicit LinearPerceptronModel(ifstream& inputFile);
    LinearPerceptronModel(InstanceList& trainSet, const InstanceList& validationSet, LinearPerceptronParameter* parameters);
};


#endif //CLASSIFICATION_LINEARPERCEPTRONMODEL_H
