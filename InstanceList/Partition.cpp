//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#include "Partition.h"

/**
 * Constructor for generating a partition.
 */
Partition::Partition() {
}

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
int Partition::size() {
    return multiList.size();
}

/**
 * Returns the corresponding instance list at given index of list of instance lists.
 *
 * @param index Index of the instance list.
 * @return Instance list at given index of list of instance lists.
 */
InstanceList* Partition::get(int index) {
    return multiList.at(index);
}

/**
 * Returns the instances of the items at the list of instance lists.
 *
 * @return Instances of the items at the list of instance lists.
 */
vector<Instance *> *Partition::getLists() {
    vector<Instance*>* result = new vector<Instance*>[multiList.size()];
    for (int i = 0; i < multiList.size(); i++) {
        result[i] = multiList.at(i)->getInstances();
    }
    return result;
}
