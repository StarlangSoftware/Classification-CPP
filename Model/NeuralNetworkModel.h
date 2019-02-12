//
// Created by olcay on 12.02.2019.
//

#ifndef CLASSIFICATION_NEURALNETWORKMODEL_H
#define CLASSIFICATION_NEURALNETWORKMODEL_H


#include "ValidatedModel.h"

class NeuralNetworkModel : public ValidatedModel{
protected:
    vector<string> classLabels;
    int K, d;
    Vector x = Vector(0, 0.0), y = Vector(0, 0.0), r = Vector(0, 0.0);
    virtual void calculateOutput() = 0;
    Matrix allocateLayerWeights(int row, int column);
    Vector normalizeOutput(Vector o);
    void createInputVector(Instance* instance);
    Vector calculateHidden(Vector& input, Matrix weights);
    Vector calculateOneMinusHidden(Vector hidden);
    void calculateForwardSingleHiddenLayer(Matrix W, Matrix V);
    Vector calculateRMinusY(Instance* instance, Vector input, Matrix weights);
    string predictWithCompositeInstance(vector<string> possibleClassLabels);
public:
    explicit NeuralNetworkModel(InstanceList& trainSet);
    string predict(Instance* instance);
};


#endif //CLASSIFICATION_NEURALNETWORKMODEL_H
