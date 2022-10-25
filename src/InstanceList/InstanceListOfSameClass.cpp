//
// Created by olcay on 28.01.2019.
//

#include "InstanceListOfSameClass.h"

/**
 * Constructor for creating a new instance list with the same class labels.
 *
 * @param classLabel Class labels of instance list.
 */
InstanceListOfSameClass::InstanceListOfSameClass(const string& classLabel) {
    this->classLabel = classLabel;
}

/**
 * Accessor for the class labels.
 *
 * @return Class labels.
 */
string InstanceListOfSameClass::getClassLabel() const{
    return classLabel;
}
