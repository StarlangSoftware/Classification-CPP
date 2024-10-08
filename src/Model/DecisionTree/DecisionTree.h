//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_DECISIONTREE_H
#define CLASSIFICATION_DECISIONTREE_H
#include "../ValidatedModel.h"
#include "DecisionNode.h"

class DecisionTree : public ValidatedModel{
protected:
    DecisionNode root;
    void pruneNode(DecisionNode decisionNode, const InstanceList& pruneSet);
public:
    DecisionTree() = default;
    string predict(Instance* instance) override;
    map<string, double> predictProbability(Instance* instance) override;
    explicit DecisionTree(ifstream& inputFile);
    explicit DecisionTree(const DecisionNode& root);
    void prune(const InstanceList& pruneSet);
    void serialize(ostream &outputFile) override;
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_DECISIONTREE_H
