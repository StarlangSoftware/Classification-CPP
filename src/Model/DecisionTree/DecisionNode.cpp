//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include <cfloat>
#include <fstream>
#include <random>
#include "DecisionNode.h"
#include "../../InstanceList/Partition.h"
#include "../../Attribute/DiscreteIndexedAttribute.h"
#include "../../Attribute/ContinuousAttribute.h"
#include "../../Classifier/Classifier.h"
#include "../../Instance/CompositeInstance.h"
#include "RandomArray.h"

/**
 * The entropyForDiscreteAttribute method takes an attributeIndex and creates an ArrayList of DiscreteDistribution.
 * Then loops through the distributions and calculates the total entropy.
 *
 * @param data InstanceList.
 * @param attributeIndex Index of the attribute.
 * @return Total entropy for the discrete attribute.
 */
double DecisionNode::entropyForDiscreteAttribute(const InstanceList& data, int attributeIndex) const{
    double sum = 0.0;
    vector<DiscreteDistribution> distributions = data.attributeClassDistribution(attributeIndex);
    for (const DiscreteDistribution& distribution : distributions) {
        sum += (distribution.getSum() / data.size()) * distribution.entropy();
    }
    return sum;
}

/**
 * The createChildrenForDiscreteIndexed method creates an ArrayList of DecisionNodes as children and a partition with respect to
 * indexed attribute.
 *
 * @param data InstanceList.
 * @param attributeIndex Index of the attribute.
 * @param attributeValue Value of the attribute.
 * @param parameter      RandomForestParameter like seed, ensembleSize, attributeSubsetSize.
 * @param isStump        Refers to decision trees with only 1 splitting rule.
 */
void
DecisionNode::createChildrenForDiscreteIndexed(const InstanceList& data, int attributeIndex, int attributeValue, RandomForestParameter *parameter,
                                               bool isStump) {
    Partition childrenData;
    childrenData = Partition(data, attributeIndex, attributeValue);
    children.emplace_back(DecisionNode(*(childrenData.get(0)), DecisionCondition(attributeIndex, new DiscreteIndexedAttribute("", attributeValue, ((DiscreteIndexedAttribute*) data.get(0)->getAttribute(attributeIndex))->getMaxIndex())), parameter, isStump));
    children.emplace_back(DecisionNode(*(childrenData.get(1)), DecisionCondition(attributeIndex, new DiscreteIndexedAttribute("", -1, ((DiscreteIndexedAttribute*) data.get(0)->getAttribute(attributeIndex))->getMaxIndex())), parameter, isStump));
}

/**
 * The createChildrenForDiscrete method creates an ArrayList of values, a partition with respect to attributes and an ArrayList
 * of DecisionNodes as children.
 *
 * @param data InstanceList.
 * @param attributeIndex Index of the attribute.
 * @param parameter      RandomForestParameter like seed, ensembleSize, attributeSubsetSize.
 * @param isStump        Refers to decision trees with only 1 splitting rule.
 */
void DecisionNode::createChildrenForDiscrete(const InstanceList& data, int attributeIndex, RandomForestParameter *parameter, bool isStump) {
    Partition childrenData;
    vector<string> valueList;
    valueList = data.getAttributeValueList(attributeIndex);
    childrenData = Partition(data, attributeIndex);
    for (int i = 0; i < valueList.size(); i++) {
        children.emplace_back(DecisionNode(*(childrenData.get(i)), DecisionCondition(attributeIndex, new DiscreteAttribute(valueList.at(i))), parameter, isStump));
    }
}

/**
 * The createChildrenForContinuous method creates an ArrayList of DecisionNodes as children and a partition with respect to
 * continious attribute and the given split value.
 *
 * @param data InstanceList.
 * @param attributeIndex Index of the attribute.
 * @param parameter      RandomForestParameter like seed, ensembleSize, attributeSubsetSize.
 * @param isStump        Refers to decision trees with only 1 splitting rule.
 * @param splitValue     Split value is used for partitioning.
 */
void DecisionNode::createChildrenForContinuous(const InstanceList& data, int attributeIndex, double splitValue, RandomForestParameter *parameter,
                                               bool isStump) {
    Partition childrenData;
    childrenData = Partition(data, attributeIndex, splitValue);
    children.emplace_back(DecisionNode(*(childrenData.get(0)), DecisionCondition(attributeIndex, '<', new ContinuousAttribute(splitValue)), parameter, isStump));
    children.emplace_back(DecisionNode(*(childrenData.get(1)), DecisionCondition(attributeIndex, '>', new ContinuousAttribute(splitValue)), parameter, isStump));
}

