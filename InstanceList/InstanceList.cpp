#include <utility>

//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#include <fstream>
#include "InstanceList.h"
#include "../Attribute/DiscreteAttribute.h"
#include "../Attribute/BinaryAttribute.h"
#include "../Attribute/ContinuousAttribute.h"

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
