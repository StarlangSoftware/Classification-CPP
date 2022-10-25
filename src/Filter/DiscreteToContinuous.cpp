//
// Created by Olcay Taner Yıldız on 2.02.2019.
//

#include "DiscreteToContinuous.h"
#include "../Attribute/ContinuousAttribute.h"

/**
 * Constructor for discrete to continuous filter.
 *
 * @param dataSet The dataSet whose instances whose discrete attributes will be converted to continuous attributes using
 *                1-of-L encoding.
 */
DiscreteToContinuous::DiscreteToContinuous(const DataSet& dataSet) : LaryFilter(dataSet) {
}

/**
 * Converts discrete attributes of a single instance to continuous version using 1-of-L encoding. For example, if
 * an attribute has values red, green, blue; this attribute will be converted to 3 continuous attributes where
 * red will have the value 100, green will have the value 010, and blue will have the value 001.
 *
 * @param instance The instance to be converted.
 */
void DiscreteToContinuous::convertInstance(Instance* instance) {
    int size = instance->attributeSize();
    for (int i = 0; i < size; i++) {
        if (!attributeDistributions.at(i).empty()) {
            DiscreteDistribution distribution = attributeDistributions.at(i);
            int index = distribution.getIndex(instance->getAttribute(i)->to_string());
            for (int j = 0; j < distribution.size(); j++) {
                if (j != index) {
                    instance->addAttribute(new ContinuousAttribute(0));
                } else {
                    instance->addAttribute(new ContinuousAttribute(1));
                }
            }
        }
    }
    removeDiscreteAttributes(instance, size);
}

/**
 * Converts the data definition with discrete attributes, to data definition with continuous attributes. Basically,
 * for each discrete attribute with L possible values, L more continuous attributes will be added.
 */
void DiscreteToContinuous::convertDataDefinition() {
    DataDefinition dataDefinition = dataSet.getDataDefinition();
    int size = dataDefinition.attributeCount();
    for (int i = 0; i < size; i++) {
        if (!attributeDistributions.at(i).empty()) {
            for (int j = 0; j < attributeDistributions.at(i).size(); j++) {
                dataDefinition.addAttribute(AttributeType::CONTINUOUS);
            }
        }
    }
    removeDiscreteAttributes(size);
}
