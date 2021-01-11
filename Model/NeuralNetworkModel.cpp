//
// Created by olcay on 12.02.2019.
//
#include <cmath>
#include <fstream>
#include <cfloat>
#include "../Instance/CompositeInstance.h"
#include "NeuralNetworkModel.h"

/**
 * Constructor that sets the class labels, their sizes as K and the size of the continuous attributes as d.
 *
 * @param trainSet {@link InstanceList} to use as train set.
 */
NeuralNetworkModel::NeuralNetworkModel(InstanceList& trainSet) {
    classLabels = trainSet.getDistinctClassLabels();
    K = classLabels.size();
    d = trainSet.get(0)->continuousAttributeSize();
}

/**
 * The allocateLayerWeights method returns a new {@link Matrix} with random weights.
 *
 * @param row    Number of rows.
 * @param column Number of columns.
 * @return Matrix with random weights.
 */
Matrix NeuralNetworkModel::allocateLayerWeights(int row, int column, default_random_engine randomEngine) {
    return Matrix(row, column, -0.01, +0.01, randomEngine);
}

/**
 * The normalizeOutput method takes an input {@link Vector} o, gets the result for e^o of each element of o,
 * then sums them up. At the end, divides the each e^o by the summation.
 *
 * @param o Vector to normalize.
 * @return Normalized vector.
 */
Vector NeuralNetworkModel::normalizeOutput(Vector o) {
    double sum = 0.0;
    vector<double> values(o.getSize());
    for (int i = 0; i < o.getSize(); i++)
        sum += exp(o.getValue(i));
    for (int i = 0; i < o.getSize(); i++)
        values[i] = exp(o.getValue(i)) / sum;
    return Vector(values);
}

/**
 * The createInputVector method takes an {@link Instance} as an input. It converts given Instance to the {@link java.util.Vector}
 * and insert 1.0 to the first element.
 *
 * @param instance Instance to insert 1.0.
 */
void NeuralNetworkModel::createInputVector(Instance* instance) {
    x = instance->toVector();
    x.insert(0, 1.0);
}

/**
 * The calculateHidden method takes a {@link Vector} input and {@link Matrix} weights, It multiplies the weights
 * Matrix with given input Vector than applies the sigmoid function and returns the result.
 *
 * @param input   Vector to multiply weights.
 * @param weights Matrix is multiplied with input Vector.
 * @return Result of sigmoid function.
 */
Vector NeuralNetworkModel::calculateHidden(Vector& input, Matrix weights) {
    Vector z = weights.multiplyWithVectorFromRight(input);
    z.sigmoid();
    return z;
}

/**
 * The calculateOneMinusHidden method takes a {@link java.util.Vector} as input. It creates a Vector of ones and
 * returns the difference between given Vector.
 *
 * @param hidden Vector to find difference.
 * @return Returns the difference between ones Vector and input Vector.
 * @throws VectorSizeMismatch Return: Number of items in both vectors must be the same.
 */
Vector NeuralNetworkModel::calculateOneMinusHidden(Vector hidden) {
    Vector one = Vector(hidden.getSize(), 1.0);
    return one.difference(hidden);
}

/**
 * The calculateForwardSingleHiddenLayer method takes two matrices W and V. First it multiplies W with x, then
 * multiplies V with the result of the previous multiplication.
 *
 * @param W Matrix to multiply with x.
 * @param V Matrix to multiply.
 */
void NeuralNetworkModel::calculateForwardSingleHiddenLayer(Matrix W, Matrix V) {
    Vector hidden = calculateHidden(x, W);
    Vector hiddenBiased = hidden.biased();
    y = V.multiplyWithVectorFromRight(hiddenBiased);
}

/**
 * The calculateRMinusY method creates a new {@link java.util.Vector} with given Instance, then it multiplies given
 * input Vector with given weights Matrix. After normalizing the output, it return the difference between the newly created
 * Vector and normalized output.
 *
 * @param instance Instance is used to get class labels.
 * @param input    Vector to multiply weights.
 * @param weights  Matrix of weights/
 * @return Difference between newly created Vector and normalized output.
 */
Vector NeuralNetworkModel::calculateRMinusY(Instance *instance, Vector input, Matrix weights) {
    r = Vector(K, std::find(classLabels.begin(), classLabels.end(), instance->getClassLabel()) - classLabels.begin(), 1.0);
    Vector o = weights.multiplyWithVectorFromRight(input);
    y = normalizeOutput(o);
    return r.difference(y);
}

/**
 * The predictWithCompositeInstance method takes an ArrayList possibleClassLabels. It returns the class label
 * which has the maximum value of y.
 *
 * @param possibleClassLabels ArrayList that has the class labels.
 * @return The class label which has the maximum value of y.
 */
string NeuralNetworkModel::predictWithCompositeInstance(vector<string> possibleClassLabels) {
    string predictedClass = possibleClassLabels.at(0);
    double maxY = -DBL_MAX;
    for (int i = 0; i < classLabels.size(); i++) {
        if (std::find(possibleClassLabels.begin(), possibleClassLabels.end(), classLabels.at(i)) != possibleClassLabels.end() && y.getValue(i) > maxY) {
            maxY = y.getValue(i);
            predictedClass = classLabels.at(i);
        }
    }
    return predictedClass;
}

/**
 * The predict method takes an {@link Instance} as an input, converts it to a Vector and calculates the {@link Matrix} y by
 * multiplying Matrix W with {@link Vector} x. Then it returns the class label which has the maximum y value.
 *
 * @param instance Instance to predict.
 * @return The class lable which has the maximum y.
 */
string NeuralNetworkModel::predict(Instance *instance) {
    createInputVector(instance);
    calculateOutput();
    if (instance->isComposite()) {
        return predictWithCompositeInstance(((CompositeInstance*)instance)->getPossibleClassLabels());
    } else {
        return classLabels.at(y.maxIndex());
    }
}

void NeuralNetworkModel::serialize(ostream &outputFile) {
    outputFile << K << "\n";
    outputFile << d << "\n";
    for (const string& classLabel : classLabels){
        outputFile << classLabel << "\n";
    }
}

NeuralNetworkModel::NeuralNetworkModel(ifstream &inputFile) {
    string classLabel;
    inputFile >> K;
    inputFile >> d;
    for (int i = 0; i < K; i++){
        inputFile >> classLabel;
        classLabels.push_back(classLabel);
    }
}
