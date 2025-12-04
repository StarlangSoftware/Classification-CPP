//
// Created by Oğuz Kerem Yıldız on 29.11.2025.
//

#ifndef CLASSIFICATION_SOFTDECISIONNODE_H
#define CLASSIFICATION_SOFTDECISIONNODE_H
#include <unordered_map>

#include "DecisionNode.h"
#include "../../Parameter/SoftDecisionTreeParameter.h"


class SoftDecisionNode : public DecisionNode {
private:
    /*! If the decision tree is a K-class soft decision tree, this is output array at the leaf node*/
    std::vector<double> w0s;
    std::vector<double> w;
    /*! If the decision tree is a K-class soft decision tree, this is temporary output array at the node*/
    std::vector<double> outputs;
    /*! If the decision tree is a soft decision tree, this is weight of the node*/
    double weight;
    SoftDecisionNode* parent;
    bool findBestSoftDecisionTreeSplit(const InstanceList& cvData, InstanceList & data, SoftDecisionTreeParameter* parameter, const unordered_map<string, int>& classLabelIndexMap);
    void gradientDescentSoftDecisionTree(SoftDecisionNode *root, InstanceList *data, SoftDecisionTreeParameter *parameter, double eta, const unordered_map<string, int>& classLabelIndexMap);
    void copyTo(SoftDecisionNode* node);
    int errorOfSoftDecisionTree(SoftDecisionNode *node, const InstanceList &data, const unordered_map<string, int>& classLabelIndexMap);
    double getRandomValue();
public:
    std::vector<double> calculateOutput(SoftDecisionNode* node, const Instance& data);
    explicit SoftDecisionNode(SoftDecisionNode* parent, const InstanceList& trainData);
    void createSoftDecisionTree(const InstanceList& cvData, InstanceList & trainData, SoftDecisionTreeParameter* parameter, const unordered_map<string, int>& classLabelIndexMap);
    SoftDecisionNode() = default;
    ~SoftDecisionNode();
};


#endif //CLASSIFICATION_SOFTDECISIONNODE_H