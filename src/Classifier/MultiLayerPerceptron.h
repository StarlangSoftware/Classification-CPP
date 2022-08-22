//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_MULTILAYERPRECEPTRON_H
#define CLASSIFICATION_MULTILAYERPRECEPTRON_H
#include "Classifier.h"

class MultiLayerPerceptron : public Classifier {
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
};


#endif //CLASSIFICATION_MULTILAYERPRECEPTRON_H
