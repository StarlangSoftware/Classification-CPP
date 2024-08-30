//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_AUTOENCODERMODEL_H
#define CLASSIFICATION_AUTOENCODERMODEL_H


#include "NeuralNetworkModel.h"
#include "../../Parameter/MultiLayerPerceptronParameter.h"

class AutoEncoderModel : public NeuralNetworkModel{
protected:
    void calculateOutput() override;
private:
    Matrix V = Matrix(0), W = Matrix(0);
    void allocateWeights(int H, default_random_engine randomEngine);
    Vector predictInput(Instance* instance);
public:
    AutoEncoderModel(InstanceList& trainSet, const InstanceList& validationSet, MultiLayerPerceptronParameter* parameters);
    Performance* testAutoEncoder(const InstanceList& data);
    void serialize(ostream &outputFile) override;
    void train(InstanceList& train, Parameter* params) override;
    Performance* test(const InstanceList& testSet) override;
};


#endif //CLASSIFICATION_AUTOENCODERMODEL_H
