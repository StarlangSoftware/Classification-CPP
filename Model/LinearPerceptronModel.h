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
    LinearPerceptronModel(InstanceList& trainSet, InstanceList& validationSet, LinearPerceptronParameter* parameters);
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_LINEARPERCEPTRONMODEL_H
