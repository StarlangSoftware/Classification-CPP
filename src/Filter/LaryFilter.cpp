//
// Created by Olcay Taner Yıldız on 2.02.2019.
//

#include "LaryFilter.h"

/**
 * Constructor that sets the dataSet and all the attributes distributions.
 *
 * @param dataSet DataSet that will bu used.
 */
LaryFilter::LaryFilter(const DataSet &dataSet) : FeatureFilter(dataSet) {
    attributeDistributions = dataSet.getInstanceList().allAttributesDistribution();
}

/**
 * The removeDiscreteAttributes method takes an {@link Instance} as an input, and removes the discrete attributes from
 * given instance.
 *
 * @param instance Instance to removes attributes from.
 * @param size     Size of the given instance.
 */
void LaryFilter::removeDiscreteAttributes(Instance* instance, int size) {
    int k = 0;
    for (int i = 0; i < size; i++) {
        if (!attributeDistributions.at(i).empty()) {
            instance->removeAttribute(k);
        } else {
            k++;
        }
    }
}

/**
 * The removeDiscreteAttributes method removes the discrete attributes from dataDefinition.
 *
 * @param size Size of item that attributes will be removed.
 */
void LaryFilter::removeDiscreteAttributes(int size) {
    DataDefinition dataDefinition = dataSet.getDataDefinition();
    int k = 0;
    for (int i = 0; i < size; i++) {
        if (!attributeDistributions.at(i).empty()) {
            dataDefinition.removeAttribute(k);
        } else {
            k++;
        }
    }
}
