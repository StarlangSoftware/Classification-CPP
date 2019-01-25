//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#include "ContinuousAttribute.h"

/**
 * Constructor for a continuous attribute.
 *
 * @param value Value of the attribute.
 */
ContinuousAttribute::ContinuousAttribute(double value) {
    this->value = value;
}

/**
 * Accessor method for value.
 *
 * @return value
 */
double ContinuousAttribute::getValue() {
    return value;
}

/**
 * Mutator method for value
 *
 * @param value New value of value.
 */
void ContinuousAttribute::setValue(double value) {
    this->value = value;
}

/**
 * Converts value to {@link String}.
 *
 * @return String representation of value.
 */
string ContinuousAttribute::to_string() {
    return std::to_string(value);
}
