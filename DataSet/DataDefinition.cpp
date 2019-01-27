//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#include "DataDefinition.h"

/**
 * Constructor for creating a new {@link DataDefinition}.
 */
DataDefinition::DataDefinition() {

}

/**
 * Constructor for creating a new {@link DataDefinition} with given attribute types.
 *
 * @param attributeTypes Attribute types of the data definition.
 */
DataDefinition::DataDefinition(vector<AttributeType> attributeTypes) {
    this->attributeTypes = attributeTypes;
}

/**
 * Returns the number of attribute types.
 *
 * @return Number of attribute types.
 */
int DataDefinition::attributeCount() {
    return attributeTypes.size();
}

/**
 * Counts the occurrences of binary and discrete type attributes.
 *
 * @return Count of binary and discrete type attributes.
 */
int DataDefinition::discreteAttributeCount() {
    int count = 0;
    for (AttributeType attributeType : attributeTypes) {
        if (attributeType == AttributeType::DISCRETE || attributeType == AttributeType::BINARY) {
            count++;
        }
    }
    return count;
}

/**
 * Counts the occurrences of binary and continuous type attributes.
 *
 * @return Count of of binary and continuous type attributes.
 */
int DataDefinition::continuousAttributeCount() {
    int count = 0;
    for (AttributeType attributeType : attributeTypes) {
        if (attributeType == AttributeType::CONTINUOUS) {
            count++;
        }
    }
    return count;
}

/**
 * Returns the attribute type of the corresponding item at given index.
 *
 * @param index Index of the attribute type.
 * @return Attribute type of the corresponding item at given index.
 */
AttributeType DataDefinition::getAttributeType(int index) {
    return attributeTypes.at(index);
}

/**
 * Adds an attribute type to the list of attribute types.
 *
 * @param attributeType Attribute type to add to the list of attribute types.
 */
void DataDefinition::addAttribute(AttributeType attributeType) {
    attributeTypes.push_back(attributeType);
}

/**
 * Removes the attribute type at given index from the list of attributes.
 *
 * @param index Index to remove attribute type from list.
 */
void DataDefinition::removeAttribute(int index) {
    attributeTypes.erase(attributeTypes.begin() + index);
}

/**
 * Clears all the attribute types from list.
 */
void DataDefinition::removeAllAttributes() {
    attributeTypes.clear();
}
