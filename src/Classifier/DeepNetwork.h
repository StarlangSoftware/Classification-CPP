//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_DEEPNETWORK_H
#define CLASSIFICATION_DEEPNETWORK_H
#include "Classifier.h"

class DeepNetwork : public Classifier{
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
};


#endif //CLASSIFICATION_DEEPNETWORK_H
