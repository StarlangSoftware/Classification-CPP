//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#ifndef CLASSIFICATION_DATADEFINITION_H
#define CLASSIFICATION_DATADEFINITION_H

#include <vector>
#include <string>
#include "../Attribute/AttributeType.h"
#include "../FeatureSelection/FeatureSubSet.h"

using namespace std;

class DataDefinition {
private:
    vector<AttributeType> attributeTypes;
    vector<vector<string>> attributeValueList;
public:
    DataDefinition();
    DataDefinition(const vector<AttributeType>& attributeTypes, const vector<vector<string>>& attributeValueList);
    explicit DataDefinition(const vector<AttributeType>& attributeTypes);
    DataDefinition getSubSetOfFeatures(const FeatureSubSet& featureSubSet);
    int attributeCount() const;
    int discreteAttributeCount() const;
    int continuousAttributeCount() const;
    AttributeType getAttributeType(int index) const;
    void addAttribute(AttributeType attributeType);
    void removeAttribute(int index);
    void removeAllAttributes();
    int numberOfValues(int attributeIndex) const;
    int featureValueIndex(int attributeIndex, const string& value) const;
};


#endif //CLASSIFICATION_DATADEFINITION_H
