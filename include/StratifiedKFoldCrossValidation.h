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
    int size;
public:
    StratifiedKFoldCrossValidation(const vector<T>* instanceLists, int size, int K, unsigned int seed);
    virtual ~StratifiedKFoldCrossValidation();
    vector<T> getTrainFold(int k);
    vector<T> getTestFold(int k);
};

template<class T> StratifiedKFoldCrossValidation<T>::StratifiedKFoldCrossValidation(const vector<T> instanceLists[], int size, int K, unsigned int seed){
    this->instanceLists = instanceLists;
    N = new unsigned long[size];
    for (int i = 0; i < size; i++){
        shuffle(this->instanceLists[i].begin(), this->instanceLists[i].end(), default_random_engine(seed));
        N[i] = instanceLists[i].capacity();
    }
    this->K = K;
    this->size = size;
}

template<class T> vector<T> StratifiedKFoldCrossValidation<T>::getTrainFold(int k){
    vector<T> trainFold;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < (k * N[i]) / this->K; j++){
            trainFold.push_back(instanceLists[i].at(j));
        }
        for (unsigned long j = ((k + 1) * N[i]) / this->K; j < N[i]; j++){
            trainFold.push_back(instanceLists[i].at(j));
        }
    }
    return trainFold;
}

template<class T> vector<T> StratifiedKFoldCrossValidation<T>::getTestFold(int k){
    vector<T> testFold;
    for (int i = 0; i < size; i++){
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