/**
 * The DecisionNode method takes InstanceList data as input and then it sets the class label parameter by finding
 * the most occurred class label of given data, it then gets distinct class labels as class labels ArrayList. Later, it adds ordered
 * indices to the indexList and shuffles them randomly. Then, it gets the class distribution of given data and finds the best entropy value
 * of these class distribution.
 * <p>
 * If an attribute of given data is DiscreteIndexedAttribute, it creates a Distribution according to discrete indexed attribute class distribution
 * and finds the entropy. If it is better than the last best entropy it reassigns the best entropy, best attribute and best split value according to
 * the newly founded best entropy's index. At the end, it also add new distribution to the class distribution .
 * <p>
 * If an attribute of given data is DiscreteAttribute, it directly finds the entropy. If it is better than the last best entropy it
 * reassigns the best entropy, best attribute and best split value according to the newly founded best entropy's index.
 * <p>
 * If an attribute of given data is ContinuousAttribute, it creates two distributions; left and right according to class distribution
 * and discrete distribution respectively, and finds the entropy. If it is better than the last best entropy it reassigns the best entropy,
 * best attribute and best split value according to the newly founded best entropy's index. At the end, it also add new distribution to
 * the right distribution and removes from left distribution .
 *
 * @param data      InstanceList input.
 * @param condition DecisionCondition to check.
 * @param parameter RandomForestParameter like seed, ensembleSize, attributeSubsetSize.
 * @param isStump   Refers to decision trees with only 1 splitting rule.
 */
DecisionNode::DecisionNode(InstanceList data, const DecisionCondition& condition, RandomForestParameter *parameter,
                           bool isStump) {
    double bestEntropy, entropy;
    DiscreteDistribution leftDistribution, rightDistribution, classDistribution;
    int bestAttribute = -1, size;
    double bestSplitValue = 0, previousValue, splitValue;
    Instance* instance;
    vector<string> classLabels;
    this->condition = condition;
    classLabelsDistribution = DiscreteDistribution();
    vector<string> labels = data.getClassLabels();
    for (const string& label : labels){
        classLabelsDistribution.addItem(label);
    }
    classLabel = Classifier::getMaximum(labels);
    leaf = true;
    classLabels = data.getDistinctClassLabels();
    if (classLabels.size() == 1) {
        return;
    }
    if (isStump && condition.getAttributeIndex() != -1) {
        return;
    }
    vector<int> indexList;
    if (parameter != nullptr && parameter->getAttributeSubsetSize() < data.get(0)->attributeSize()) {
        indexList = RandomArray::indexArray(data.get(0)->attributeSize(), parameter->getSeed());
        size = parameter->getAttributeSubsetSize();
    } else {
        indexList.reserve(data.get(0)->attributeSize());
        for (int i = 0; i < data.get(0)->attributeSize(); i++) {
            indexList.push_back(i);
        }
        size = data.get(0)->attributeSize();
    }
    classDistribution = data.classDistribution();
    bestEntropy = classDistribution.entropy();
    for (int j = 0; j < size; j++) {
        int index = indexList.at(j);
        if (data.get(0)->getAttribute(index)->isDiscreteIndexed()) {
            for (int k = 0; k < ((DiscreteIndexedAttribute*) data.get(0)->getAttribute(index))->getMaxIndex(); k++) {
                DiscreteDistribution distribution = data.discreteIndexedAttributeClassDistribution(index, k);
                if (distribution.getSum() > 0) {
                    classDistribution.removeDistribution(distribution);
                    entropy = (classDistribution.entropy() * classDistribution.getSum() + distribution.entropy() * distribution.getSum()) / data.size();
                    if (entropy < bestEntropy) {
                        bestEntropy = entropy;
                        bestAttribute = index;
                        bestSplitValue = k;
                    }
                    classDistribution.addDistribution(distribution);
                }
            }
        } else {
            if (data.get(0)->getAttribute(index)->isDiscrete()) {
                entropy = entropyForDiscreteAttribute(data, index);
                if (entropy < bestEntropy) {
                    bestEntropy = entropy;
                    bestAttribute = index;
                }
            } else {
                if (data.get(0)->getAttribute(index)->isContinuous()) {
                    data.sort(index);
                    previousValue = -DBL_MAX;
                    leftDistribution = data.classDistribution();
                    rightDistribution = DiscreteDistribution();
                    for (int k = 0; k < data.size(); k++) {
                        instance = data.get(k);
                        if (k == 0) {
                            previousValue = ((ContinuousAttribute*) instance->getAttribute(index))->getValue();
                        } else {
                            if (((ContinuousAttribute*) instance->getAttribute(index))->getValue() != previousValue) {
                                splitValue = (previousValue + ((ContinuousAttribute*) instance->getAttribute(index))->getValue()) / 2;
                                previousValue = ((ContinuousAttribute*) instance->getAttribute(index))->getValue();
                                entropy = (leftDistribution.getSum() / data.size()) * leftDistribution.entropy() + (rightDistribution.getSum() / data.size()) * rightDistribution.entropy();
                                if (entropy < bestEntropy) {
                                    bestEntropy = entropy;
                                    bestSplitValue = splitValue;
                                    bestAttribute = index;
                                }
                            }
                        }
                        leftDistribution.removeItem(instance->getClassLabel());
                        rightDistribution.addItem(instance->getClassLabel());
                    }
                }
            }
        }
    }
    if (bestAttribute != -1) {
        leaf = false;
        if (data.get(0)->getAttribute(bestAttribute)->isDiscreteIndexed()) {
            createChildrenForDiscreteIndexed(data, bestAttribute, (int) bestSplitValue, parameter, isStump);
        } else {
            if (data.get(0)->getAttribute(bestAttribute)->isDiscrete()) {
                createChildrenForDiscrete(data, bestAttribute, parameter, isStump);
            } else {
                if (data.get(0)->getAttribute(bestAttribute)->isContinuous()) {
                    createChildrenForContinuous(data, bestAttribute, bestSplitValue, parameter, isStump);
                }
            }
        }
    }
}

