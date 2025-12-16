//
// Created by Oğuz Kerem Yıldız on 29.11.2025.
//

#include "SoftDecisionTree.h"

#include <unordered_map>

#include "SoftDecisionNode.h"
#include "../../InstanceList/Partition.h"

void SoftDecisionTree::train(InstanceList &trainSet, Parameter *parameters) {
    srand(parameters->getSeed());
    classLabelIndexMap = unordered_map<string, int>();
    root = new SoftDecisionNode(nullptr, trainSet);
    const std::vector<string> classLabels = trainSet.getDistinctClassLabels();
    for (int i = 0; i < classLabels.size(); i++) {
        classLabelIndexMap[classLabels[i]] = i;
    }
    auto partition = Partition(trainSet, ((LinearPerceptronParameter*) parameters)->getCrossValidationRatio(), parameters->getSeed(), true);
    ((SoftDecisionNode*) root)->createSoftDecisionTree(*partition.get(0), *partition.get(1), (SoftDecisionTreeParameter*) parameters, classLabelIndexMap);
}

string SoftDecisionTree::predict(Instance* instance) {
    const std::vector<double> output = ((SoftDecisionNode*) root)->calculateOutput((SoftDecisionNode*)root, *instance);
    int label = 0;
    double max = output[0];
    for (int i = 1; i < output.size(); i++) {
        if (max < output[i]) {
            max = output[i];
            label = i;
        }
    }
    for (const auto& o : classLabelIndexMap) {
        if (o.second == label) {
            return o.first;
        }
    }
    return "";
}