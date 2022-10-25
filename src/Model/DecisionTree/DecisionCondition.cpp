//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include <ostream>
#include <fstream>
#include "DecisionCondition.h"
#include "../../Attribute/DiscreteIndexedAttribute.h"
#include "../../Attribute/ContinuousAttribute.h"

/**
 * A constructor that sets attributeIndex and {@link Attribute} value. It also assigns equal sign to the comparison character.
 *
 * @param attributeIndex Integer number that shows attribute index.
 * @param value          The value of the {@link Attribute}.
 */
DecisionCondition::DecisionCondition(int attributeIndex, Attribute *value) {
    this->attributeIndex = attributeIndex;
    comparison = '=';
    this->value = value;
}

/**
 * A constructor that sets attributeIndex, comparison and {@link Attribute} value.
 *
 * @param attributeIndex Integer number that shows attribute index.
 * @param value          The value of the {@link Attribute}.
 * @param comparison     Comparison character.
 */
DecisionCondition::DecisionCondition(int attributeIndex, char comparison, Attribute *value) {
    this->attributeIndex = attributeIndex;
    this->comparison = comparison;
    this->value = value;
}

/**
 * The satisfy method takes an {@link Instance} as an input.
 * <p>
 * If defined {@link Attribute} value is a {@link DiscreteIndexedAttribute} it compares the index of {@link Attribute} of instance at the
 * attributeIndex and the index of {@link Attribute} value and returns the result.
 * <p>
 * If defined {@link Attribute} value is a {@link DiscreteAttribute} it compares the value of {@link Attribute} of instance at the
 * attributeIndex and the value of {@link Attribute} value and returns the result.
 * <p>
 * If defined {@link Attribute} value is a {@link ContinuousAttribute} it compares the value of {@link Attribute} of instance at the
 * attributeIndex and the value of {@link Attribute} value and returns the result according to the comparison character whether it is
 * less than or greater than signs.
 *
 * @param instance Instance to compare.
 * @return True if gicen instance satisfies the conditions.
 */
bool DecisionCondition::satisfy(Instance *instance) const{
    if (value->isDiscreteIndexed()) {
        if (((DiscreteIndexedAttribute*) value)->getIndex() != -1) {
            return ((DiscreteIndexedAttribute*) instance->getAttribute(attributeIndex))->getIndex() == ((DiscreteIndexedAttribute*) value)->getIndex();
        } else {
            return true;
        }
    } else {
        if (value->isDiscrete()) {
            return (((DiscreteAttribute*) instance->getAttribute(attributeIndex))->getValue() == ((DiscreteAttribute*) value)->getValue());
        } else {
            if (value->isContinuous()) {
                if (comparison == '<') {
                    return ((ContinuousAttribute*) instance->getAttribute(attributeIndex))->getValue() <= ((ContinuousAttribute*) value)->getValue();
                } else {
                    if (comparison == '>') {
                        return ((ContinuousAttribute*) instance->getAttribute(attributeIndex))->getValue() > ((ContinuousAttribute*) value)->getValue();
                    }
                }
            }
        }
    }
    return false;
}

int DecisionCondition::getAttributeIndex() const{
    return attributeIndex;
}

DecisionCondition::DecisionCondition() = default;

void DecisionCondition::serialize(ostream &outputFile) {
    outputFile << attributeIndex << "\n";
    if (attributeIndex != -1){
        outputFile << comparison << "\n";
        if (value->isDiscrete()){
            outputFile << "Discrete\n";
        } else {
            if (value->isContinuous()){
                outputFile << "Continuous\n";
            }
        }
        outputFile << value->to_string() << "\n";
    }
}

DecisionCondition::DecisionCondition(ifstream &inputFile) {
    string type, discreteAttribute;
    double continuousAttribute;
    inputFile >> attributeIndex;
    if (attributeIndex != -1){
        inputFile >> comparison;
        inputFile >> type;
        if (type == "Discrete"){
            inputFile >> discreteAttribute;
            value = new DiscreteAttribute(discreteAttribute);
        } else {
            if (type == "Continuous"){
                inputFile >> continuousAttribute;
                value = new ContinuousAttribute(continuousAttribute);
            }
        }
    } else {

    }
}
