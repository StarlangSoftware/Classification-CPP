//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#ifndef CLASSIFICATION_DATADEFINITION_H
#define CLASSIFICATION_DATADEFINITION_H

#include <vector>
#include "../Attribute/AttributeType.h"
#include "../FeatureSelection/FeatureSubSet.h"

using namespace std;

class DataDefinition {
private:
    vector<AttributeType> attributeTypes;
public:
    DataDefinition();
    explicit DataDefinition(const vector<AttributeType>& attributeTypes);
    DataDefinition getSubSetOfFeatures(const FeatureSubSet& featureSubSet);
    int attributeCount() const;
    int discreteAttributeCount() const;
    int continuousAttributeCount() const;
    AttributeType getAttributeType(int index) const;
    void addAttribute(AttributeType attributeType);
    void removeAttribute(int index);
    void removeAllAttributes();
};


#endif //CLASSIFICATION_DATADEFINITION_H
