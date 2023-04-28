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
    vector<Matrix> setBestWeights() const;
public:
    DeepNetworkModel(InstanceList& trainSet, const InstanceList& validationSet, DeepNetworkParameter* parameters);
    explicit DeepNetworkModel(ifstream& inputFile);
protected:
    void calculateOutput() override;
};


#endif //CLASSIFICATION_DEEPNETWORKMODEL_H
