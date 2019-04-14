//
// Created by olcay on 12.02.2019.
//

#include <MatrixColumnMismatch.h>
#include <MatrixDimensionMismatch.h>
#include <VectorSizeMismatch.h>
#include "LinearPerceptronModel.h"

/**
 * Constructor that sets the {@link NeuralNetworkModel} nodes with given {@link InstanceList}.
 *
 * @param trainSet InstanceList that is used to train.
 */
LinearPerceptronModel::LinearPerceptronModel(InstanceList &trainSet) : NeuralNetworkModel(trainSet) {
}

/**
 * Constructor that takes {@link InstanceList}s as trainsSet and validationSet. Initially it allocates layer weights,
 * then creates an input vector by using given trainSet and finds error. Via the validationSet it finds the classification
 * performance and at the end it reassigns the allocated weight Matrix with the matrix that has the best accuracy.
 *
 * @param trainSet      InstanceList that is used to train.
 * @param validationSet InstanceList that is used to validate.
 * @param parameters    Linear perceptron parameters; learningRate, etaDecrease, crossValidationRatio, epoch.
 */
LinearPerceptronModel::LinearPerceptronModel(InstanceList &trainSet, InstanceList &validationSet,
                                             LinearPerceptronParameter *parameters) : NeuralNetworkModel(trainSet){
    int epoch;
    double learningRate;
    W = allocateLayerWeights(K, d + 1);
    Matrix bestW = W.clone();
    ClassificationPerformance* bestClassificationPerformance = new ClassificationPerformance(0.0);
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
 * The calculateOutput method calculates the {@link Matrix} y by multiplying Matrix W with {@link Vector} x.
 */
void LinearPerceptronModel::calculateOutput() {
    try {
        y = W.multiplyWithVectorFromRight(x);
    } catch (MatrixColumnMismatch& matrixColumnMismatch) {
    }
}

void LinearPerceptronModel::serialize(ostream &outputFile) {

}
