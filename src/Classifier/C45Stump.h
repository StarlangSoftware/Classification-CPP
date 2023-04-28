//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_C45STUMP_H
#define CLASSIFICATION_C45STUMP_H
#include "Classifier.h"

class C45Stump : public Classifier {
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_C45STUMP_H
