//
// Created by Oğuz Kerem Yıldız on 29.11.2025.
//

#include "SoftDecisionNode.h"
#include <cmath>
#include <iostream>
#include <unordered_map>

#include "../../Attribute/ContinuousAttribute.h"
#include "../../Parameter/SoftDecisionTreeParameter.h"

inline bool kroneckerDelta(const int& r, const int& k) {
    return r == k;
}

inline double getRandomValue() {
    return (rand() + 0.0) / RAND_MAX;
}

void SoftDecisionNode::copyTo(SoftDecisionNode* node) {
    node->w = vector(this->w);
    ((SoftDecisionNode*)node->children.at(0))->w0s = vector(((SoftDecisionNode*)this->children.at(0))->w0s);
    ((SoftDecisionNode*)node->children.at(1))->w0s = vector(((SoftDecisionNode*)this->children.at(1))->w0s);
}

SoftDecisionNode::SoftDecisionNode(SoftDecisionNode* parent, const InstanceList& trainData) {
    this->parent = parent;
    w0s = std::vector<double>(trainData.getDistinctClassLabels().size());
    for (double & w0 : w0s) {
        w0 = (getRandomValue() * 0.02) - 0.01;
    }
    outputs = std::vector<double>(w0s.size());
    for (int i = 0; i < w0s.size(); i++) {
        outputs[i] = (getRandomValue() * 0.02) - 0.01;
    }
    w = std::vector<double>(trainData.get(0)->attributeSize() + 1);
    for (double & i : w) {
        i = (getRandomValue() * 0.02) - 0.01;
    }
    weight = 0.0;
}

void SoftDecisionNode::createSoftDecisionTree(const InstanceList& cvData, InstanceList& trainData, SoftDecisionTreeParameter* parameter, const unordered_map<string, int>& classLabelIndexMap) {
    if (findBestSoftDecisionTreeSplit(cvData, trainData, parameter, classLabelIndexMap)) {
        ((SoftDecisionNode*) this->children.at(0))->createSoftDecisionTree(cvData, trainData, parameter, classLabelIndexMap);
        ((SoftDecisionNode*) this->children.at(1))->createSoftDecisionTree(cvData, trainData, parameter, classLabelIndexMap);
    }
}

std::vector<double> SoftDecisionNode::calculateOutput(SoftDecisionNode* node, const Instance& data) {
    if (node->children.empty()) {
        return node->w0s;
    }
    double v = data.toVector().biased().dotProduct(Vector(node->w));
    v = 1 / (1 + exp(-v));
    ((SoftDecisionNode*)node->children.at(0))->weight = v;
    ((SoftDecisionNode*)node->children.at(1))->weight = 1 - ((SoftDecisionNode*)node->children.at(0))->weight;
    std::vector<double> left_output = calculateOutput((SoftDecisionNode *) node->children.at(0), data);
    std::vector<double> right_output = calculateOutput((SoftDecisionNode *) node->children.at(1), data);
    for (int i = 0; i < node->outputs.size(); i++) {
        node->outputs[i] = ((SoftDecisionNode*)node->children.at(0))->weight * left_output[i] + ((SoftDecisionNode*)node->children.at(1))->weight * right_output[i];
    }
    return node->outputs;
}

int SoftDecisionNode::errorOfSoftDecisionTree(SoftDecisionNode *node, const InstanceList &data, const unordered_map<string, int>& classLabelIndexMap) {
    int count = 0;
    for (int i = 0; i < data.size(); i++) {
        const auto* instance = data.get(i);
        const int classLabel = classLabelIndexMap.at(instance->getClassLabel());
        std::vector<double> o = calculateOutput(node, *instance);
        double max = o[0];
        int index = 0;
        for (int j = 1; j < o.size(); j++) {
            if (max < o[j]) {
                max = o[j];
                index = j;
            }
        }
        if (index != classLabel) {
            count++;
        }
    }
    return count;
}

SoftDecisionNode *SoftDecisionNode::createNode(const InstanceList& data) {
    auto* node = new SoftDecisionNode();
    node->children.push_back(new SoftDecisionNode(node, data));
    node->children.push_back(new SoftDecisionNode(node, data));
    return node;
}


