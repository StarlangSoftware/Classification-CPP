//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_CONFUSIONMATRIX_H
#define CLASSIFICATION_CONFUSIONMATRIX_H


#include <CounterHashMap.h>
#include <vector>

class ConfusionMatrix {
private:
    map<string, CounterHashMap<string>> matrix;
    vector<string> classLabels;
    double sumOfElements() const;
    double trace() const;
    double columnSum(const string& predictedClass) const;
public:
    ConfusionMatrix();
    explicit ConfusionMatrix(const vector<string>& classLabels);
    void classify(const string& actualClass, const string& predictedClass);
    void addConfusionMatrix(const ConfusionMatrix& confusionMatrix);
    double getAccuracy() const;
    double* precision() const;
    double* recall() const;
    double* fMeasure() const;
    double weightedFMeasure() const;
};


#endif //CLASSIFICATION_CONFUSIONMATRIX_H
