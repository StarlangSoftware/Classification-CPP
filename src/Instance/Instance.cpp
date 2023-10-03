//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#include <ostream>
#include "Instance.h"
#include "../Attribute/DiscreteAttribute.h"
#include "../Attribute/ContinuousAttribute.h"

/**
 * Constructor for a single instance. Given the attributes and class label, it generates a new instance.
 *
 * @param classLabel Class label of the instance.
 * @param attributes Attributes of the instance.
 */
Instance::Instance(const string& classLabel, const vector<Attribute *>& attributes) {
    this->classLabel = classLabel;
    this->attributes = attributes;
}

/**
 * Constructor for a single instance. Given the class label, it generates a new instance with 0 attributes.
 * Attributes must be added later with different addAttribute methods.
 *
 * @param classLabel Class label of the instance.
 */
Instance::Instance(const string& classLabel) {
    this->classLabel = classLabel;
}

/**
 * Adds a discrete attribute with the given String value.
 *
 * @param value Value of the discrete attribute.
 */
void Instance::addAttribute(const string& value) {
    attributes.push_back(new DiscreteAttribute(value));
}

/**
 * Adds a continuous attribute with the given double value.
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
 * Adds a Vector of continuous attributes.
 *
 * @param vector Vector that has the continuous attributes.
 */
void Instance::addVectorAttribute(const Vector& vector) {
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
Attribute *Instance::getAttribute(int index) const{
    return attributes.at(index);
}

/**
 * Returns the number of attributes in the attributes list.
 *
 * @return Number of attributes in the attributes list.
 */
int Instance::attributeSize() const{
    return attributes.size();
}

/**
 * Returns the number of continuous and discrete indexed attributes in the attributes list.
 *
 * @return Number of continuous and discrete indexed attributes in the attributes list.
 */
int Instance::continuousAttributeSize() const{
    int size = 0;
    for (Attribute* attribute : attributes) {
        size += attribute->continuousAttributeSize();
    }
    return size;
}

/**
 * The continuousAttributes method creates a new vector result and it adds the continuous attributes of the
 * attributes list and also it adds 1 for the discrete indexed attributes
 * .
 *
 * @return result vector that has continuous and discrete indexed attributes.
 */
vector<double> Instance::continuousAttributes() const{
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
string Instance::getClassLabel() const{
    return classLabel;
}

vector<string> Instance::getPossibleClassLabels() const{
    vector<string> classLabels;
    classLabels.push_back(classLabel);
    return classLabels;
}

/**
 * Converts instance to a String.
 *
 * @return A string of attributes separated with comma character.
 */
string Instance::to_string() const{
    string result;
    for (Attribute* attribute : attributes) {
        result += attribute->to_string() + ",";
    }
    result = result + classLabel;
    return result;
}

/**
 * The toVector method returns a Vector of continuous attributes and discrete indexed attributes.
 *
 * @return Vector of continuous attributes and discrete indexed attributes.
 */
Vector Instance::toVector() const{
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

/**
 * The getSubSetOfFeatures method takes a FeatureSubSet as an input. First it creates a result Instance
 * with the class label, and adds the attributes of the given featureSubSet to it.
 *
 * @param featureSubSet FeatureSubSet an vector of indices.
 * @return result Instance.
 */
Instance *Instance::getSubSetOfFeatures(const FeatureSubSet& featureSubSet) const{
    auto* result = new Instance(classLabel);
    for (int i = 0; i < featureSubSet.size(); i++) {
        result->addAttribute(attributes.at(featureSubSet.get(i)));
    }
    return result;
}

/**
 * Returns a new NodeList with the ArrayList that has continuous and discrete indexed attributes.
 *
 * @return NodeList that has continuous and discrete indexed attributes.
 */
NodeList Instance::toNodeList() const{
    return NodeList(continuousAttributes());
}

void Instance::serialize(ostream &outputFile) {
    for (Attribute* attribute : attributes){
        outputFile << attribute->to_string() << " ";
    }
    outputFile << classLabel << "\n";
}
