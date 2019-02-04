//
// Created by Olcay Taner Yıldız on 4.02.2019.
//

#include "DiscreteToIndexed.h"
#include "../Attribute/DiscreteIndexedAttribute.h"

/**
 * Constructor for discrete to indexed filter.
 *
 * @param dataSet The dataSet whose instances whose discrete attributes will be converted to indexed attributes
 */
DiscreteToIndexed::DiscreteToIndexed(DataSet &dataSet) : LaryFilter(dataSet) {

}

/**
 * Converts discrete attributes of a single instance to indexed version.
 *
 * @param instance The instance to be converted.
 */
void DiscreteToIndexed::convertInstance(Instance *instance) {
    int size = instance->attributeSize();
    for (int i = 0; i < size; i++) {
        if (!attributeDistributions.at(i).empty()) {
            int index = attributeDistributions.at(i).getIndex(instance->getAttribute(i)->to_string());
            instance->addAttribute(new DiscreteIndexedAttribute(instance->getAttribute(i)->to_string(), index, attributeDistributions.at(i).size()));
        }
    }
    removeDiscreteAttributes(instance, size);
}

/**
 * Converts the data definition with discrete attributes, to data definition with DISCRETE_INDEXED attributes.
 */
void DiscreteToIndexed::convertDataDefinition() {
    DataDefinition dataDefinition = dataSet.getDataDefinition();
    int size = dataDefinition.attributeCount();
    for (int i = 0; i < size; i++) {
        if (!attributeDistributions.at(i).empty()) {
            dataDefinition.addAttribute(AttributeType::DISCRETE_INDEXED);
        }
    }
    removeDiscreteAttributes(size);
}
