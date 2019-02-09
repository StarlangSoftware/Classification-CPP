//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_DUMMY_H
#define CLASSIFICATION_DUMMY_H
#include "Classifier.h"

class Dummy : public Classifier {
public:
    void train(InstanceList& trainSet, Parameter* parameters);
};


#endif //CLASSIFICATION_DUMMY_H
