//
// Created by olcay on 12.02.2019.
//

#ifndef CLASSIFICATION_LINEARPERCEPTRON_H
#define CLASSIFICATION_LINEARPERCEPTRON_H
#include "Classifier.h"

class LinearPerceptron : public Classifier{
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
};


#endif //CLASSIFICATION_LINEARPERCEPTRON_H
