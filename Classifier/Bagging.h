//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_BAGGING_H
#define CLASSIFICATION_BAGGING_H
#include "Classifier.h"

class Bagging : public Classifier {
public:
    void train(InstanceList& trainSet, Parameter* parameters);
};


#endif //CLASSIFICATION_BAGGING_H
