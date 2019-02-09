//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_RANDOMCLASSIFIER_H
#define CLASSIFICATION_RANDOMCLASSIFIER_H


#include "Classifier.h"

class RandomClassifier : public Classifier {
public:
    void train(InstanceList& trainSet, Parameter* parameters);

};


#endif //CLASSIFICATION_RANDOMCLASSIFIER_H
