//
// Created by olcay on 12.02.2019.
//

#ifndef CLASSIFICATION_KNN_H
#define CLASSIFICATION_KNN_H
#include "Classifier.h"

class Knn : public Classifier{
public:
    void train(InstanceList& trainSet, Parameter* parameters);

};


#endif //CLASSIFICATION_KNN_H
