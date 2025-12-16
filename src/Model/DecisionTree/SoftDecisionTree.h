//
// Created by Oğuz Kerem Yıldız on 29.11.2025.
//

#ifndef CLASSIFICATION_SOFTDECISIONTREE_H
#define CLASSIFICATION_SOFTDECISIONTREE_H
#include <unordered_map>

#include "DecisionTree.h"
#include "../../Parameter/LinearPerceptronParameter.h"


class SoftDecisionTree : public DecisionTree {
private:
    unordered_map<string, int> classLabelIndexMap;
public:
    SoftDecisionTree() = default;
    void train(InstanceList &trainSet, Parameter* parameters) override;
    string predict(Instance* instance) override;
};


#endif //CLASSIFICATION_SOFTDECISIONTREE_H