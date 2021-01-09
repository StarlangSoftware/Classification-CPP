//
// Created by Olcay Taner Yıldız on 29.09.2018.
//

#ifndef SAMPLING_STRATIFIEDKFOLDCROSSVALIDATION_H
#define SAMPLING_STRATIFIEDKFOLDCROSSVALIDATION_H

#include <vector>
#include <random>
#include "CrossValidation.h"

template <class T> class StratifiedKFoldCrossValidation : public CrossValidation<T> {
private:
    unsigned long* N;
    vector<T>* instanceLists;
    int numberOfClasses;
public:
    StratifiedKFoldCrossValidation(vector<T>* instanceLists, int numberOfClasses, int K, unsigned int seed);
    virtual ~StratifiedKFoldCrossValidation();
    vector<T> getTrainFold(int k);
    vector<T> getTestFold(int k);
};

/**
 * A constructor of {@link StratifiedKFoldCrossValidation} class which takes as set of class samples as an array of array of instances, a K (K in K-fold cross-validation) and a seed number,
 * then shuffles each class sample using the seed number.
 *
 * @param instanceLists Original class samples. Each element of the this array is a sample only from one class.
 * @param K K in K-fold cross-validation
 * @param seed Random number to create K-fold sample(s)
 */
template<class T> StratifiedKFoldCrossValidation<T>::StratifiedKFoldCrossValidation(vector<T>* instanceLists, int numberOfClasses, int K, unsigned int seed){
    this->instanceLists = instanceLists;
    N = new unsigned long[numberOfClasses];
    for (int i = 0; i < numberOfClasses; i++){
        shuffle(this->instanceLists[i].begin(), this->instanceLists[i].end(), default_random_engine(seed));
        N[i] = instanceLists[i].size();
    }
    this->K = K;
    this->numberOfClasses = numberOfClasses;
}

/**
 * getTrainFold returns the k'th train fold in K-fold stratified cross-validation.
 *
 * @param k index for the k'th train fold of the K-fold stratified cross-validation
 * @return Produced training sample
 */
template<class T> vector<T> StratifiedKFoldCrossValidation<T>::getTrainFold(int k){
    vector<T> trainFold;
    for (int i = 0; i < numberOfClasses; i++){
        for (int j = 0; j < (k * N[i]) / this->K; j++){
            trainFold.push_back(instanceLists[i].at(j));
        }
        for (unsigned long j = ((k + 1) * N[i]) / this->K; j < N[i]; j++){
            trainFold.push_back(instanceLists[i].at(j));
        }
    }
    return trainFold;
}

/**
 * getTestFold returns the k'th test fold in K-fold stratified cross-validation.
 *
 * @param k index for the k'th test fold of the K-fold stratified cross-validation
 * @return Produced testing sample
 */
template<class T> vector<T> StratifiedKFoldCrossValidation<T>::getTestFold(int k){
    vector<T> testFold;
    for (int i = 0; i < numberOfClasses; i++){
        for (unsigned long j = (k * N[i]) / this->K; j < ((k + 1) * N[i]) / this->K; j++){
            testFold.push_back(instanceLists[i].at(j));
        }
    }
    return testFold;
}

template<class T>
StratifiedKFoldCrossValidation<T>::~StratifiedKFoldCrossValidation() {
    delete N;
}

#endif //SAMPLING_STRATIFIEDKFOLDCROSSVALIDATION_H
