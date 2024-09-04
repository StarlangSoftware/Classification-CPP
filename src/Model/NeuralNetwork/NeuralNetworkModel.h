//
// Created by olcay on 12.02.2019.
//

#ifndef CLASSIFICATION_NEURALNETWORKMODEL_H
#define CLASSIFICATION_NEURALNETWORKMODEL_H


#include "../ValidatedModel.h"
#include "../../Parameter/ActivationFunction.h"

class NeuralNetworkModel : public ValidatedModel{
protected:
    vector<string> classLabels;
    int K, d;
    Vector x = Vector(0, 0.0), y = Vector(0, 0.0), r = Vector(0, 0.0);
    virtual void calculateOutput() = 0;
    Matrix allocateLayerWeights(int row, int column, default_random_engine randomEngine);
    Vector normalizeOutput(const Vector& o) const;
    void createInputVector(Instance* instance);
    Vector calculateHidden(const Vector& input, const Matrix& weights, ActivationFunction activationFunction) const;
    Vector calculateOneMinusHidden(const Vector& hidden) const;
    void calculateForwardSingleHiddenLayer(const Matrix& W, const Matrix& V, ActivationFunction activationFunction);
    Vector calculateRMinusY(Instance* instance, const Vector& input, const Matrix& weights);
    string predictWithCompositeInstance(const vector<string>& possibleClassLabels) const;
    ActivationFunction getActivationFunction(ifstream& inputFile) const;
    void load(ifstream& inputFile);
    void initialize(InstanceList &train);
public:
    NeuralNetworkModel() = default;
    explicit NeuralNetworkModel(ifstream& inputFile);
    string predict(Instance* instance) override;
    map<string, double> predictProbability(Instance* instance) override;
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_NEURALNETWORKMODEL_H