/**
 * The predict method takes an Instance as input and performs prediction on the DecisionNodes and returns the prediction
 * for that instance.
 *
 * @param instance Instance to make prediction.
 * @return The prediction for given instance.
 */
string DecisionNode::predict(Instance *instance) const{
    if (instance->isComposite()) {
        vector<string> possibleClassLabels = ((CompositeInstance*) instance)->getPossibleClassLabels();
        DiscreteDistribution distribution = classLabelsDistribution;
        string predictedClass = distribution.getMaxItem(possibleClassLabels);
        if (leaf) {
            return predictedClass;
        } else {
            for (const DecisionNode& node : children) {
                if (node.condition.satisfy(instance)) {
                    string childPrediction = node.predict(instance);
                    if (!childPrediction.empty()) {
                        return childPrediction;
                    } else {
                        return predictedClass;
                    }
                }
            }
            return predictedClass;
        }
    } else {
        if (leaf) {
            return classLabel;
        } else {
            for (const DecisionNode& node : children) {
                if (node.condition.satisfy(instance)) {
                    return node.predict(instance);
                }
            }
            return classLabel;
        }
    }
}

DecisionNode::DecisionNode() = default;

bool DecisionNode::isLeaf() const{
    return leaf;
}

void DecisionNode::setLeaf(bool _leaf) {
    this->leaf = _leaf;
}

vector<DecisionNode> DecisionNode::getChildren() const{
    return children;
}

void DecisionNode::serialize(ostream &outputFile) {
    condition.serialize(outputFile);
    outputFile << children.size() << endl;
    if (!children.empty()){
        for (DecisionNode decisionNode : children){
            decisionNode.serialize(outputFile);
        }
    } else {
        outputFile << classLabel << endl;
    }
}

DecisionNode::DecisionNode(ifstream &inputFile) {
    int size;
    condition = DecisionCondition(inputFile);
    inputFile >> size;
    if (size != 0){
        leaf = false;
        for (int i = 0; i < size; i++){
            DecisionNode decisionNode = DecisionNode(inputFile);
            children.push_back(decisionNode);
        }
    } else {
        leaf = true;
        inputFile >> classLabel;
        classLabelsDistribution = DiscreteDistribution(inputFile);
    }
}

map<string, double> DecisionNode::predictProbabilityDistribution(Instance *instance) {
    if (leaf) {
        return classLabelsDistribution.getProbabilityDistribution();
    } else {
        for (DecisionNode node : children) {
            if (node.condition.satisfy(instance)) {
                return node.predictProbabilityDistribution(instance);
            }
        }
        return classLabelsDistribution.getProbabilityDistribution();
    }
}
