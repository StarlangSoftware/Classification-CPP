//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#include <fstream>
#include <random>
#include "InstanceList.h"

#include <algorithm>

#include "StringUtils.h"
#include "../Model/Model.h"
#include "../Attribute/DiscreteAttribute.h"
#include "../Attribute/DiscreteIndexedAttribute.h"
#include "../Attribute/BinaryAttribute.h"
#include "../Attribute/ContinuousAttribute.h"

using namespace std;
/**
 * Empty constructor for an instance list. Initializes the instance list with zero instances.
 */
InstanceList::InstanceList() = default;

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
InstanceList::InstanceList(const DataDefinition& definition, const string& separator, const string& fileName) {
    Instance* current;
    string line;
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    getline(inputFile, line);
    while (inputFile.good()) {
        vector<string> attributeList = StringUtils::split(line, separator);
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
                        current->addAttribute(new DiscreteIndexedAttribute(attributeList[i],
                                                                          definition.featureValueIndex(i, attributeList[i]),
                                                                          definition.numberOfValues(i)));
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
InstanceList::InstanceList(const vector<Instance *>& list) {
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
void InstanceList::addAll(const vector<Instance *>& instanceList) {
    list.insert(list.end(), instanceList.begin(), instanceList.end());
}

/**
 * Returns size of the instance list.
 *
 * @return Size of the instance list.
 */
int InstanceList::size() const{
    return list.size();
}

/**
 * Accessor for a single instance with the given index.
 *
 * @param index Index of the instance.
 * @return Instance with index 'index'.
 */
Instance *InstanceList::get(int index) const{
    return list.at(index);
}

struct InstanceComparator{
    int attributeIndex;
    /**
     * Constructor for instance comparator.
     *
     * @param attributeIndex Index of the attribute of which two instances will be compared.
     */
    explicit InstanceComparator(int attributeIndex) {
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
        return ((ContinuousAttribute*)instance1->getAttribute(attributeIndex))->getValue() < ((ContinuousAttribute*)(instance2->getAttribute(attributeIndex)))->getValue();
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
 * Compares two Instance inputs and returns a positive value if the first input's class label is greater
 * than the second's class label input lexicographically.
 *
 * @param o1 First Instance to be compared.
 * @param o2 Second Instance to be compared.
 * @return Negative value if the class label of the first instance is less than the class label of the second instance.
 * Positive value if the class label of the first instance is greater than the class label of the second instance.
 * 0 if the class label of the first instance is equal to the class label of the second instance.
 */
struct InstanceClassComparator{
    InstanceClassComparator() = default;

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
Bootstrap <Instance*> InstanceList::bootstrap(int seed) const{
    return Bootstrap<Instance*>(list, seed);
}

/**
 * Extracts the class labels of each instance in the instance list and returns them in an array of String.
 *
 * @return A vector of class labels.
 */
vector<string> InstanceList::getClassLabels() const{
    vector<string> classLabels;
    classLabels.reserve(list.size());
    for (Instance* instance : list) {
        classLabels.push_back(instance->getClassLabel());
    }
    return classLabels;
}

/**
 * Extracts the class labels of each instance in the instance list and returns them as a set.
 *
 * @return A vector of distinct class labels.
 */
vector<string> InstanceList::getDistinctClassLabels() const{
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
vector<Instance *> InstanceList::getInstances() const{
    return list;
}

/**
 * Extracts the possible class labels of each instance in the instance list and returns them as a set.
 *
 * @return An vector of distinct class labels.
 */
vector<string> InstanceList::getUnionOfPossibleClassLabels() const{
    vector<string> possibleClassLabels;
    for (Instance* instance : list) {
        for (const string& possibleClassLabel : instance->getPossibleClassLabels()){
            if (find(possibleClassLabels.begin(), possibleClassLabels.end(), possibleClassLabel) == possibleClassLabels.end()) {
                possibleClassLabels.push_back(possibleClassLabel);
            }
        }
    }
    return possibleClassLabels;
}

/**
 * Extracts distinct discrete values of a given attribute as an array of strings.
 *
 * @param attributeIndex Index of the discrete attribute.
 * @return An array of distinct values of a discrete attribute.
 */
vector<string> InstanceList::getAttributeValueList(int attributeIndex) const{
    vector<string> valueList;
    for (Instance* instance : list) {
        string attributeValue = ((DiscreteAttribute*)(instance->getAttribute(attributeIndex)))->getValue();
        if (find(valueList.begin(), valueList.end(), attributeValue) == valueList.end()) {
            valueList.push_back(attributeValue);
        }
    }
    return valueList;
}

/**
 * Calculates the mean of a single attribute for this instance list (m_i). If the attribute is discrete, the maximum
 * occurring value for that attribute is returned. If the attribute is continuous, the mean value of the values of
 * all instances are returned.
 *
 * @param index Index of the attribute.
 * @return The mean value of the instances as an attribute.
 */
Attribute *InstanceList::attributeAverage(int index) const{
    if (list.at(0)->getAttribute(index)->isDiscrete()) {
        vector<string> values;
        values.reserve(list.size());
        for (Instance* instance : list) {
            values.push_back(((DiscreteAttribute*)(instance->getAttribute(index)))->getValue());
        }
        return new DiscreteAttribute(Model::getMaximum(values));
    } else {
        if (list.at(0)->getAttribute(index)->isContinuous()) {
            double sum = 0.0;
            for (Instance* instance : list) {
                sum += ((ContinuousAttribute*)(instance->getAttribute(index)))->getValue();
            }
            return new ContinuousAttribute(sum / list.size());
        } else {
            return nullptr;
        }
    }
}

/**
 * Calculates the mean of a single attribute for this instance list (m_i).
 *
 * @param index Index of the attribute.
 * @return The mean value of the instances as an attribute.
 */
vector<double> InstanceList::continuousAttributeAverage(int index) const{
    if (list.at(0)->getAttribute(index)->isDiscreteIndexed()) {
        int maxIndexSize = ((DiscreteIndexedAttribute*)(list.at(0)->getAttribute(index)))->getMaxIndex();
        vector<double> values(maxIndexSize, 0.0);
        for (Instance* instance : list) {
            int valueIndex = ((DiscreteIndexedAttribute*)(instance->getAttribute(index)))->getIndex();
            values[valueIndex]++;
        }
        for (double &value : values) {
            value /= list.size();
        }
        return values;
    } else {
        if (list.at(0)->getAttribute(index)->isContinuous()) {
            double sum = 0.0;
            for (Instance* instance : list) {
                sum += ((ContinuousAttribute*)(instance->getAttribute(index)))->getValue();
            }
            vector<double> values;
            values.push_back(sum / list.size());
            return values;
        }
    }
}

/**
 * Calculates the standard deviation of a single attribute for this instance list (m_i). If the attribute is discrete,
 * null returned. If the attribute is continuous, the standard deviation  of the values all instances are returned.
 *
 * @param index Index of the attribute.
 * @return The standard deviation of the instances as an attribute.
 */
Attribute *InstanceList::attributeStandardDeviation(int index) const{
    if (list.at(0)->getAttribute(index)->isContinuous()) {
        double average, sum = 0.0;
        for (Instance* instance : list) {
            sum += ((ContinuousAttribute*)(instance->getAttribute(index)))->getValue();
        }
        average = sum / list.size();
        sum = 0.0;
        for (Instance* instance : list) {
            sum += pow(((ContinuousAttribute*)(instance->getAttribute(index)))->getValue() - average, 2);
        }
        return new ContinuousAttribute(sqrt(sum / (list.size() - 1)));
    } else {
        return nullptr;
    }
}

/**
 * Calculates the standard deviation of a single continuous attribute for this instance list (m_i).
 *
 * @param index Index of the attribute.
 * @return The standard deviation of the instances as an attribute.
 */
vector<double> InstanceList::continuousAttributeStandardDeviation(int index) const{
    if (list.at(0)->getAttribute(index)->isDiscreteIndexed()) {
        int maxIndexSize = ((DiscreteIndexedAttribute*)(list.at(0)->getAttribute(index)))->getMaxIndex();
        vector<double> averages(maxIndexSize, 0.0);
        for (Instance* instance : list) {
            int valueIndex = ((DiscreteIndexedAttribute*)(instance->getAttribute(index)))->getIndex();
            averages[valueIndex]++;
        }
        for (double &average : averages) {
            average /= list.size();
        }
        vector<double> values(maxIndexSize, 0.0);
        for (Instance* instance : list) {
            int valueIndex = ((DiscreteIndexedAttribute*)(instance->getAttribute(index)))->getIndex();
            for (int i = 0; i < maxIndexSize; i++) {
                if (i == valueIndex) {
                    values[i] += pow(1 - averages.at(i), 2);
                } else {
                    values[i] += pow(averages.at(i), 2);
                }
            }
        }
        for (double &value : values) {
            value = sqrt(value / (list.size() - 1));
        }
        return values;
    } else {
        if (list.at(0)->getAttribute(index)->isContinuous()) {
            double average, sum = 0.0;
            for (Instance* instance : list) {
                sum += ((ContinuousAttribute*)(instance->getAttribute(index)))->getValue();
            }
            average = sum / list.size();
            sum = 0.0;
            for (Instance* instance : list) {
                sum += pow(((ContinuousAttribute*)(instance->getAttribute(index)))->getValue() - average, 2);
            }
            vector<double> result;
            result.push_back(sqrt(sum / (list.size() - 1)));
            return result;
        }
    }
}

/**
 * The attributeDistribution method takes an index as an input and if the attribute of the instance at given index is
 * discrete, it returns the distribution of the attributes of that instance.
 *
 * @param index Index of the attribute.
 * @return Distribution of the attribute.
 */
DiscreteDistribution InstanceList::attributeDistribution(int index) const{
    DiscreteDistribution distribution = DiscreteDistribution();
    if (list.at(0)->getAttribute(index)->isDiscrete()) {
        for (Instance* instance : list) {
            distribution.addItem(((DiscreteAttribute*)(instance->getAttribute(index)))->getValue());
        }
    }
    return distribution;
}

/**
 * The attributeClassDistribution method takes an attribute index as an input. It loops through the instances, gets
 * the corresponding value of given attribute index and adds the class label of that instance to the discrete distributions list.
 *
 * @param attributeIndex Index of the attribute.
 * @return Distribution of the class labels.
 */
vector<DiscreteDistribution> InstanceList::attributeClassDistribution(int attributeIndex) const{
    vector<string> valueList = getAttributeValueList(attributeIndex);
    vector<DiscreteDistribution> distributions(valueList.size(), DiscreteDistribution());
    for (Instance* instance : list) {
        string value = ((DiscreteAttribute*)(instance->getAttribute(attributeIndex)))->getValue();
        distributions[find(valueList.begin(), valueList.end(), value) - valueList.begin()].addItem(instance->getClassLabel());
    }
    return distributions;
}

/**
 * The discreteIndexedAttributeClassDistribution method takes an attribute index and an attribute value as inputs.
 * It loops through the instances, gets the corresponding value of given attribute index and given attribute value.
 * Then, adds the class label of that instance to the discrete indexed distributions list.
 *
 * @param attributeIndex Index of the attribute.
 * @param attributeValue Value of the attribute.
 * @return Distribution of the class labels.
 */
DiscreteDistribution InstanceList::discreteIndexedAttributeClassDistribution(int attributeIndex, int attributeValue) const{
    DiscreteDistribution distribution;
    for (Instance* instance : list) {
        if (((DiscreteIndexedAttribute*)(instance->getAttribute(attributeIndex)))->getIndex() == attributeValue) {
            distribution.addItem(instance->getClassLabel());
        }
    }
    return distribution;
}

/**
 * The classDistribution method returns the distribution of all the class labels of instances.
 *
 * @return Distribution of the class labels.
 */
DiscreteDistribution InstanceList::classDistribution() const{
    DiscreteDistribution distribution;
    for (Instance* instance : list) {
        distribution.addItem(instance->getClassLabel());
    }
    return distribution;
}

/**
 * The allAttributesDistribution method returns the distributions of all the attributes of instances.
 *
 * @return Distributions of all the attributes of instances.
 */
vector<DiscreteDistribution> InstanceList::allAttributesDistribution() const{
    vector<DiscreteDistribution> distributions;
    distributions.reserve(list.at(0)->attributeSize());
    for (int i = 0; i < list.at(0)->attributeSize(); i++) {
        distributions.push_back(attributeDistribution(i));
    }
    return distributions;
}

/**
 * Returns the mean of all the attributes for instances in the list.
 *
 * @return Mean of all the attributes for instances in the list.
 */
Instance *InstanceList::average() const{
    auto* result = new Instance(list.at(0)->getClassLabel());
    for (int i = 0; i < list.at(0)->attributeSize(); i++) {
        result->addAttribute(attributeAverage(i));
    }
    return result;
}

/**
 * Calculates mean of the attributes of instances.
 *
 * @return Mean of the attributes of instances.
 */
vector<double> InstanceList::continuousAttributeAverage() const{
    vector<double> result;
    for (int i = 0; i < list.at(0)->attributeSize(); i++) {
        vector<double> added = continuousAttributeAverage(i);
        result.insert(result.end(), added.begin(), added.end());
    }
    return result;
}

/**
 * Returns the standard deviation of attributes for instances.
 *
 * @return Standard deviation of attributes for instances.
 */
Instance *InstanceList::standardDeviation() const{
    auto* result = new Instance(list.at(0)->getClassLabel());
    for (int i = 0; i < list.at(0)->attributeSize(); i++) {
        result->addAttribute(attributeStandardDeviation(i));
    }
    return result;
}

/**
 * Returns the standard deviation of continuous attributes for instances.
 *
 * @return Standard deviation of continuous attributes for instances.
 */
vector<double> InstanceList::continuousAttributeStandardDeviation() const{
    vector<double> result;
    for (int i = 0; i < list.at(0)->attributeSize(); i++) {
        vector<double> added = continuousAttributeStandardDeviation(i);
        result.insert(result.end(), added.begin(), added.end());
    }
    return result;
}

/**
 * Calculates a covariance Matrix by using an average Vector.
 *
 * @param average Vector input.
 * @return Covariance Matrix.
 */
Matrix InstanceList::covariance(const Vector& average) const{
    double mi, mj, xi, xj;
    Matrix result = Matrix(list.at(0)->continuousAttributeSize(), list.at(0)->continuousAttributeSize());
    for (Instance* instance : list) {
        vector<double> continuousAttributes = instance->continuousAttributes();
        for (int i = 0; i < instance->continuousAttributeSize(); i++) {
            xi = continuousAttributes.at(i);
            mi = average.getValue(i);
            for (int j = 0; j < instance->continuousAttributeSize(); j++) {
                xj = continuousAttributes.at(j);
                mj = average.getValue(j);
                result.addValue(i, j, (xi - mi) * (xj - mj));
            }
        }
    }
    result.divideByConstant(list.size() - 1);
    return result;
}

/**
 * Prints an instance list to an output file
 * @param outputFile Output file
 */
void InstanceList::serialize(ostream &outputFile) {
    Instance* firstInstance = list.at(0);
    outputFile << firstInstance->attributeSize() << "\n";
    for (int i = 0; i < firstInstance->attributeSize(); i++){
        if (firstInstance->getAttribute(i)->isDiscrete()){
            outputFile << "Discrete ";
        } else {
            if (firstInstance->getAttribute(i)->isContinuous()){
                outputFile << "Continuous ";
            } else {
                if (firstInstance->getAttribute(i)->isBinary()){
                    outputFile << "Binary ";
                }
            }
        }
    }
    outputFile << "\n";
    outputFile << list.size() << "\n";
    for (Instance* instance : list){
        instance->serialize(outputFile);
    }
}

/**
 * Reads an instance list from an input file
 * @param inputFile Input file
 */
InstanceList::InstanceList(ifstream &inputFile) {
    int size;
    string line, discreteAttribute;
    vector<string> attributeTypes, attributeValues;
    Instance* current;
    inputFile.ignore();
    getline(inputFile, line);
    attributeTypes = StringUtils::split(line);
    inputFile >> size;
    inputFile.ignore();
    for (int i = 0; i < size; i++){
        vector<Attribute*> attributeList;
        getline(inputFile, line);
        attributeValues = StringUtils::split(line, ",");
        for (int j = 0; j < attributeTypes.size(); j++) {
            if (attributeTypes[j] == "DISCRETE"){
                attributeList.push_back(new DiscreteAttribute(attributeValues[j]));
            } else {
                if (attributeTypes[j] == "CONTINUOUS"){
                    attributeList.push_back(new ContinuousAttribute(stof(attributeValues[j])));
                }
            }
        }
        current = new Instance(attributeValues[attributeTypes.size()], attributeList);
        list.push_back(current);
    }
}

/**
 * Removes the instances in the instance list.
 */
void InstanceList::clear() {
    list.clear();
}
