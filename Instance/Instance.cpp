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

/**
 * Removes attribute with the given index from the attributes list.
 *
 * @param index Index of the attribute to be removed.
 */
void Instance::removeAttribute(int index) {
    attributes.erase(attributes.begin() + index);
}

/**
 * Removes all the attributes from the attributes list.
 */
void Instance::removeAllAttributes() {
    attributes.clear();
}

/**
 * Accessor for a single attribute.
 *
 * @param index Index of the attribute to be accessed.
 * @return Attribute with index 'index'.
 */
Attribute *Instance::getAttribute(int index) {
    return attributes.at(index);
}

/**
 * Returns the number of attributes in the attributes list.
 *
 * @return Number of attributes in the attributes list.
 */
int Instance::attributeSize() {
    return attributes.size();
}

/**
 * Returns the number of continuous and discrete indexed attributes in the attributes list.
 *
 * @return Number of continuous and discrete indexed attributes in the attributes list.
 */
int Instance::continuousAttributeSize() {
    int size = 0;
    for (Attribute* attribute : attributes) {
        size += attribute->continuousAttributeSize();
    }
    return size;
}

/**
 * The continuousAttributes method creates a new {@link vector} result and it adds the continuous attributes of the
 * attributes list and also it adds 1 for the discrete indexed attributes
 * .
 *
 * @return result {@link vector} that has continuous and discrete indexed attributes.
 */
vector<double> Instance::continuousAttributes() {
    vector<double> result;
    for (Attribute* attribute : attributes) {
        vector<double> inserted = attribute->continuousAttributes();
        result.insert(result.end(), inserted.begin(), inserted.end());
    }
    return result;
}

/**
 * Accessor for the class label.
 *
 * @return Class label of the instance.
 */
string Instance::getClassLabel() {
    return classLabel;
}

vector<string> Instance::getPossibleClassLabels() {
    vector<string> classLabels;
    classLabels.push_back(classLabel);
    return classLabels;
}

/**
 * Converts instance to a {@link String}.
 *
 * @return A string of attributes separated with comma character.
 */
string Instance::to_string() {
    string result;
    for (Attribute* attribute : attributes) {
        result = result + attribute->to_string() + ",";
    }
    result = result + classLabel;
    return result;
}

/**
 * The toVector method returns a {@link Vector} of continuous attributes and discrete indexed attributes.
 *
 * @return {@link Vector} of continuous attributes and discrete indexed attributes.
 */
Vector Instance::toVector() {
    vector<double> values;
    for (Attribute* attribute : attributes) {
        vector<double> inserted = attribute->continuousAttributes();
        values.insert(values.end(), inserted.begin(), inserted.end());
    }
    return Vector(values);
}

Instance::~Instance() {
    for (Attribute* attribute : attributes){
        delete attribute;
    }
}
