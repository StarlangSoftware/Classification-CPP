//
// Created by olcay on 31.01.2019.
//

#include "ConfusionMatrix.h"

ConfusionMatrix::ConfusionMatrix() {

}

/**
 * Constructor that sets the class labels ArrayList and creates new HashMap matrix
 *
 * @param classLabels ArrayList of String.
 */
ConfusionMatrix::ConfusionMatrix(const vector<string>& classLabels) {
    this->classLabels = classLabels;
}

/**
 * The classify method takes two Strings; actual class and predicted class as inputs. If the matrix map contains
 * given actual class String as a key, it then assigns the corresponding object of that key to a CounterHashMap, if not
 * it creates a new CounterHashMap. Then, it puts the given predicted class String to the counterHashMap and
 * also put this counterHashMap to the matrix map together with the given actual class String.
 *
 * @param actualClass    String input actual class.
 * @param predictedClass String input predicted class.
 */
void ConfusionMatrix::classify(const string& actualClass, const string& predictedClass) {
    CounterHashMap<string> counterHashMap;
    if (matrix.contains(actualClass)) {
        counterHashMap = matrix.find(actualClass)->second;
    }
    counterHashMap.put(predictedClass);
    matrix.insert_or_assign(actualClass, counterHashMap);
}

/**
 * The addConfusionMatrix method takes a ConfusionMatrix as an input and loops through actual classes of that HashMap
 * and initially gets one row at a time. Then it puts the current row to the matrix HashMap together with the actual class string.
 *
 * @param confusionMatrix ConfusionMatrix input.
 */
void ConfusionMatrix::addConfusionMatrix(const ConfusionMatrix& confusionMatrix) {
    for (auto &it : confusionMatrix.matrix) {
        CounterHashMap<string> rowToBeAdded = it.second;
        if (matrix.contains(it.first)) {
            CounterHashMap<string> currentRow = matrix.find(it.first)->second;
            currentRow.add(rowToBeAdded);
            matrix.insert_or_assign(it.first, currentRow);
        } else {
            matrix.emplace(it.first, rowToBeAdded);
        }
    }
}

/**
 * The sumOfElements method loops through the keys in matrix HashMap and returns the summation of all the values of the keys.
 * I.e: TP+TN+FP+FN.
 *
 * @return The summation of values.
 */
double ConfusionMatrix::sumOfElements() const{
    double result = 0;
    for (auto& it : matrix) {
        result += it.second.sumOfCounts();
    }
    return result;
}

/**
 * The trace method loops through the keys in matrix HashMap and if the current key contains the actual key,
 * it accumulates the corresponding values. I.e: TP+TN.
 *
 * @return Summation of values.
 */
double ConfusionMatrix::trace() const{
    double result = 0;
    for (auto& it : matrix) {
        if (it.second.containsKey(it.first)) {
            result += it.second.count(it.first);
        }
    }
    return result;
}

/**
 * The columnSum method takes a String predicted class as input, and loops through the keys in matrix HashMap.
 * If the current key contains the predicted class String, it accumulates the corresponding values. I.e: TP+FP.
 *
 * @param predictedClass String input predicted class.
 * @return Summation of values.
 */
double ConfusionMatrix::columnSum(const string& predictedClass) const{
    double result = 0;
    for (auto& it : matrix) {
        if (it.second.containsKey(predictedClass)) {
            result += it.second.count(predictedClass);
        }
    }
    return result;
}

/**
 * The getAccuracy method returns the result of  TP+TN / TP+TN+FP+FN
 *
 * @return the result of  TP+TN / TP+TN+FP+FN
 */
double ConfusionMatrix::getAccuracy() const{
    return trace() / sumOfElements();
}

/**
 * The precision method loops through the class labels and returns the resulting Array which has the result of TP/FP+TP.
 *
 * @return The result of TP/FP+TP.
 */
double *ConfusionMatrix::precision() const{
    auto* result = new double[classLabels.size()];
    for (int i = 0; i < classLabels.size(); i++) {
        string actualClass = classLabels.at(i);
        if (matrix.contains(actualClass)) {
            result[i] = matrix.find(actualClass)->second.count(actualClass) / columnSum(actualClass);
        }
    }
    return result;
}

/**
 * The recall method loops through the class labels and returns the resulting Array which has the result of TP/FN+TP.
 *
 * @return The result of TP/FN+TP.
 */
double *ConfusionMatrix::recall() const{
    auto* result = new double[classLabels.size()];
    for (int i = 0; i < classLabels.size(); i++) {
        string actualClass = classLabels.at(i);
        if (matrix.contains(actualClass)) {
            result[i] = (matrix.find(actualClass)->second.count(actualClass) + 0.0) / matrix.find(actualClass)->second.sumOfCounts();
        }
    }
    return result;
}

/**
 * The fMeasure method loops through the class labels and returns the resulting Array which has the average of
 * recall and precision.
 *
 * @return The average of recall and precision.
 */
double *ConfusionMatrix::fMeasure() const{
    double* precisionValues = precision();
    double* recallValues = recall();
    auto* result = new double[classLabels.size()];
    for (int i = 0; i < classLabels.size(); i++) {
        result[i] = 2 / (1 / precisionValues[i] + 1 / recallValues[i]);
    }
    delete precisionValues;
    delete recallValues;
    return result;
}

/**
 * The weightedFMeasure method loops through the class labels and returns the resulting Array which has the weighted average of
 * recall and precision.
 *
 * @return The weighted average of recall and precision.
 */
double ConfusionMatrix::weightedFMeasure() const{
    double* fMeasureValues = fMeasure();
    double sum = 0;
    for (int i = 0; i < classLabels.size(); i++) {
        string actualClass = classLabels.at(i);
        sum += fMeasureValues[i] * matrix.find(actualClass)->second.sumOfCounts();
    }
    return sum / sumOfElements();
}
