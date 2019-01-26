//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#include "DiscreteAttribute.h"

/**
 * Constructor for a discrete attribute.
 *
 * @param value Value of the attribute.
 */
DiscreteAttribute::DiscreteAttribute(string value) {
    this->value = move(value);
}

/**
 * Accessor method for value.
 *
 * @return value
 */
string DiscreteAttribute::getValue() {
    return value;
}

/**
 * Converts value to {@link String}.
 *
 * @return String representation of value.
 */
string DiscreteAttribute::to_string() {
    if (value == ","){
        return "comma";
    } else {
        return value;
    }
}

DiscreteAttribute::DiscreteAttribute(bool value) {
    if (value){
        value = "true";
    } else {
        value = "false";
    }
}

int DiscreteAttribute::continuousAttributeSize() {
    return 0;
}

vector<double> DiscreteAttribute::continuousAttributes() {
    return vector<double>();
}
