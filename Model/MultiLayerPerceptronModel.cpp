//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include <MatrixColumnMismatch.h>
#include <MatrixRowMismatch.h>
#include <MatrixDimensionMismatch.h>
#include <VectorSizeMismatch.h>
#include "MultiLayerPerceptronModel.h"

/**
 * The allocateWeights method allocates layers' weights of Matrix W and V.
 *
 * @param H Integer value for weights.
 */
void MultiLayerPerceptronModel::allocateWeights(int H, default_random_engine randomEngine) {
    W = allocateLayerWeights(H, d + 1, randomEngine);
    V = allocateLayerWeights(K, H + 1, randomEngine);
}

MultiLayerPerceptronModel::MultiLayerPerceptronModel(InstanceList &trainSet, InstanceList &validationSet,
                                                     MultiLayerPerceptronParameter *parameters) : LinearPerceptronModel(trainSet){
    int epoch;
    double learningRate;
    Matrix bestW = Matrix(0), bestV = Matrix(0);
    allocateWeights(parameters->getHiddenNodes(), default_random_engine(parameters->getSeed()));
    bestW = W.clone();
    bestV = V.clone();
    auto* bestClassificationPerformance = new ClassificationPerformance(0.0);
    epoch = parameters->getEpoch();
    learningRate = parameters->getLearningRate();
    for (int i = 0; i < epoch; i++) {
        trainSet.shuffle(parameters->getSeed());
        for (int j = 0; j < trainSet.size(); j++) {
            createInputVector(trainSet.get(j));
            try {
                Vector hidden = calculateHidden(x, W);
                Vector hiddenBiased = hidden.biased();
                Vector rMinusY = calculateRMinusY(trainSet.get(j), hiddenBiased, V);
                Matrix deltaV = Matrix(rMinusY, hiddenBiased);
                Vector oneMinusHidden = calculateOneMinusHidden(hidden);
                Vector tmph = V.multiplyWithVectorFromLeft(rMinusY);
                tmph.remove(0);
                Vector tmpHidden = oneMinusHidden.elementProduct(hidden.elementProduct(tmph));
                Matrix deltaW = Matrix(tmpHidden, x);
                deltaV.multiplyWithConstant(learningRate);
                V.add(deltaV);
                deltaW.multiplyWithConstant(learningRate);
                W.add(deltaW);
            } catch (MatrixColumnMismatch& mismatch) {
            } catch (MatrixRowMismatch& mismatch) {
            } catch (MatrixDimensionMismatch& mismatch) {
            } catch (VectorSizeMismatch& mismatch) {
            }
        }
        ClassificationPerformance* currentClassificationPerformance = testClassifier(validationSet);
        if (currentClassificationPerformance->getAccuracy() > bestClassificationPerformance->getAccuracy()) {
            bestClassificationPerformance = currentClassificationPerformance;
            bestW = W.clone();
            bestV = V.clone();
        }
        learningRate *= parameters->getEtaDecrease();
    }
    W = bestW;
    V = bestV;
}

/**
 * The calculateOutput method calculates the forward single hidden layer by using Matrices W and V.
 */
void MultiLayerPerceptronModel::calculateOutput() {
    try {
        calculateForwardSingleHiddenLayer(W, V);
    } catch (MatrixColumnMismatch& matrixColumnMismatch) {
    }
}

void MultiLayerPerceptronModel::serialize(ostream &outputFile) {
    LinearPerceptronModel::serialize(outputFile);
    V.serialize(outputFile);
}

MultiLayerPerceptronModel::MultiLayerPerceptronModel(ifstream &inputFile) : LinearPerceptronModel(inputFile) {
    V = Matrix(inputFile);
}
