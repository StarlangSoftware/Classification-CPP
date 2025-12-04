//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_DECISIONNODE_H
#define CLASSIFICATION_DECISIONNODE_H


#include "DecisionCondition.h"
#include "../../InstanceList/InstanceList.h"
#include "../../Parameter/RandomForestParameter.h"

class DecisionNode {
protected:
    vector<DecisionNode*> children;
private:
    string classLabel;
    bool leaf = false;
    DiscreteDistribution classLabelsDistribution;
    DecisionCondition condition = DecisionCondition(-1, nullptr);
    double entropyForDiscreteAttribute(const InstanceList& data, int attributeIndex) const;
    void createChildrenForDiscreteIndexed(const InstanceList& data, int attributeIndex, int attributeValue, RandomForestParameter* parameter, bool isStump);
    void createChildrenForDiscrete(const InstanceList& data, int attributeIndex, RandomForestParameter* parameter, bool isStump);
    void createChildrenForContinuous(const InstanceList& data, int attributeIndex, double splitValue, RandomForestParameter* parameter, bool isStump);
public:
    DecisionNode();
    ~DecisionNode();
    explicit DecisionNode(ifstream& inputFile);
    DecisionNode(InstanceList data, const DecisionCondition& condition, RandomForestParameter* parameter, bool isStump);
    string predict(Instance* instance) const;
    map<string, double> predictProbabilityDistribution(Instance* instance);
    bool isLeaf() const;
    void setLeaf(bool leaf);
    vector<DecisionNode*> getChildren() const;
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_DECISIONNODE_H
