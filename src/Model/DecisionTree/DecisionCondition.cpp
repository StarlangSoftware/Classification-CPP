//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include <ostream>
#include <fstream>
#include "DecisionCondition.h"
#include "../../Attribute/DiscreteIndexedAttribute.h"
#include "../../Attribute/ContinuousAttribute.h"

/**
 * A constructor that sets attributeIndex and Attribute value. It also assigns equal sign to the comparison character.
 *
 * @param attributeIndex Integer number that shows attribute index.
 * @param value          The value of the Attribute.
 */
DecisionCondition::DecisionCondition(int attributeIndex, Attribute *value) {
    this->attributeIndex = attributeIndex;
    comparison = '=';
    this->value = value;
}

/**
 * A constructor that sets attributeIndex, comparison and Attribute value.
 *
 * @param attributeIndex Integer number that shows attribute index.
 * @param value          The value of the Attribute.
 * @param comparison     Comparison character.
 */
DecisionCondition::DecisionCondition(int attributeIndex, char comparison, Attribute *value) {
    this->attributeIndex = attributeIndex;
    this->comparison = comparison;
    this->value = value;
}

/**
 * The satisfy method takes an Instance as an input.
 * <p>
 * If defined Attribute value is a DiscreteIndexedAttribute it compares the index of Attribute of instance at the
 * attributeIndex and the index of Attribute value and returns the result.
 * <p>
 * If defined Attribute value is a DiscreteAttribute it compares the value of Attribute of instance at the
 * attributeIndex and the value of Attribute value and returns the result.
 * <p>
 * If defined Attribute value is a ContinuousAttribute it compares the value of Attribute of instance at the
 * attributeIndex and the value of Attribute value and returns the result according to the comparison character whether it is
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

/**
 * Accessor for the attribute index.
 * @return Attribute index.
 */
int DecisionCondition::getAttributeIndex() const{
    return attributeIndex;
}

/**
 * Default constructor
 */
DecisionCondition::DecisionCondition() = default;

/**
 * Prints the decision condition into an output file.
 * @param outputFile Output file
 */
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

/**
 * Reads a decision condition from an input file
 * @param inputFile Input file
 */
DecisionCondition::DecisionCondition(ifstream &inputFile) {
    string type;
    int maxIndex;
    inputFile >> attributeIndex;
    inputFile >> comparison;
    inputFile >> type;
    if (attributeIndex != -1){
        if (comparison == '='){
            value = new DiscreteAttribute(type);
        } else {
            if (comparison == ':'){
                comparison = '=';
                inputFile >> maxIndex;
                value = new DiscreteIndexedAttribute("", stoi(type), maxIndex);
            } else {
                value = new ContinuousAttribute(stof(type));
            }
        }
    }
}
