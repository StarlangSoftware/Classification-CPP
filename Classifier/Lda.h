//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_LDA_H
#define CLASSIFICATION_LDA_H
#include "Classifier.h"

class Lda : public Classifier {
public:
    void train(InstanceList& trainSet, Parameter* parameters);
};


#endif //CLASSIFICATION_LDA_H
