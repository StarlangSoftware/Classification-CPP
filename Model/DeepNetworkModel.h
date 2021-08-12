//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_DEEPNETWORKMODEL_H
#define CLASSIFICATION_DEEPNETWORKMODEL_H


#include "NeuralNetworkModel.h"
#include "../Parameter/DeepNetworkParameter.h"

class DeepNetworkModel : public NeuralNetworkModel {
private:
    vector<Matrix> weights;
    int hiddenLayerSize;
    ActivationFunction activationFunction;
    void allocateWeights(DeepNetworkParameter* parameters);
    vector<Matrix> setBestWeights();
public:
    explicit DeepNetworkModel(ifstream& inputFile);
    DeepNetworkModel(InstanceList& trainSet, InstanceList& validationSet, DeepNetworkParameter* parameters);
    void serialize(ostream &outputFile) override;
protected:
    void calculateOutput() override;
};


#endif //CLASSIFICATION_DEEPNETWORKMODEL_H
