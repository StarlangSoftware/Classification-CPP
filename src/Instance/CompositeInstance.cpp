#include <utility>

//
// Created by Olcay Taner Yıldız on 26.01.2019.
//

#include "CompositeInstance.h"

/**
 * Constructor of CompositeInstance class which takes a class label as an input. It generates a new composite instance
 * with given class label.
 *
 * @param classLabel Class label of the composite instance.
 */
CompositeInstance::CompositeInstance(const string& classLabel) : Instance(classLabel) {
}

/**
 * Constructor of CompositeInstance class which takes a class label and attributes as inputs. It generates
 * a new composite instance with given class label and attributes.
 *
 * @param classLabel Class label of the composite instance.
 * @param attributes Attributes of the composite instance.
 */
CompositeInstance::CompositeInstance(const string& classLabel, const vector<Attribute *>& attributes) : Instance(classLabel, attributes) {
}

/**
 * Constructor of CompositeInstance class which takes an {@link java.lang.reflect.Array} of possible labels as
 * input. It generates a new composite instance with given labels.
 *
 * @param possibleLabels Possible labels of the composite instance.
 */
CompositeInstance::CompositeInstance(const vector<string>& possibleLabels) : Instance(possibleLabels.at(0)) {
    this->possibleClassLabels.insert(this->possibleClassLabels.end(), possibleLabels.begin() + 1, possibleLabels.end());
}

/**
 * Constructor of CompositeInstance class which takes a class label, attributes and an ArrayList of
 * possible labels as inputs. It generates a new composite instance with given labels, attributes and possible labels.
 *
 * @param classLabel          Class label of the composite instance.
 * @param attributes          Attributes of the composite instance.
 * @param possibleClassLabels Possible labels of the composite instance.
 */
CompositeInstance::CompositeInstance(const string& classLabel, const vector<Attribute *>& attributes,
                                     const vector<string>& possibleClassLabels) : Instance(classLabel, attributes) {
    this->possibleClassLabels.insert(this->possibleClassLabels.end(), possibleClassLabels.begin(), possibleClassLabels.end());
}

/**
 * Accessor for the possible class labels.
 *
 * @return Possible class labels of the composite instance.
 */
vector<string> CompositeInstance::getPossibleClassLabels() const{
    return possibleClassLabels;
}

/**
 * Mutator method for possible class labels.
 *
 * @param _possibleClassLabels value of possible class labels.
 */
void CompositeInstance::setPossibleClassLabels(const vector<string>& _possibleClassLabels) {
    this->possibleClassLabels.insert(this->possibleClassLabels.end(), _possibleClassLabels.begin(), _possibleClassLabels.end());
}

/**
 * Converts possible class labels to String.
 *
 * @return String representation of possible class labels.
 */
string CompositeInstance::to_string() const{
    string result = Instance::to_string();
    for (const string &possibleClassLabel : possibleClassLabels) {
        result.append(";").append(possibleClassLabel);
    }
    return result;
}
