//
// Created by Olcay Taner Yıldız on 27.01.2019.
//
#include <random>
#include "Partition.h"
#include "CounterHashMap.h"
#include "DiscreteDistribution.h"
#include "InstanceListOfSameClass.h"
#include "../Attribute/DiscreteAttribute.h"
#include "../Attribute/DiscreteIndexedAttribute.h"
#include "../Attribute/ContinuousAttribute.h"
#include "RandomArray.h"

using namespace std;
/**
 * Constructor for generating a partition.
 */
Partition::Partition() = default;

/**
 * Adds given instance list to the list of instance lists.
 *
 * @param list Instance list to add.
 */
void Partition::add(InstanceList* list) {
    multiList.push_back(list);
}

/**
 * Returns the size of the list of instance lists.
 *
 * @return The size of the list of instance lists.
 */
int Partition::size() const{
    return multiList.size();
}

/**
 * Returns the corresponding instance list at given index of list of instance lists.
 *
 * @param index Index of the instance list.
 * @return Instance list at given index of list of instance lists.
 */
InstanceList* Partition::get(int index) const{
    return multiList.at(index);
}

/**
 * Returns the instances of the items at the list of instance lists.
 *
 * @return Instances of the items at the list of instance lists.
 */
vector<Instance *> *Partition::getLists() const{
    auto* result = new vector<Instance*>[multiList.size()];
    for (int i = 0; i < multiList.size(); i++) {
        result[i] = multiList.at(i)->getInstances();
    }
    return result;
}

/**
 * Divides the instances in the instance list into partitions so that all instances of a class are grouped in a
 * single partition.
 *
 * @return Groups of instances according to their class labels.
 */
Partition::Partition(const InstanceList &list){
    vector<string> classLabels = list.getDistinctClassLabels();
    for (const string &classLabel : classLabels)
        add(new InstanceListOfSameClass(classLabel));
    for (Instance* instance : list.getInstances()) {
        get(find(classLabels.begin(), classLabels.end(), instance->getClassLabel()) - classLabels.begin())->add(instance);
    }
}

/**
 * Creates a stratified/not-stratified partition of the current instance list. In a stratified partition, the percentage of each
 * class is preserved. For example, let's say there are three classes in the instance list, and let the percentages of
 * these classes be %20, %30, and %50; then the percentages of these classes in the stratified partitions are the
 * same, that is, %20, %30, and %50.
 *
 * @param ratio Ratio of the stratified partition. Ratio is between 0 and 1. If the ratio is 0.2, then 20 percent
 *              of the instances are put in the first group, 80 percent of the instances are put in the second group.
 * @param random random is used as a random number.
 * @return 2 group stratified partition of the instances in this instance list.
 */
Partition::Partition(InstanceList& list, double ratio, int seed, bool stratified) {
    add(new InstanceList());
    add(new InstanceList());
    if (stratified){
        CounterHashMap<string> counts;
        DiscreteDistribution distribution;
        distribution = list.classDistribution();
        vector<int> randomArray = RandomArray::indexArray(list.size(), seed);
        for (int i = 0; i < list.size(); i++) {
            Instance* instance = list.get(randomArray.at(i));
            if (counts.count(instance->getClassLabel()) < list.size() * ratio * distribution.getProbability(instance->getClassLabel())) {
                get(0)->add(instance);
            } else {
                get(1)->add(instance);
            }
            counts.put(instance->getClassLabel());
        }
    } else {
        list.shuffle(seed);
        for (int i = 0; i < list.size(); i++) {
            Instance* instance = list.get(i);
            if (i < list.size() * ratio) {
                get(0)->add(instance);
            } else {
                get(1)->add(instance);
            }
        }
    }
}

/**
 * Creates a partition depending on the distinct values of a discrete attribute. If the discrete attribute has 4
 * distinct values, the resulting partition will have 4 groups, where each group contain instance whose
 * values of that discrete attribute are the same.
 *
 * @param attributeIndex Index of the discrete attribute.
 * @return L groups of instances, where L is the number of distinct values of the discrete attribute with index
 * attributeIndex.
 */
Partition::Partition(const InstanceList &list, int attributeIndex) {
    vector<string> valueList = list.getAttributeValueList(attributeIndex);
    for (const string &value : valueList) {
        add(new InstanceList());
    }
    for (Instance* instance : list.getInstances()) {
        string attributeValue = ((DiscreteAttribute*)(instance->getAttribute(attributeIndex)))->getValue();
        get(find(valueList.begin(), valueList.end(), attributeValue) - valueList.begin())->add(instance);
    }
}

/**
 * Creates a partition depending on the distinct values of a discrete indexed attribute.
 *
 * @param attributeIndex Index of the discrete indexed attribute.
 * @param attributeValue Value of the attribute.
 * @return L groups of instances, where L is the number of distinct values of the discrete indexed attribute with index
 * attributeIndex and value attributeValue.
 */
Partition::Partition(const InstanceList &list, int attributeIndex, int attributeValue) {
    add(new InstanceList());
    add(new InstanceList());
    for (Instance* instance : list.getInstances()) {
        int currentAttributeValue = ((DiscreteIndexedAttribute*)(instance->getAttribute(attributeIndex)))->getIndex();
        if (currentAttributeValue == attributeValue) {
            get(0)->add(instance);
        } else {
            get(1)->add(instance);
        }
    }
}

/**
 * Creates a two group partition depending on the values of a continuous attribute. If the value of the attribute is
 * less than splitValue, the instance is forwarded to the first group, else it is forwarded to the second group.
 *
 * @param attributeIndex Index of the continuous attribute
 * @param splitValue     Threshold to divide instances
 * @return Two groups of instances as a partition.
 */
Partition::Partition(const InstanceList &list, int attributeIndex, double splitValue) {
    add(new InstanceList());
    add(new InstanceList());
    for (Instance* instance : list.getInstances()) {
        double attributeValue = ((ContinuousAttribute*)(instance->getAttribute(attributeIndex)))->getValue();
        if (attributeValue <= splitValue) {
            get(0)->add(instance);
        } else {
            get(1)->add(instance);
        }
    }
}
