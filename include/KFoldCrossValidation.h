//
// Created by Olcay Taner Yıldız on 28.09.2018.
//

#ifndef SAMPLING_KFOLDCROSSVALIDATION_H
#define SAMPLING_KFOLDCROSSVALIDATION_H
#include "CrossValidation.h"
#include <random>
using namespace std;

template <class T> class KFoldCrossValidation : public CrossValidation<T>{
private:
    int N;
    vector<T> instanceList;
public:
    KFoldCrossValidation(const vector<T>& instanceList, int K, unsigned int seed);
    vector<T> getTrainFold(int k);
    vector<T> getTestFold(int k);
};

/**
 * A constructor of {@link KFoldCrossValidation} class which takes a sample as an array of instances, a K (K in K-fold cross-validation) and a seed number,
 * then shuffles the original sample using this seed as random number.
 *
 * @param instanceList Original sample
 * @param K K in K-fold cross-validation
 * @param seed Random number to create K-fold sample(s)
 */
template<class T> KFoldCrossValidation<T>::KFoldCrossValidation(const vector<T> &instanceList, int K, unsigned int seed) {
    this->instanceList = instanceList;
    shuffle(this->instanceList.begin(), this->instanceList.end(), default_random_engine(seed));
    N = instanceList.size();
    this->K = K;
}

/**
 * getTrainFold returns the k'th train fold in K-fold cross-validation.
 *
 * @param k index for the k'th train fold of the K-fold cross-validation
 * @return Produced training sample
 */
template<class T> vector<T> KFoldCrossValidation<T>::getTrainFold(int k){
    vector<T> trainFold;
    for (int i = 0; i < (k * N) / this->K; i++){
        trainFold.push_back(instanceList.at(i));
    }
    for (int i = ((k + 1) * N) / this->K; i < N; i++){
        trainFold.push_back(instanceList.at(i));
    }
    return trainFold;
}

/**
 * getTestFold returns the k'th test fold in K-fold cross-validation.
 *
 * @param k index for the k'th test fold of the K-fold cross-validation
 * @return Produced testing sample
 */
template<class T> vector<T> KFoldCrossValidation<T>::getTestFold(int k){
    vector<T> testFold;
    for (int i = (k * N) / this->K; i < ((k + 1) * N) / this->K; i++){
        testFold.push_back(instanceList.at(i));
    }
    return testFold;
}

#endif //SAMPLING_KFOLDCROSSVALIDATION_H
