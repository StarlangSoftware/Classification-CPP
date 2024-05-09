//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include <ostream>
#include <fstream>
#include <MatrixColumnMismatch.h>
#include <VectorSizeMismatch.h>
#include <MatrixDimensionMismatch.h>
#include "DeepNetworkModel.h"

/**
 * The allocateWeights method takes DeepNetworkParameters as an input. First it adds random weights to the ArrayList
 * of Matrix weights' first layer. Then it loops through the layers and adds random weights till the last layer.
 * At the end it adds random weights to the last layer and also sets the hiddenLayerSize value.
 *
 * @param parameters DeepNetworkParameter input.
 */
void DeepNetworkModel::allocateWeights(DeepNetworkParameter *parameters) {
    weights.push_back(allocateLayerWeights(parameters->getHiddenNodes(0), d + 1, default_random_engine(parameters->getSeed())));
    for (int i = 0; i < parameters->layerSize() - 1; i++) {
        weights.push_back(allocateLayerWeights(parameters->getHiddenNodes(i + 1), parameters->getHiddenNodes(i) + 1, default_random_engine(parameters->getSeed())));
    }
    weights.push_back(allocateLayerWeights(K, parameters->getHiddenNodes(parameters->layerSize() - 1) + 1, default_random_engine(parameters->getSeed())));
    hiddenLayerSize = parameters->layerSize();
}

/**
 * The setBestWeights method creates an vector of Matrix as bestWeights and clones the values of weights ArrayList
 * into this newly created vector.
 *
 * @return An vector clones from the weights ArrayList.
 */
vector<Matrix> DeepNetworkModel::setBestWeights() const{
    vector<Matrix> bestWeights;
    for (Matrix m : weights) {
        bestWeights.push_back(m.clone());
    }
    return bestWeights;
}

/**
 * Constructor that takes two InstanceList train set and validation set and DeepNetworkParameter as inputs.
 * First it sets the class labels, their sizes as K and the size of the continuous attributes as d of given train set and
 * allocates weights and sets the best weights. At each epoch, it shuffles the train set and loops through the each item of that train set,
 * it multiplies the weights Matrix with input Vector than applies the sigmoid function and stores the result as hidden and add bias.
 * Then updates weights and at the end it compares the performance of these weights with validation set. It updates the bestClassificationPerformance and
 * bestWeights according to the current situation. At the end it updates the learning rate via etaDecrease value and finishes
 * with clearing the weights.
 *
 * @param trainSet      InstanceList to be used as trainSet.
 * @param validationSet InstanceList to be used as validationSet.
 * @param parameters    DeepNetworkParameter input.
 */
