#include <utility>

//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#include <fstream>
#include <random>
#include "InstanceList.h"
#include "../Attribute/DiscreteAttribute.h"
#include "../Attribute/BinaryAttribute.h"
#include "../Attribute/ContinuousAttribute.h"

using namespace std;
/**
 * Empty constructor for an instance list. Initializes the instance list with zero instances.
 */
InstanceList::InstanceList() {
}

/**
 * Constructor for an instance list with a given data definition, data file and a separator character. Each instance
 * must be stored in a separate line separated with the character separator. The last item must be the class label.
 * The function reads the file line by line and for each line; depending on the data definition, that is, type of
 * the attributes, adds discrete and continuous attributes to a new instance. For example, given the data set file
 * <p>
 * red;1;0.4;true
 * green;-1;0.8;true
 * blue;3;1.3;false
 * <p>
 * where the first attribute is a discrete attribute, second and third attributes are continuous attributes, the
 * fourth item is the class label.
 *
 * @param definition Data definition of the data set.
 * @param separator  Separator character which separates the attribute values in the data file.
 * @param fileName   Name of the data set file.
 */
InstanceList::InstanceList(DataDefinition definition, string separator, string fileName) {
    Instance* current;
    string line;
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    getline(inputFile, line);
    while (inputFile.good()) {
        size_t currentPos, previousPos = 0;
        vector<string> attributeList;
        currentPos = line.find_first_of(separator);
        while (currentPos != string::npos) {
            attributeList.push_back(line.substr(previousPos, currentPos - previousPos));
            previousPos = currentPos + 1;
            currentPos = line.find_first_of(separator, previousPos);
        }
        attributeList.push_back(line.substr(previousPos, currentPos - previousPos));
        if (attributeList.size() == definition.attributeCount() + 1) {
            current = new Instance(attributeList[attributeList.size() - 1]);
            for (int i = 0; i < attributeList.size() - 1; i++) {
                switch (definition.getAttributeType(i)) {
                    case AttributeType::DISCRETE:
                        current->addAttribute(new DiscreteAttribute(attributeList[i]));
                        break;
                    case AttributeType::BINARY:
                        current->addAttribute(new BinaryAttribute(attributeList[i]));
                        break;
                    case AttributeType::CONTINUOUS:
                        current->addAttribute(new ContinuousAttribute(stod(attributeList[i])));
                        break;
                    case AttributeType::DISCRETE_INDEXED:
                        break;
                }
            }
            list.push_back(current);
        }
        getline(inputFile, line);
    }
}

/**
 * Mutator for the list variable.
 *
 * @param list New list for the list variable.
 */
InstanceList::InstanceList(vector<Instance *> list) {
    this->list = list;
}

/**
 * Adds instance to the instance list.
 *
 * @param instance Instance to be added.
 */
void InstanceList::add(Instance *instance) {
    list.push_back(instance);
}

/**
 * Adds a list of instances to the current instance list.
 *
 * @param instanceList List of instances to be added.
 */
void InstanceList::addAll(vector<Instance *> instanceList) {
    list.insert(list.end(), instanceList.begin(), instanceList.end());
}

/**
 * Returns size of the instance list.
 *
 * @return Size of the instance list.
 */
int InstanceList::size() {
    return list.size();
}

/**
 * Accessor for a single instance with the given index.
 *
 * @param index Index of the instance.
 * @return Instance with index 'index'.
 */
Instance *InstanceList::get(int index) {
    return list.at(index);
}

