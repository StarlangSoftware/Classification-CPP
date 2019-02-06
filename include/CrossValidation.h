//
// Created by Olcay Taner Yıldız on 27.09.2018.
//

#ifndef SAMPLING_CROSSVALIDATION_H
#define SAMPLING_CROSSVALIDATION_H
#include <vector>
using namespace std;

template <class T> class CrossValidation {
protected:
    int K;
public:
    virtual std::vector<T> getTrainFold(int k) = 0;
    virtual std::vector<T> getTestFold(int k) = 0;
};

#endif //SAMPLING_CROSSVALIDATION_H
