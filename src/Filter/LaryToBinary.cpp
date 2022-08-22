//
// Created by Olcay Taner Yıldız on 4.02.2019.
//

#include "LaryToBinary.h"
#include "../Attribute/BinaryAttribute.h"

/**
 * Constructor for L-ary discrete to binary discrete filter.
 *
 * @param dataSet The instances whose L-ary discrete attributes will be converted to binary discrete attributes.
 */
LaryToBinary::LaryToBinary(DataSet &dataSet) : LaryFilter(dataSet) {
}

/**
 * Converts discrete attributes of a single instance to binary discrete version using 1-of-L encoding. For example, if
 * an attribute has values red, green, blue; this attribute will be converted to 3 binary attributes where
 * red will have the value true false false, green will have the value false true false, and blue will have the value false false true.
 *
 * @param instance The instance to be converted.
 */
void LaryToBinary::convertInstance(Instance* instance) {
    int size = instance->attributeSize();
    for (int i = 0; i < size; i++) {
        if (!attributeDistributions.at(i).empty()) {
            int index = attributeDistributions.at(i).getIndex(instance->getAttribute(i)->to_string());
            for (int j = 0; j < attributeDistributions.at(i).size(); j++) {
                if (j != index) {
                    instance->addAttribute(new BinaryAttribute(false));
                } else {
                    instance->addAttribute(new BinaryAttribute(true));
                }
            }
        }
    }
    removeDiscreteAttributes(instance, size);
}

/**
 * Converts the data definition with L-ary discrete attributes, to data definition with binary discrete attributes.
 */
void LaryToBinary::convertDataDefinition() {
    DataDefinition dataDefinition = dataSet.getDataDefinition();
    int size = dataDefinition.attributeCount();
    for (int i = 0; i < size; i++) {
        if (!attributeDistributions.at(i).empty()) {
            for (int j = 0; j < attributeDistributions.at(i).size(); j++) {
                dataDefinition.addAttribute(AttributeType::BINARY);
            }
        }
    }
    removeDiscreteAttributes(size);
}