DeepNetworkModel::DeepNetworkModel(InstanceList &trainSet, const InstanceList &validationSet,
                                   DeepNetworkParameter *parameters) : NeuralNetworkModel(trainSet){
    int epoch;
    double learningRate;
    vector<Matrix> bestWeights;
    vector<Matrix> deltaWeights;
    vector<Vector> hidden;
    vector<Vector> hiddenBiased;
    Vector tmph = Vector(0, 0.0), tmpHidden = Vector(0, 0.0);
    Vector activationDerivative = Vector(0, 0.0), oneMinusHidden = Vector(0, 0.0), one = Vector(0, 0.0);
    activationFunction = parameters->getActivationFunction();
    allocateWeights(parameters);
    bestWeights = setBestWeights();
    auto* bestClassificationPerformance = new ClassificationPerformance(0.0);
    epoch = parameters->getEpoch();
    learningRate = parameters->getLearningRate();
    for (int i = 0; i < epoch; i++) {
        trainSet.shuffle(parameters->getSeed());
        for (int j = 0; j < trainSet.size(); j++) {
            createInputVector(trainSet.get(j));
            try {
                hidden.clear();
                hiddenBiased.clear();
                deltaWeights.clear();
                for (int k = 0; k < hiddenLayerSize; k++) {
                    if (k == 0) {
                        hidden.push_back(calculateHidden(x, weights.at(k), activationFunction));
                    } else {
                        hidden.push_back(calculateHidden(hiddenBiased.at(k - 1), weights.at(k), activationFunction));
                    }
                    hiddenBiased.push_back(hidden.at(k).biased());
                }
                Vector rMinusY = calculateRMinusY(trainSet.get(j), hiddenBiased.at(hiddenLayerSize - 1), weights.at(weights.size() - 1));
                deltaWeights.insert(deltaWeights.begin(), Matrix(rMinusY, hiddenBiased.at(hiddenLayerSize - 1)));
                for (int k = weights.size() - 2; k >= 0; k--) {
                    if (k == weights.size() - 2){
                        tmph = weights.at(k + 1).multiplyWithVectorFromLeft(rMinusY);
                    } else {
                        tmph = weights.at(k + 1).multiplyWithVectorFromLeft(tmpHidden);
                    }
                    tmph.remove(0);
                    switch (activationFunction){
                        case ActivationFunction::SIGMOID:
                            oneMinusHidden = calculateOneMinusHidden(hidden.at(k));
                            activationDerivative = oneMinusHidden.elementProduct(hidden.at(k));
                            break;
                        case ActivationFunction::TANH:
                            one = Vector(hidden.size(), 1.0);
                            hidden.at(k).tanh();
                            activationDerivative = one.difference(hidden.at(k).elementProduct(hidden.at(k)));
                            break;
                        case ActivationFunction::RELU:
                            hidden.at(k).reluDerivative();
                            activationDerivative = hidden.at(k);
                            break;
                    }
                    tmpHidden = tmph.elementProduct(activationDerivative);
                    if (k == 0) {
                        deltaWeights.insert(deltaWeights.begin(), Matrix(tmpHidden, x));
                    } else {
                        deltaWeights.insert(deltaWeights.begin(), Matrix(tmpHidden, hiddenBiased.at(k - 1)));
                    }
                }
                for (int k = 0; k < weights.size(); k++) {
                    deltaWeights.at(k).multiplyWithConstant(learningRate);
                    weights.at(k).add(deltaWeights.at(k));
                }
            } catch (MatrixColumnMismatch& mismatch) {
            } catch (VectorSizeMismatch& mismatch) {
            } catch (MatrixDimensionMismatch& mismatch) {
            }
        }
        ClassificationPerformance* currentClassificationPerformance = testClassifier(validationSet);
        if (currentClassificationPerformance->getAccuracy() > bestClassificationPerformance->getAccuracy()) {
            bestClassificationPerformance = currentClassificationPerformance;
            bestWeights = setBestWeights();
        }
        learningRate *= parameters->getEtaDecrease();
    }
    weights.clear();
    for (const Matrix &m : bestWeights) {
        weights.push_back(m);
    }
}

/**
 * The calculateOutput method loops size of the weights times and calculate one hidden layer at a time and adds bias term.
 * At the end it updates the output y value.
 */
void DeepNetworkModel::calculateOutput() {
    Vector hidden = Vector(0, 0.0), hiddenBiased = Vector(0, 0.0);
    try {
        for (int i = 0; i < weights.size() - 1; i++) {
            if (i == 0) {
                hidden = calculateHidden(x, weights.at(i), activationFunction);
            } else {
                hidden = calculateHidden(hiddenBiased, weights.at(i), activationFunction);
            }
            hiddenBiased = hidden.biased();
        }
        y = weights.at(weights.size() - 1).multiplyWithVectorFromRight(hiddenBiased);
    } catch (MatrixColumnMismatch& matrixColumnMismatch) {
    }
}

/**
 * Loads a deep network model from an input model file.
 * @param inputFile Model file.
 */
DeepNetworkModel::DeepNetworkModel(ifstream &inputFile) : NeuralNetworkModel(inputFile) {
    inputFile >> hiddenLayerSize;
    for (int i = 0; i < hiddenLayerSize + 1; i++){
        weights.emplace_back(inputFile);
    }
    activationFunction = getActivationFunction(inputFile);
}
