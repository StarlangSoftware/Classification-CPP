//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_AUTOENCODER_H
#define CLASSIFICATION_AUTOENCODER_H
#include "Classifier.h"

class AutoEncoder : public Classifier{
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
    Performance* test(InstanceList testSet);
};


#endif //CLASSIFICATION_AUTOENCODER_H
