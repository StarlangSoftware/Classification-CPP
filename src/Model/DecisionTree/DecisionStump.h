//
// Created by Olcay Taner YILDIZ on 30.08.2024.
//

#ifndef CLASSIFICATION_DECISIONSTUMP_H
#define CLASSIFICATION_DECISIONSTUMP_H


#include "DecisionTree.h"

class DecisionStump : public DecisionTree{
public:
    DecisionStump() = default;
    explicit DecisionStump(const DecisionNode& root);
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_DECISIONSTUMP_H
