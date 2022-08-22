//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_RANDOMFOREST_H
#define CLASSIFICATION_RANDOMFOREST_H
#include "Classifier.h"

class RandomForest : public Classifier{
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
};


#endif //CLASSIFICATION_RANDOMFOREST_H
