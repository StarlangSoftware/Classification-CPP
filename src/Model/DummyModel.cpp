//
// Created by Olcay Taner Yıldız on 8.02.2019.
//

#include "DummyModel.h"
#include "../Instance/CompositeInstance.h"

/**
 * Constructor which sets the distribution using the given InstanceList.
 *
 * @param trainSet InstanceList which is used to get the class distribution.
 */
DummyModel::DummyModel(InstanceList& trainSet) {
    distribution = trainSet.classDistribution();
}

/**
 * The predict method takes an Instance as an input and returns the entry of distribution which has the maximum value.
 *
 * @param instance Instance to make prediction.
 * @return The entry of distribution which has the maximum value.
 */
string DummyModel::predict(Instance *instance){
    if (instance->isComposite()) {
        vector<string> possibleClassLabels = instance->getPossibleClassLabels();
        return distribution.getMaxItem(possibleClassLabels);
    } else {
        return distribution.getMaxItem();
    }
}

void DummyModel::serialize(ostream &outputFile) {
    distribution.serialize(outputFile);
}

DummyModel::DummyModel(ifstream &inputFile) {
    distribution = DiscreteDistribution(inputFile);
}

map<string, double> DummyModel::predictProbability(Instance *instance){
    return distribution.getProbabilityDistribution();
}
