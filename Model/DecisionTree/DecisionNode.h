//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_DECISIONNODE_H
#define CLASSIFICATION_DECISIONNODE_H


#include "DecisionCondition.h"
#include "../../InstanceList/InstanceList.h"
#include "../../Parameter/RandomForestParameter.h"

class DecisionNode {
private:
    vector<DecisionNode> children;
    InstanceList data;
    string classLabel;
    bool leaf = false;
    DecisionCondition condition = DecisionCondition(-1, nullptr);
    double entropyForDiscreteAttribute(int attributeIndex);
    void createChildrenForDiscreteIndexed(int attributeIndex, int attributeValue, RandomForestParameter* parameter, bool isStump);
    void createChildrenForDiscrete(int attributeIndex, RandomForestParameter* parameter, bool isStump);
    void createChildrenForContinuous(int attributeIndex, double splitValue, RandomForestParameter* parameter, bool isStump);
public:
    DecisionNode();
    explicit DecisionNode(ifstream& inputFile);
    DecisionNode(InstanceList data, DecisionCondition condition, RandomForestParameter* parameter, bool isStump);
    string predict(Instance* instance);
    bool isLeaf();
    void setLeaf(bool leaf);
    vector<DecisionNode> getChildren();
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_DECISIONNODE_H
