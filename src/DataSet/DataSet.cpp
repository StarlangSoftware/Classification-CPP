//
// Created by olcay on 29.01.2019.
//

#include <fstream>
#include "DataSet.h"
#include "Dictionary/Word.h"
#include "../Instance/CompositeInstance.h"
#include "../Attribute/ContinuousAttribute.h"
#include "../Attribute/DiscreteAttribute.h"

/**
 * Constructor for generating a new {@link DataSet}.
 */
DataSet::DataSet() {
    instances = InstanceList();
}

/**
 * Constructor for generating a new {@link DataSet} with given {@link DataDefinition}.
 *
 * @param definition Data definition of the data set.
 */
DataSet::DataSet(const DataDefinition& definition) {
    this->definition = definition;
    instances = InstanceList();
}

/**
 * Constructor for generating a new {@link DataSet} from given {@link ifstream}.
 *
 * @param file {@link ifstream} to generate {@link DataSet} from.
 */
DataSet::DataSet(ifstream& file) {
    Instance* instance;
    int i = 0;
    string instanceText;
    instances = InstanceList();
    definition = DataDefinition();
    while (file.good()){
        getline(file, instanceText);
        vector<string> attributes = Word::split(instanceText, ",");
        if (i == 0) {
            for (int j = 0; j < attributes.size() - 1; j++) {
                try {
                    stod(attributes[j]);
                    definition.addAttribute(AttributeType::CONTINUOUS);
                } catch (invalid_argument& e) {
                    definition.addAttribute(AttributeType::DISCRETE);
                }
            }
        } else {
            if (attributes.size() != definition.attributeCount() + 1) {
                continue;
            }
        }
        string classLabel = attributes[attributes.size() - 1];
        if (classLabel.find_first_of(';') == string::npos) {
            instance = new Instance(classLabel);
        } else {
            vector<string> labels = Word::split(classLabel, ";");
            instance = new CompositeInstance(labels);
        }
        for (int j = 0; j < attributes.size() - 1; j++) {
            switch (definition.getAttributeType(j)) {
                case AttributeType::CONTINUOUS:
                    try {
                        instance->addAttribute(new ContinuousAttribute(stod(attributes[j])));
                    } catch (invalid_argument& e) {
                    }
                    break;
                case AttributeType::DISCRETE:
                    instance->addAttribute(new DiscreteAttribute(attributes[j]));
                    break;
                case AttributeType::BINARY:
                case AttributeType::DISCRETE_INDEXED:
                    break;
            }
        }
        if (instance->attributeSize() == definition.attributeCount()) {
            instances.add(instance);
        }
        i++;
    }
    file.close();
}

/**
 * Constructor for generating a new {@link DataSet} with a {@link DataDefinition}, from a {@link File} by using a separator.
 *
 * @param definition Data definition of the data set.
 * @param separator  Separator character which separates the attribute values in the data file.
 * @param fileName   Name of the data set file.
 */
DataSet::DataSet(const DataDefinition& definition, const string& separator, const string& fileName) {
    this->definition = definition;
    instances = InstanceList(definition, separator, fileName);
}

/**
 * Checks the correctness of the attribute type, for instance, if the attribute of given instance is a Binary attribute,
 * and the attribute type of the corresponding item of the data definition is also a Binary attribute, it then
 * returns true, and false otherwise.
 *
 * @param instance {@link Instance} to checks the attribute type.
 * @return true if attribute types of given {@link Instance} and data definition matches.
 */
