//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#ifndef CLASSIFICATION_DATADEFINITION_H
#define CLASSIFICATION_DATADEFINITION_H

#include <vector>
#include "../Attribute/AttributeType.h"
using namespace std;

class DataDefinition {
private:
    vector<AttributeType> attributeTypes;
public:
    DataDefinition();
    DataDefinition(vector<AttributeType> attributeTypes);
    int attributeCount();
    int discreteAttributeCount();
    int continuousAttributeCount();
    AttributeType getAttributeType(int index);
    void addAttribute(AttributeType attributeType);
    void removeAttribute(int index);
    void removeAllAttributes();
};


#endif //CLASSIFICATION_DATADEFINITION_H
