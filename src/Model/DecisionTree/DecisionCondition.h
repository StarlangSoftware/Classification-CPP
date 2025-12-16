//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_DECISIONCONDITION_H
#define CLASSIFICATION_DECISIONCONDITION_H
#include "../../Attribute/Attribute.h"
#include "../../Instance/Instance.h"

class DecisionCondition {
private:
    int attributeIndex = -1;
    char comparison;
    Attribute* value;
public:
    DecisionCondition();
    explicit DecisionCondition(ifstream& inputFile);
    DecisionCondition(int attributeIndex, Attribute* value);
    DecisionCondition(int attributeIndex, char comparison, Attribute* value);
    bool satisfy(Instance* instance) const;
    [[nodiscard]] int getAttributeIndex() const;
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_DECISIONCONDITION_H
