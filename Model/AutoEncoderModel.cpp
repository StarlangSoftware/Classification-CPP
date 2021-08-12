//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include <cfloat>
#include <MatrixColumnMismatch.h>
#include <MatrixRowMismatch.h>
#include <MatrixDimensionMismatch.h>
#include <VectorSizeMismatch.h>
#include "AutoEncoderModel.h"

/**
 * The allocateWeights method takes an integer number and sets layer weights of W and V matrices according to given number.
 *
 * @param H Integer input.
 */
void AutoEncoderModel::allocateWeights(int H, default_random_engine randomEngine) {
    W = allocateLayerWeights(H, d + 1, randomEngine);
    V = allocateLayerWeights(K, H + 1, randomEngine);
}

/**
 * The {@link AutoEncoderModel} method takes two {@link InstanceList}s as inputs; train set and validation set. First it allocates
 * the weights of W and V matrices using given {@link MultiLayerPerceptronParameter} and takes the clones of these matrices as the bestW and bestV.
 * Then, it gets the epoch and starts to iterate over them. First it shuffles the train set and tries to find the new W and V matrices.
 * At the end it tests the autoencoder with given validation set and if its performance is better than the previous one,
 * it reassigns the bestW and bestV matrices. Continue to iterate with a lower learning rate till the end of an episode.
 *
 * @param trainSet      {@link InstanceList} to use as train set.
 * @param validationSet {@link InstanceList} to use as validation set.
 * @param parameters    {@link MultiLayerPerceptronParameter} is used to get the parameters.
 */
AutoEncoderModel::AutoEncoderModel(InstanceList &trainSet, InstanceList &validationSet,
                                   MultiLayerPerceptronParameter *parameters) : NeuralNetworkModel(trainSet){
    Matrix bestW = Matrix(0), bestV = Matrix(0);
    int epoch;
    double learningRate;
    K = trainSet.get(0)->continuousAttributeSize();
    allocateWeights(parameters->getHiddenNodes(), default_random_engine(parameters->getSeed()));
    bestW = W.clone();
    bestV = V.clone();
    auto* bestPerformance = new Performance(DBL_MAX);
    epoch = parameters->getEpoch();
    learningRate = parameters->getLearningRate();
    for (int i = 0; i < epoch; i++) {
        trainSet.shuffle(parameters->getSeed());
        for (int j = 0; j < trainSet.size(); j++) {
            createInputVector(trainSet.get(j));
            r = trainSet.get(j)->toVector();
            try {
                Vector hidden = calculateHidden(x, W, ActivationFunction::SIGMOID);
                Vector hiddenBiased = hidden.biased();
                y = V.multiplyWithVectorFromRight(hiddenBiased);
                Vector rMinusY = r.difference(y);
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
            } catch (MatrixColumnMismatch& mismatch1) {
            } catch (MatrixRowMismatch& mismatch2) {
            } catch (MatrixDimensionMismatch& mismatch3){
            } catch (VectorSizeMismatch& mismatch4) {
            }
        }
        Performance* currentPerformance = testAutoEncoder(validationSet);
        if (currentPerformance->getErrorRate() < bestPerformance->getErrorRate()) {
            bestPerformance = currentPerformance;
            bestW = W.clone();
            bestV = V.clone();
        }
        learningRate *= 0.95;
    }
    W = bestW;
    V = bestV;
}

/**
 * The testAutoEncoder method takes an {@link InstanceList} as an input and tries to predict a value and finds the difference with the
 * actual value for each item of that InstanceList. At the end, it returns an error rate by finding the mean of total errors.
 *
 * @param data {@link InstanceList} to use as validation set.
 * @return Error rate by finding the mean of total errors.
 */
Performance *AutoEncoderModel::testAutoEncoder(InstanceList &data) {
    double total = data.size();
    double error = 0.0;
    for (int i = 0; i < total; i++) {
        y = predictInput(data.get(i));
        r = data.get(i)->toVector();
        try {
            error += r.difference(y).dotProduct();
        } catch (VectorSizeMismatch& vectorSizeMismatch) {
        }
    }
    return new Performance(error / total);
}

/**
 * The predictInput method takes an {@link Instance} as an input and calculates a forward single hidden layer and returns the predicted value.
 *
 * @param instance {@link Instance} to predict.
 * @return Predicted value.
 */
Vector AutoEncoderModel::predictInput(Instance *instance) {
    createInputVector(instance);
    try {
        calculateForwardSingleHiddenLayer(W, V, ActivationFunction::SIGMOID);
        return y;
    } catch (MatrixColumnMismatch& matrixColumnMismatch) {
    }
}

/**
 * The calculateOutput method calculates a forward single hidden layer.
 */
void AutoEncoderModel::calculateOutput() {
    try {
        calculateForwardSingleHiddenLayer(W, V, ActivationFunction::SIGMOID);
    } catch (MatrixColumnMismatch& matrixColumnMismatch) {
    }
}

void AutoEncoderModel::serialize(ostream &outputFile) {

}
