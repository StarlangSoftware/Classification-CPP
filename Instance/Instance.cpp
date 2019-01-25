//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#include "Instance.h"
#include "../Attribute/DiscreteAttribute.h"
#include "../Attribute/ContinuousAttribute.h"

/**
 * Constructor for a single instance. Given the attributes and class label, it generates a new instance.
 *
 * @param classLabel Class label of the instance.
 * @param attributes Attributes of the instance.
 */
Instance::Instance(string classLabel, vector<Attribute *> attributes) {
    this->classLabel = move(classLabel);
    this->attributes = move(attributes);
}

/**
 * Constructor for a single instance. Given the class label, it generates a new instance with 0 attributes.
 * Attributes must be added later with different addAttribute methods.
 *
 * @param classLabel Class label of the instance.
 */
Instance::Instance(string classLabel) {
    this->classLabel = move(classLabel);
}

/**
 * Adds a discrete attribute with the given {@link String} value.
 *
 * @param value Value of the discrete attribute.
 */
void Instance::addAttribute(string value) {
    attributes.push_back(new DiscreteAttribute(move(value)));
}

/**
 * Adds a continuous attribute with the given {@link double} value.
 *
 * @param value Value of the continuous attribute.
 */
void Instance::addAttribute(double value) {
    attributes.push_back(new ContinuousAttribute(value));
}

/**
 * Adds a new attribute.
 *
 * @param attribute Attribute to be added.
 */
void Instance::addAttribute(Attribute *attribute) {
    attributes.push_back(attribute);
}

/**
 * Adds a {@link Vector} of continuous attributes.
 *
 * @param vector {@link Vector} that has the continuous attributes.
 */
void Instance::addVectorAttribute(Vector vector) {
    for (int i = 0; i < vector.getSize(); i++) {
        attributes.push_back(new ContinuousAttribute(vector.getValue(i)));
    }
}
