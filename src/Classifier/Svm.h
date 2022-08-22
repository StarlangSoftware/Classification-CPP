//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_SVM_H
#define CLASSIFICATION_SVM_H
#include "Classifier.h"

class Svm : public Classifier{
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
};


#endif //CLASSIFICATION_SVM_H
