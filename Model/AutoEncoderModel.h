//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_AUTOENCODERMODEL_H
#define CLASSIFICATION_AUTOENCODERMODEL_H


#include "NeuralNetworkModel.h"
#include "../Parameter/MultiLayerPerceptronParameter.h"

class AutoEncoderModel : public NeuralNetworkModel{
protected:
    void calculateOutput() override;
private:
    Matrix V = Matrix(0), W = Matrix(0);
    void allocateWeights(int H);
    Vector predictInput(Instance* instance);
public:
    AutoEncoderModel(InstanceList& trainSet, InstanceList& validationSet, MultiLayerPerceptronParameter* parameters);
    Performance* testAutoEncoder(InstanceList& data);
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_AUTOENCODERMODEL_H
