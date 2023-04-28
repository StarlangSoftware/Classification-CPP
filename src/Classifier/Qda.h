//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_QDA_H
#define CLASSIFICATION_QDA_H

#include "Classifier.h"

class Qda : public Classifier {
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_QDA_H
