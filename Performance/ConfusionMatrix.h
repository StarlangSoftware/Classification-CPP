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
    double sumOfElements();
    double trace();
    double columnSum(string predictedClass);
public:
    ConfusionMatrix();
    ConfusionMatrix(vector<string> classLabels);
    void classify(string actualClass, string predictedClass);
    void addConfusionMatrix(ConfusionMatrix confusionMatrix);
    double getAccuracy();
    double* precision();
    double* recall();
    double* fMeasure();
    double weightedFMeasure();
};


#endif //CLASSIFICATION_CONFUSIONMATRIX_H
