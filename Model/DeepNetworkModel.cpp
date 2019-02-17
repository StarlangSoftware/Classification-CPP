//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include <MatrixColumnMismatch.h>
#include <VectorSizeMismatch.h>
#include <MatrixDimensionMismatch.h>
#include "DeepNetworkModel.h"

/**
 * The allocateWeights method takes {@link DeepNetworkParameter}s as an input. First it adds random weights to the {@link ArrayList}
 * of {@link Matrix} weights' first layer. Then it loops through the layers and adds random weights till the last layer.
 * At the end it adds random weights to the last layer and also sets the hiddenLayerSize value.
 *
 * @param parameters {@link DeepNetworkParameter} input.
 */
void DeepNetworkModel::allocateWeights(DeepNetworkParameter *parameters) {
    weights.push_back(allocateLayerWeights(parameters->getHiddenNodes(0), d + 1));
    for (int i = 0; i < parameters->layerSize() - 1; i++) {
        weights.push_back(allocateLayerWeights(parameters->getHiddenNodes(i + 1), parameters->getHiddenNodes(i) + 1));
    }
    weights.push_back(allocateLayerWeights(K, parameters->getHiddenNodes(parameters->layerSize() - 1) + 1));
    hiddenLayerSize = parameters->layerSize();
}

/**
 * The setBestWeights method creates an {@link vector} of Matrix as bestWeights and clones the values of weights {@link ArrayList}
 * into this newly created {@link vector}.
 *
 * @return An {@link vector} clones from the weights ArrayList.
 */
vector<Matrix> DeepNetworkModel::setBestWeights() {
    vector<Matrix> bestWeights;
    for (Matrix m : weights) {
        bestWeights.push_back(m.clone());
    }
    return bestWeights;
}

DeepNetworkModel::DeepNetworkModel(InstanceList &trainSet, InstanceList &validationSet,
                                   DeepNetworkParameter *parameters) : NeuralNetworkModel(trainSet){
    int epoch;
    double learningRate;
    vector<Matrix> bestWeights;
    vector<Matrix> deltaWeights;
    vector<Vector> hidden;
    vector<Vector> hiddenBiased;
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
                        hidden.push_back(calculateHidden(x, weights.at(k)));
                    } else {
                        hidden.push_back(calculateHidden(hiddenBiased.at(k - 1), weights.at(k)));
                    }
                    hiddenBiased.push_back(hidden.at(k).biased());
                }
                Vector rMinusY = calculateRMinusY(trainSet.get(j), hiddenBiased.at(hiddenLayerSize - 1), weights.at(weights.size() - 1));
                deltaWeights.insert(deltaWeights.begin(), Matrix(rMinusY, hiddenBiased.at(hiddenLayerSize - 1)));
                for (int k = weights.size() - 2; k >= 0; k--) {
                    Vector oneMinusHidden = calculateOneMinusHidden(hidden.at(k));
                    Vector tmph = deltaWeights.at(0).elementProduct(weights.at(k + 1)).sumOfRows();
                    tmph.remove(0);
                    Vector tmpHidden = oneMinusHidden.elementProduct(tmph);
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
                hidden = calculateHidden(x, weights.at(i));
            } else {
                hidden = calculateHidden(hiddenBiased, weights.at(i));
            }
            hiddenBiased = hidden.biased();
        }
        y = weights.at(weights.size() - 1).multiplyWithVectorFromRight(hiddenBiased);
    } catch (MatrixColumnMismatch& matrixColumnMismatch) {
    }
}
