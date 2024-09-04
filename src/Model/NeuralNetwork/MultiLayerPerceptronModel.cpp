//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#include <fstream>
#include <MatrixColumnMismatch.h>
#include <MatrixRowMismatch.h>
#include <MatrixDimensionMismatch.h>
#include <VectorSizeMismatch.h>
#include "MultiLayerPerceptronModel.h"
#include "../../InstanceList/Partition.h"
#include "../../Model/DiscreteFeaturesNotAllowed.h"

/**
 * The allocateWeights method allocates layers' weights of Matrix W and V.
 *
 * @param H Integer value for weights.
 */
void MultiLayerPerceptronModel::allocateWeights(int H, default_random_engine randomEngine) {
    W = allocateLayerWeights(H, d + 1, randomEngine);
    V = allocateLayerWeights(K, H + 1, randomEngine);
}

/**
 * The calculateOutput method calculates the forward single hidden layer by using Matrices W and V.
 */
void MultiLayerPerceptronModel::calculateOutput() {
    try {
        calculateForwardSingleHiddenLayer(W, V, activationFunction);
    } catch (MatrixColumnMismatch& matrixColumnMismatch) {
    }
}

/**
 * Loads a multi-layer perceptron model from an input model file.
 * @param inputFile Model file.
 */
MultiLayerPerceptronModel::MultiLayerPerceptronModel(ifstream& inputFile) : LinearPerceptronModel(inputFile){
    load(inputFile);
}

/**
 * Training algorithm for the multilayer perceptron algorithm. 20 percent of the data is separated as cross-validation
 * data used for selecting the best weights. 80 percent of the data is used for training the multilayer perceptron with
 * gradient descent.
 *
 * @param trainSet   Training data given to the algorithm
 * @param parameters Parameters of the multilayer perceptron.
 */
void MultiLayerPerceptronModel::train(InstanceList &train, Parameter *params) {
    initialize(train);
    Partition partition = Partition(train, ((MultiLayerPerceptronParameter*) params)->getCrossValidationRatio(), params->getSeed(), true);
    InstanceList trainSet = *(partition.get(1));
    InstanceList validationSet = *(partition.get(0));
    MultiLayerPerceptronParameter* parameters = (MultiLayerPerceptronParameter*) params;
    int epoch;
    double learningRate;
    Matrix bestW = Matrix(0), bestV = Matrix(0);
    Vector activationDerivative = Vector(0, 0.0), oneMinusHidden = Vector(0, 0.0), one = Vector(0, 0.0);
    activationFunction = parameters->getActivationFunction();
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
                Vector hidden = calculateHidden(x, W, activationFunction);
                Vector hiddenBiased = hidden.biased();
                Vector rMinusY = calculateRMinusY(trainSet.get(j), hiddenBiased, V);
                Matrix deltaV = Matrix(rMinusY, hiddenBiased);
                Vector tmph = V.multiplyWithVectorFromLeft(rMinusY);
                tmph.remove(0);
                switch (activationFunction){
                    case ActivationFunction::SIGMOID:
                        oneMinusHidden = calculateOneMinusHidden(hidden);
                        activationDerivative = oneMinusHidden.elementProduct(hidden);
                        break;
                    case ActivationFunction::TANH:
                        one = Vector(hidden.getSize(), 1.0);
                        hidden.tanh();
                        activationDerivative = one.difference(hidden.elementProduct(hidden));
                        break;
                    case ActivationFunction::RELU:
                        hidden.reluDerivative();
                        activationDerivative = hidden;
                        break;
                }
                Vector tmpHidden = tmph.elementProduct(activationDerivative);
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
 * Loads the multi-layer perceptron model from an input file.
 * @param fileName File name of the multi-layer perceptron model.
 */
void MultiLayerPerceptronModel::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    NeuralNetworkModel::load(inputFile);
    LinearPerceptronModel::load(inputFile);
    load(inputFile);
    inputFile.close();
}

void MultiLayerPerceptronModel::load(ifstream& inputFile){
    V = Matrix(inputFile);
    activationFunction = getActivationFunction(inputFile);
}