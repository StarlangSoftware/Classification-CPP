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
double ContinuousAttribute::getValue() const {
    return value;
}

/**
 * Mutator method for _value
 *
 * @param _value New _value of _value.
 */
void ContinuousAttribute::setValue(double _value) {
    this->value = _value;
}

/**
 * Converts value to {@link String}.
 *
 * @return String representation of value.
 */
string ContinuousAttribute::to_string() const{
    return std::to_string(value);
}

int ContinuousAttribute::continuousAttributeSize() const{
    return 1;
}

vector<double> ContinuousAttribute::continuousAttributes() const{
    vector<double> result;
    result.push_back(value);
    return result;
}
