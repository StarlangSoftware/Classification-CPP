//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#include "DataDefinition.h"

/**
 * Constructor for creating a new {@link DataDefinition}.
 */
DataDefinition::DataDefinition() = default;

/**
 * Constructor for creating a new {@link DataDefinition} with given attribute types.
 *
 * @param attributeTypes Attribute types of the data definition.
 */
DataDefinition::DataDefinition(const vector<AttributeType>& attributeTypes) {
    this->attributeTypes = attributeTypes;
}

/**
 * Returns the number of attribute types.
 *
 * @return Number of attribute types.
 */
int DataDefinition::attributeCount() const{
    return attributeTypes.size();
}

/**
 * Counts the occurrences of binary and discrete type attributes.
 *
 * @return Count of binary and discrete type attributes.
 */
int DataDefinition::discreteAttributeCount() const{
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
int DataDefinition::continuousAttributeCount() const{
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
AttributeType DataDefinition::getAttributeType(int index) const{
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

/**
 * Generates new subset of attribute types by using given feature subset.
 *
 * @param featureSubSet {@link FeatureSubSet} input.
 * @return DataDefinition with new subset of attribute types.
 */
DataDefinition DataDefinition::getSubSetOfFeatures(const FeatureSubSet& featureSubSet) {
    vector<AttributeType> newAttributeTypes;
    newAttributeTypes.reserve(featureSubSet.size());
    for (int i = 0; i < featureSubSet.size(); i++) {
        newAttributeTypes.push_back(attributeTypes.at(featureSubSet.get(i)));
    }
    return DataDefinition(newAttributeTypes);
}

int DataDefinition::numberOfValues(int attributeIndex) const{
    return attributeValueList[attributeIndex].size();
}

int DataDefinition::featureValueIndex(int attributeIndex, const string& value) const{
    for (int i = 0; i < attributeValueList[attributeIndex].size(); i++){
        if (attributeValueList[attributeIndex][i] == value){
            return i;
        }
    }
    return -1;
}

/**
 * Constructor for creating a new {@link DataDefinition} with given attribute types.
 *
 * @param attributeTypes Attribute types of the data definition.
 * @param attributeValueList Array of array of strings to represent all possible values of discrete features.
 */
DataDefinition::DataDefinition(const vector<AttributeType> &attributeTypes, const vector<vector<string>> &attributeValueList) {
    this->attributeTypes = attributeTypes;
    this->attributeValueList = attributeValueList;
}
