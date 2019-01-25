//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#include "BinaryAttribute.h"

/**
 * Constructor for a binary discrete attribute. The attribute can take only two values "True" or "False".
 *
 * @param value Value of the attribute. Can be true or false.
 */
BinaryAttribute::BinaryAttribute(bool value) : DiscreteAttribute(value) {
}
