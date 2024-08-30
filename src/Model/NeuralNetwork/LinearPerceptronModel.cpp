//
// Created by olcay on 12.02.2019.
//

#include <fstream>
#include <MatrixColumnMismatch.h>
#include <MatrixDimensionMismatch.h>
#include <VectorSizeMismatch.h>
#include "LinearPerceptronModel.h"
#include "../../InstanceList/Partition.h"
#include "../../Model/DiscreteFeaturesNotAllowed.h"

/**
 * The calculateOutput method calculates the Matrix y by multiplying Matrix W with Vector x.
 */
void LinearPerceptronModel::calculateOutput() {
    try {
        y = W.multiplyWithVectorFromRight(x);
    } catch (MatrixColumnMismatch& matrixColumnMismatch) {
    }
}

/**
 * Loads a linear perceptron model from an input model file.
 * @param inputFile Model file.
 */
LinearPerceptronModel::LinearPerceptronModel(ifstream &inputFile) : NeuralNetworkModel(inputFile) {
    load(inputFile);
}

/**
 * Training algorithm for the linear perceptron algorithm. 20 percent of the data is separated as cross-validation
 * data used for selecting the best weights. 80 percent of the data is used for training the linear perceptron with
 * gradient descent.
 *
 * @param trainSet   Training data given to the algorithm
 * @param parameters Parameters of the linear perceptron.
 */
void LinearPerceptronModel::train(InstanceList& train, Parameter *params) {
    if (!discreteCheck(train.get(0))){
        throw DiscreteFeaturesNotAllowed();
    }
    classLabels = train.getDistinctClassLabels();
    K = classLabels.size();
    d = train.get(0)->continuousAttributeSize();
    Partition partition = Partition(train, ((LinearPerceptronParameter*) params)->getCrossValidationRatio(), params->getSeed(), true);
    InstanceList trainSet = *(partition.get(1));
    InstanceList validationSet = *(partition.get(0));
    LinearPerceptronParameter* parameters = (LinearPerceptronParameter*) params;
    int epoch;
    double learningRate;
    W = allocateLayerWeights(K, d + 1, default_random_engine(parameters->getSeed()));
    Matrix bestW = W.clone();
    auto* bestClassificationPerformance = new ClassificationPerformance(0.0);
    epoch = parameters->getEpoch();
    learningRate = parameters->getLearningRate();
    for (int i = 0; i < epoch; i++) {
        trainSet.shuffle(parameters->getSeed());
        for (int j = 0; j < trainSet.size(); j++) {
            createInputVector(trainSet.get(j));
            try {
                Vector rMinusY = calculateRMinusY(trainSet.get(j), x, W);
                Matrix deltaW = Matrix(rMinusY, x);
                deltaW.multiplyWithConstant(learningRate);
                W.add(deltaW);
            } catch (MatrixColumnMismatch& mismatch1) {
            } catch (MatrixDimensionMismatch& mismatch2) {
            } catch (VectorSizeMismatch& mismatch3) {
            }
        }
        ClassificationPerformance* currentClassificationPerformance = testClassifier(validationSet);
        if (currentClassificationPerformance->getAccuracy() > bestClassificationPerformance->getAccuracy()) {
            bestClassificationPerformance = currentClassificationPerformance;
            bestW = W.clone();
        }
        learningRate *= parameters->getEtaDecrease();
    }
    W = bestW;
}

/**
 * Loads the linear perceptron model from an input file.
 * @param fileName File name of the linear perceptron model.
 */
void LinearPerceptronModel::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    NeuralNetworkModel::load(inputFile);
    load(inputFile);
    inputFile.close();
}

/**
 * Loads a linear perceptron model from an input model file.
 * @param inputFile Model file.
 */
void LinearPerceptronModel::load(ifstream& inputFile){
    W = Matrix(inputFile);
}