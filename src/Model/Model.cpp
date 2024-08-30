//
// Created by Olcay Taner YILDIZ on 30.08.2024.
//

#include "Model.h"
#include <CounterHashMap.h>
#include "../Performance/ConfusionMatrix.h"
#include "../Performance/DetailedClassificationPerformance.h"

/**
 * Given an array of class labels, returns the maximum occurred one.
 *
 * @param classLabels An array of class labels.
 * @return The class label that occurs most in the array of class labels (mod of class label list).
 */
string Model::getMaximum(const vector<string>& classLabels) {
    CounterHashMap<string> frequencies;
    for (const string &label : classLabels) {
        frequencies.put(label);
    }
    return frequencies.max();
}

/**
 * Checks given instance's attribute and returns true if it is a discrete indexed attribute, false otherwise.
 *
 * @param instance Instance to check.
 * @return True if instance is a discrete indexed attribute, false otherwise.
 */
bool Model::discreteCheck(Instance *instance) const{
    for (int i = 0; i < instance->attributeSize(); i++) {
        if (instance->getAttribute(i)->isDiscrete() && !(instance->getAttribute(i)->isDiscreteIndexed())) {
            return false;
        }
    }
    return true;
}

/**
 * TestClassification an instance list with the current model.
 *
 * @param testSet Test data (list of instances) to be tested.
 * @return The accuracy (and error) of the model as an instance of Performance class.
 */
Performance* Model::test(const InstanceList& testSet){
    vector<string> classLabels = testSet.getUnionOfPossibleClassLabels();
    ConfusionMatrix confusion = ConfusionMatrix(classLabels);
    for (int i = 0; i < testSet.size(); i++) {
        Instance* instance = testSet.get(i);
        confusion.classify(instance->getClassLabel(), predict(instance));
    }
    return new DetailedClassificationPerformance(confusion);
}

/**
 * Runs current classifier with the given train and test data.
 *
 * @param parameter Parameter of the classifier to be trained.
 * @param trainSet  Training data to be used in training the classifier.
 * @param testSet   Test data to be tested after training the model.
 * @return The accuracy (and error) of the trained model as an instance of Performance class.
 * @throws DiscreteFeaturesNotAllowed Exception for discrete features.
 */
Performance *Model::singleRun(Parameter *parameter, InstanceList& trainSet, const InstanceList& testSet){
    train(trainSet, parameter);
    return test(testSet);
}
