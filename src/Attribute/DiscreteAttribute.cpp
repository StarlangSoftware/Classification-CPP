//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#include "DiscreteAttribute.h"

/**
 * Constructor for a discrete attribute.
 *
 * @param value Value of the attribute.
 */
DiscreteAttribute::DiscreteAttribute(const string& value) {
    this->value = value;
}

/**
 * Accessor method for value.
 *
 * @return value
 */
string DiscreteAttribute::getValue() const{
    return value;
}

/**
 * Converts value to {@link String}.
 *
 * @return String representation of value.
 */
string DiscreteAttribute::to_string() const{
    if (value == ","){
        return "comma";
    } else {
        return value;
    }
}

DiscreteAttribute::DiscreteAttribute(bool value) {
    if (value){
        this->value = "true";
    } else {
        this->value = "false";
    }
}

int DiscreteAttribute::continuousAttributeSize() const{
    return 0;
}

vector<double> DiscreteAttribute::continuousAttributes() const{
    return {};
}