bool SoftDecisionNode::findBestSoftDecisionTreeSplit(const InstanceList& cvData, InstanceList& data, SoftDecisionTreeParameter* parameter, const unordered_map<string, int>& classLabelIndexMap) {
    auto tmp = vector(w0s);
    auto root = this;
    while (root->parent != nullptr) {
        root = root->parent;
    }
    auto performanceBefore = errorOfSoftDecisionTree(root, cvData, classLabelIndexMap);
    this->children = std::vector<DecisionNode*>();
    this->children.push_back(new SoftDecisionNode(this, data));
    this->children.push_back(new SoftDecisionNode(this, data));
    auto* bestNode = createNode(data);
    auto* tmpNode = createNode(data);
    this->copyTo(tmpNode);
    int performanceBest = INT_MAX;
    bool result = true;
    int denominator = 1;
    for (int i = 0; i <= 10; i++) {
        const double eta = 10.0 / denominator;
        gradientDescentSoftDecisionTree(root, &data, parameter, eta, classLabelIndexMap);
        int performanceNow = errorOfSoftDecisionTree(root, cvData, classLabelIndexMap);
        if (performanceNow < performanceBest) {
            performanceBest = performanceNow;
            this->copyTo(bestNode);
        }
        tmpNode->copyTo(this);
        denominator *= 2;
    }
    if (performanceBefore <= performanceBest) {
        result = false;
        this->children.clear();
        this->w0s = vector(tmp);
    } else {
        bestNode->copyTo(this);
    }
    return result;
}

void SoftDecisionNode::gradientDescentSoftDecisionTree(SoftDecisionNode *root, InstanceList* data, SoftDecisionTreeParameter *parameter, double eta, const unordered_map<string, int>& classLabelIndexMap) {
    auto previousUpdateLeftw0s = std::vector<double>(classLabelIndexMap.size());
    auto previousUpdateRightw0s = std::vector<double>(classLabelIndexMap.size());
    auto previousUpdatew = std::vector<double>(data->get(0)->attributeSize() + 1);
    double featureValue;
    for (int i = 0; i < parameter->getEpoch(); i++) {
        data->shuffle(parameter->getSeed());
        for (int j = 0; j < data->size(); j++) {
            const auto inst = data->get(j);
            std::vector<double> output = calculateOutput(root, *inst);
            double sum = 0.0;
            for (const double t : output) {
                sum += exp(t);
            }
            for (double & t : output) {
                t = exp(t) / sum;
            }
            int r = classLabelIndexMap.at(inst->getClassLabel());
            double multiplier = eta;
            const SoftDecisionNode* tmpNode = this;
            while (tmpNode->parent) {
                multiplier *= tmpNode->weight;
                tmpNode = tmpNode->parent;
            }
            for (int k = 0; k < classLabelIndexMap.size(); k++) {
                ((SoftDecisionNode*)this->children.at(0))->w0s[k] += multiplier * (kroneckerDelta(r, k) - output[k]) * ((SoftDecisionNode*)this->children.at(0))->weight + parameter->getAlpha() * previousUpdateLeftw0s[k];
                previousUpdateLeftw0s[k] = multiplier * (kroneckerDelta(r, k) - output[k]) * ((SoftDecisionNode*)this->children.at(0))->weight;
                ((SoftDecisionNode*)this->children.at(1))->w0s[k] += multiplier * (kroneckerDelta(r, k) - output[k]) * ((SoftDecisionNode*)this->children.at(1))->weight + parameter->getAlpha() * previousUpdateRightw0s[k];
                previousUpdateRightw0s[k] = multiplier * (kroneckerDelta(r, k) - output[k]) * ((SoftDecisionNode*)this->children.at(1))->weight;
            }
            for (int t = 0; t < inst->attributeSize() + 1; t++) {
                if (t != 0) {
                    featureValue = ((ContinuousAttribute*)inst->getAttribute(t - 1))->getValue();
                } else {
                    featureValue = 1;
                }
                sum = 0.0;
                for (int k = 0; k < classLabelIndexMap.size(); k++) {
                    const double delta = multiplier * (kroneckerDelta(r, k) - output[k]) * featureValue * (((SoftDecisionNode*)this->children.at(0))->outputs[k] - ((SoftDecisionNode*)this->children.at(1))->outputs[k]) * ((SoftDecisionNode*)this->children.at(0))->weight * ((SoftDecisionNode*)this->children.at(1))->weight;
                    sum += delta;
                }
                this->w[t] += sum + parameter->getAlpha() * previousUpdatew[t];
                previousUpdatew[t] = sum;
            }
        }
        eta = eta * parameter->getEtaDecrease();
    }
}

SoftDecisionNode::~SoftDecisionNode() {
    for (const DecisionNode* node : children) {
        delete node;
    }
}
