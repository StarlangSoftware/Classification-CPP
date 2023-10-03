//
// Created by olcay on 31.01.2019.
//

#include <string>
#include <fstream>
#include <cmath>
#include "ExperimentPerformance.h"
#include "ClassificationAlgorithmExpectedException.h"
#include "ClassificationPerformance.h"

/**
 * A constructor which creates a new ArrayList of Performance as results.
 */
ExperimentPerformance::ExperimentPerformance() = default;

/**
 * A constructor that takes a file name as an input and takes the inputs from that file assigns these inputs to the errorRate
 * and adds them to the results ArrayList as a new Performance.
 *
 * @param fileName String input.
 */
ExperimentPerformance::ExperimentPerformance(const string& fileName) {
    string performance;
    containsDetails = false;
    ifstream inputFile;
    inputFile.open(fileName, ifstream::in);
    while (inputFile.good()) {
        getline(inputFile, performance);
        results.push_back(new Performance(stod(performance)));
    }
}

/**
 * The add method takes a Performance as an input and adds it to the results ArrayList.
 *
 * @param performance Performance input.
 */
void ExperimentPerformance::add(Performance *performance) {
    containsDetails = performance->containsDetails();
    classification = performance->isClassification();
    results.push_back(performance);
}

/**
 * The numberOfExperiments method returns the size of the results vector.
 *
 * @return The results vector.
 */
int ExperimentPerformance::numberOfExperiments() const{
    return results.size();
}

/**
 * The getErrorRate method takes an index as an input and returns the errorRate at given index of results vector.
 *
 * @param index Index of results vector to retrieve.
 * @return The errorRate at given index of results vector.
 */
double ExperimentPerformance::getErrorRate(int index) const{
    return results.at(index)->getErrorRate();
}

/**
 * The getAccuracy method takes an index as an input. It returns the accuracy of a Performance at given index of results vector.
 *
 * @param index Index of results vector to retrieve.
 * @return The accuracy of a Performance at given index of results vector.
 */
double ExperimentPerformance::getAccuracy(int index) const{
    if (results.at(index)->isClassification()) {
        return ((ClassificationPerformance*)(results.at(index)))->getAccuracy();
    } else {
        throw ClassificationAlgorithmExpectedException();
    }
}

/**
 * The meanPerformance method loops through the performances of results ArrayList and sums up the errorRates of each then
 * returns a new Performance with the mean of that summation.
 *
 * @return A new Performance with the mean of the summation of errorRates.
 */
Performance *ExperimentPerformance::meanPerformance() const{
    double sumError = 0;
    for (Performance* performance : results) {
        sumError += performance->getErrorRate();
    }
    return new Performance(sumError / results.size());
}

/**
 * The meanClassificationPerformance method loops through the performances of results ArrayList and sums up the accuracy of each
 * classification performance, then returns a new classificationPerformance with the mean of that summation.
 *
 * @return A new classificationPerformance with the mean of that summation.
 */
ClassificationPerformance *ExperimentPerformance::meanClassificationPerformance() const{
    if (results.empty() || !classification) {
        return nullptr;
    }
    double sumAccuracy = 0;
    for (Performance* performance : results) {
        auto* classificationPerformance = (ClassificationPerformance*)(performance);
        sumAccuracy += classificationPerformance->getAccuracy();
    }
    return new ClassificationPerformance(sumAccuracy / results.size());
}

/**
 * The meanDetailedPerformance method gets the first confusion matrix of results ArrayList.
 * Then, it adds new confusion matrices as the DetailedClassificationPerformance of
 * other elements of results ArrayList' confusion matrices as a DetailedClassificationPerformance.
 *
 * @return A new DetailedClassificationPerformance with the ConfusionMatrix sum.
 */
DetailedClassificationPerformance *ExperimentPerformance::meanDetailedPerformance() const{
    if (results.empty() || !containsDetails) {
        return nullptr;
    }
    ConfusionMatrix sum = ((DetailedClassificationPerformance*)(results.at(0)))->getConfusionMatrix();
    for (int i = 1; i < results.size(); i++) {
        sum.addConfusionMatrix(((DetailedClassificationPerformance*)(results.at(i)))->getConfusionMatrix());
    }
    return new DetailedClassificationPerformance(sum);
}

/**
 * The standardDeviationPerformance method loops through the Performances of results ArrayList and returns
 * a new Performance with the standard deviation.
 *
 * @return A new Performance with the standard deviation.
 */
Performance* ExperimentPerformance::standardDeviationPerformance() const{
    double sumErrorRate = 0;
    Performance* averagePerformance;
    averagePerformance = meanPerformance();
    for (Performance* performance : results) {
        sumErrorRate += pow(performance->getErrorRate() - averagePerformance->getErrorRate(), 2);
    }
    return new Performance(sqrt(sumErrorRate / (results.size() - 1)));
}

/**
 * The standardDeviationClassificationPerformance method loops through the Performances of results ArrayList and
 * returns a new ClassificationPerformance with standard deviation.
 *
 * @return A new ClassificationPerformance with standard deviation.
 */
ClassificationPerformance *ExperimentPerformance::standardDeviationClassificationPerformance() const{
    if (results.empty() || !classification) {
        return nullptr;
    }
    double sumAccuracy = 0, sumErrorRate = 0;
    ClassificationPerformance* averageClassificationPerformance;
    averageClassificationPerformance = meanClassificationPerformance();
    for (Performance* performance : results) {
        auto* classificationPerformance = (ClassificationPerformance*)(performance);
        sumAccuracy += pow(classificationPerformance->getAccuracy() - averageClassificationPerformance->getAccuracy(), 2);
        sumErrorRate += pow(classificationPerformance->getErrorRate() - averageClassificationPerformance->getErrorRate(), 2);
    }
    return new ClassificationPerformance(sqrt(sumAccuracy / (results.size() - 1)), sqrt(sumErrorRate / (results.size() - 1)));
}

/**
 * The isBetter method  takes an ExperimentPerformance as an input and returns true if the result of compareTo method is positive
 * and false otherwise.
 *
 * @param experimentPerformance ExperimentPerformance input.
 * @return True if the result of compareTo method is positive and false otherwise.
 */
bool ExperimentPerformance::isBetter(ExperimentPerformance* experimentPerformance) const{
    double accuracy1, accuracy2;
    accuracy1 = meanClassificationPerformance()->getAccuracy();
    accuracy2 = experimentPerformance->meanClassificationPerformance()->getAccuracy();
    return accuracy1 > accuracy2;
}
