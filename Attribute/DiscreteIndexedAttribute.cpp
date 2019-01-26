#include <utility>

//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#include "DiscreteIndexedAttribute.h"

/**
 * Constructor for a discrete attribute.
 *
 * @param value Value of the attribute.
 * @param index Index of the attribute.
 * @param maxIndex Maximum index of the attribute.
 */
DiscreteIndexedAttribute::DiscreteIndexedAttribute(string value, int index, int maxIndex) : DiscreteAttribute(move(value)){
    this->index = index;
    this->maxIndex = maxIndex;
}

/**
 * Accessor method for index.
 *
 * @return index.
 */
int DiscreteIndexedAttribute::getIndex() {
    return index;
}

/**
 * Accessor method for maxIndex.
 *
 * @return maxIndex.
 */
int DiscreteIndexedAttribute::getMaxIndex() {
    return maxIndex;
}

int DiscreteIndexedAttribute::continuousAttributeSize() {
    return maxIndex;
}

vector<double> DiscreteIndexedAttribute::continuousAttributes() {
    vector<double> result;
    for (int i = 0; i < maxIndex; i++) {
        if (i != index) {
            result.push_back(0.0);
        } else {
            result.push_back(1.0);
        }
    }
    return result;
}