bool DataSet::checkDefinition(Instance *instance) const{
    for (int i = 0; i < instance->attributeSize(); i++) {
        if (instance->getAttribute(i)->isBinary()) {
            if (definition.getAttributeType(i) != AttributeType::BINARY)
                return false;
        } else {
            if (instance->getAttribute(i)->isDiscreteIndexed()) {
                if (definition.getAttributeType(i) != AttributeType::DISCRETE_INDEXED)
                    return false;
            } else {
                if (instance->getAttribute(i)->isDiscrete()) {
                    if (definition.getAttributeType(i) != AttributeType::DISCRETE)
                        return false;
                } else {
                    if (instance->getAttribute(i)->isContinuous()) {
                        if (definition.getAttributeType(i) != AttributeType::CONTINUOUS)
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

/**
 * Adds the attribute types according to given {@link Instance}. For instance, if the attribute type of given {@link Instance}
 * is a Discrete type, it than adds a discrete attribute type to the list of attribute types.
 *
 * @param instance {@link Instance} input.
 */
void DataSet::setDefinition(Instance *instance) {
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(instance->attributeSize());
    for (int i = 0; i < instance->attributeSize(); i++) {
        if (instance->getAttribute(i)->isBinary()) {
            attributeTypes.push_back(AttributeType::BINARY);
        } else {
            if (instance->getAttribute(i)->isDiscreteIndexed()) {
                attributeTypes.push_back(AttributeType::DISCRETE_INDEXED);
            } else {
                if (instance->getAttribute(i)->isDiscrete()) {
                    attributeTypes.push_back(AttributeType::DISCRETE);
                } else {
                    if (instance->getAttribute(i)->isContinuous()) {
                        attributeTypes.push_back(AttributeType::CONTINUOUS);
                    }
                }
            }
        }
    }
    definition = DataDefinition(attributeTypes);
}

/**
 * Returns the size of the {@link InstanceList}.
 *
 * @return Size of the {@link InstanceList}.
 */
int DataSet::sampleSize() const{
    return instances.size();
}

/**
 * Returns the size of the class label distribution of {@link InstanceList}.
 *
 * @return Size of the class label distribution of {@link InstanceList}.
 */
int DataSet::classCount() const{
    return instances.classDistribution().size();
}

/**
 * Returns the number of attribute types at {@link DataDefinition} list.
 *
 * @return The number of attribute types at {@link DataDefinition} list.
 */
int DataSet::attributeCount() const{
    return definition.attributeCount();
}

/**
 * Returns the number of discrete attribute types at {@link DataDefinition} list.
 *
 * @return The number of discrete attribute types at {@link DataDefinition} list.
 */
int DataSet::discreteAttributeCount() const{
    return definition.discreteAttributeCount();
}

/**
 * Returns the number of continuous attribute types at {@link DataDefinition} list.
 *
 * @return The number of continuous attribute types at {@link DataDefinition} list.
 */
int DataSet::continuousAttributeCount() const{
    return definition.continuousAttributeCount();
}

/**
 * Returns the accumulated {@link String} of class labels of the {@link InstanceList}.
 *
 * @return The accumulated {@link String} of class labels of the {@link InstanceList}.
 */
string DataSet::getClasses() const{
    string result;
    vector<string> classLabels = instances.getDistinctClassLabels();
    result = classLabels.at(0);
    for (int i = 1; i < classLabels.size(); i++) {
        result += ";" + classLabels.at(i);
    }
    return result;
}

/**
 * Returns the general information about the given data set such as the number of instances, distinct class labels,
 * attributes, discrete and continuous attributes.
 *
 * @param dataSetName Data set name.
 * @return General information about the given data set.
 */
string DataSet::info(const string& dataSetName) const{
    string result = "DATASET: " + dataSetName + "\n";
    result = result + "Number of instances: " + std::to_string(sampleSize()) + "\n";
    result = result + "Number of distinct class labels: " + std::to_string(classCount()) + "\n";
    result = result + "Number of attributes: " + std::to_string(attributeCount()) + "\n";
    result = result + "Number of discrete attributes: " + std::to_string(discreteAttributeCount()) + "\n";
    result = result + "Number of continuous attributes: " + std::to_string(continuousAttributeCount()) + "\n";
    result = result + "Class labels: " + getClasses();
    return result;
}

/**
 * Returns a formatted String of general information about the data set.
 *
 * @param dataSetName Data set name.
 * @return Formatted String of general information about the data set.
 */
string DataSet::to_string(const string& dataSetName) const{
    return dataSetName + std::to_string(sampleSize()) + std::to_string(classCount()) + std::to_string(attributeCount()) + std::to_string(discreteAttributeCount()) + std::to_string(continuousAttributeCount());
}

/**
 * Adds a new instance to the {@link InstanceList}.
 *
 * @param current {@link Instance} to add.
 */
void DataSet::addInstance(Instance *current) {
    if (definition.attributeCount() == 0) {
        setDefinition(current);
        instances.add(current);
    } else {
        if (checkDefinition(current)) {
            instances.add(current);
        }
    }
}

/**
 * Adds all the instances of given instance list to the {@link InstanceList}.
 *
 * @param instanceList {@link InstanceList} to add instances from.
 */
void DataSet::addInstanceList(const vector<Instance *>& instanceList) {
    for (Instance* instance : instanceList) {
        addInstance(instance);
    }
}

/**
 * Returns the instances of {@link InstanceList}.
 *
 * @return The instances of {@link InstanceList}.
 */
vector<Instance *> DataSet::getInstances() const{
    return instances.getInstances();
}

/**
 * Returns instances of the items at the list of instance lists from the partitions.
 *
 * @return Instances of the items at the list of instance lists from the partitions.
 */
Partition DataSet::getClassInstances() const{
    return Partition(instances);
}

/**
 * Accessor for the {@link InstanceList}.
 *
 * @return The {@link InstanceList}.
 */
InstanceList DataSet::getInstanceList() const{
    return instances;
}

/**
 * Accessor for the data definition.
 *
 * @return The data definition.
 */
DataDefinition DataSet::getDataDefinition() const{
    return definition;
}

/**
 * Print out the instances of {@link InstanceList} as a {@link String}.
 *
 * @param outFileName File name to write the output.
 */
void DataSet::writeToFile(const string& outFileName) {
    ofstream outfile;
    outfile = ofstream(outFileName, ofstream::out);
    for (int i = 0; i < instances.size(); i++) {
        outfile << instances.get(i)->to_string() << "\n";
    }
    outfile.close();
}

/**
 * Return a subset generated via the given {@link FeatureSubSet}.
 *
 * @param featureSubSet {@link FeatureSubSet} input.
 * @return Subset generated via the given {@link FeatureSubSet}.
 */
DataSet DataSet::getSubSetOfFeatures(const FeatureSubSet& featureSubSet) {
    DataDefinition dataDefinition = definition.getSubSetOfFeatures(featureSubSet);
    DataSet result = DataSet(dataDefinition);
    for (int i = 0; i < instances.size(); i++) {
        result.addInstance(instances.get(i)->getSubSetOfFeatures(featureSubSet));
    }
    return result;
}