struct InstanceComparator{
    int attributeIndex;
    /**
     * Constructor for instance comparator.
     *
     * @param attributeIndex Index of the attribute of which two instances will be compared.
     */
    InstanceComparator(int attributeIndex) {
        this->attributeIndex = attributeIndex;
    }
    /**
    * Compares two instance on the values of the attribute with index attributeIndex.
    *
    * @param instance1 First instance to be compared
    * @param instance2 Second instance to be compared
    * @return -1 if the attribute value of the first instance is less than the attribute value of the second instance.
    * 1 if the attribute value of the first instance is greater than the attribute value of the second instance.
    * 0 if the attribute value of the first instance is equal to the attribute value of the second instance.
    */
    bool operator() (Instance* instance1, Instance* instance2){
        return dynamic_cast<ContinuousAttribute*>(instance1->getAttribute(attributeIndex))->getValue() < dynamic_cast<ContinuousAttribute*>(instance2->getAttribute(attributeIndex))->getValue();
    }
};

/**
 * Sorts attribute list according to the attribute with index 'attributeIndex'.
 *
 * @param attributeIndex index of the attribute.
 */
void InstanceList::sort(int attributeIndex) {
    stable_sort(list.begin(), list.end(), InstanceComparator(attributeIndex));
}

/**
 * Compares two {@link Instance} inputs and returns a positive value if the first input's class label is greater
 * than the second's class label input lexicographically.
 *
 * @param o1 First {@link Instance} to be compared.
 * @param o2 Second {@link Instance} to be compared.
 * @return Negative value if the class label of the first instance is less than the class label of the second instance.
 * Positive value if the class label of the first instance is greater than the class label of the second instance.
 * 0 if the class label of the first instance is equal to the class label of the second instance.
 */
struct InstanceClassComparator{
    InstanceClassComparator() {
    }
    bool operator() (Instance* instance1, Instance* instance2){
        string label1 = instance1->getClassLabel();
        string label2 = instance2->getClassLabel();
        return label1.compare(label2) < 0;
    }
};

/**
 * Sorts attributes list.
 */
void InstanceList::sort() {
    stable_sort(list.begin(), list.end(), InstanceClassComparator());
}

/**
 * Shuffles the instance list.
 * @param seed Seed is used for random number generation.
 */
void InstanceList::shuffle(int seed) {
    std::shuffle(list.begin(), list.end(), default_random_engine(seed));
}

/**
 * Creates a bootstrap sample from the current instance list.
 *
 * @param seed To create a different bootstrap sample, we need a new seed for each sample.
 * @return Bootstrap sample.
 */
Bootstrap <Instance*> InstanceList::bootstrap(int seed) {
    return Bootstrap<Instance*>(list, seed);
}

/**
 * Extracts the class labels of each instance in the instance list and returns them in an array of {@link String}.
 *
 * @return A {@link vector} of class labels.
 */
vector<string> InstanceList::getClassLabels() {
    vector<string> classLabels;
    for (Instance* instance : list) {
        classLabels.push_back(instance->getClassLabel());
    }
    return classLabels;
}

/**
 * Extracts the class labels of each instance in the instance list and returns them as a set.
 *
 * @return A {@link vector} of distinct class labels.
 */
vector<string> InstanceList::getDistinctClassLabels() {
    vector<string> classLabels;
    for (Instance* instance : list) {
        if (find(classLabels.begin(), classLabels.end(), instance->getClassLabel()) == classLabels.end()) {
            classLabels.push_back(instance->getClassLabel());
        }
    }
    return classLabels;
}

/**
 * Accessor for the instances.
 *
 * @return Instances.
 */
vector<Instance *> InstanceList::getInstances() {
    return list;
}

/**
 * Extracts the possible class labels of each instance in the instance list and returns them as a set.
 *
 * @return An {@link vector} of distinct class labels.
 */
vector<string> InstanceList::getUnionOfPossibleClassLabels() {
    vector<string> possibleClassLabels;
    for (Instance* instance : list) {
        for (string possibleClassLabel : instance->getPossibleClassLabels()){
            if (find(possibleClassLabels.begin(), possibleClassLabels.end(), possibleClassLabel) == possibleClassLabels.end()) {
                possibleClassLabels.push_back(possibleClassLabel);
            }
        }
    }
    return possibleClassLabels;
}
