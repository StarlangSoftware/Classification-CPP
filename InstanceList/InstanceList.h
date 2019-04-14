//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#ifndef CLASSIFICATION_INSTANCELIST_H
#define CLASSIFICATION_INSTANCELIST_H

#include <Bootstrap.h>
#include <DiscreteDistribution.h>
#include <Matrix.h>
#include "../Instance/Instance.h"
#include "../DataSet/DataDefinition.h"

class InstanceList {
private:
    Attribute* attributeAverage(int index);
    Attribute* attributeStandardDeviation(int index);
    vector<double> continuousAttributeAverage(int index);
    vector<double> continuousAttributeStandardDeviation(int index);
protected:
    vector<Instance*> list;
public:
    InstanceList();
    InstanceList(DataDefinition definition, string separator, string fileName);
    explicit InstanceList(ifstream& inputFile);
    explicit InstanceList(vector<Instance*> list);
    void add(Instance* instance);
    void addAll(vector<Instance*> instanceList);
    int size();
    Instance* get(int index);
    void sort(int attributeIndex);
    void sort();
    void shuffle(int seed);
    Bootstrap<Instance*> bootstrap(int seed);
    vector<string> getClassLabels();
    virtual string getClassLabel() {return "";};
    vector<string> getDistinctClassLabels();
    vector<string> getUnionOfPossibleClassLabels();
    vector<string> getAttributeValueList(int attributeIndex);
    DiscreteDistribution attributeDistribution(int index);
    DiscreteDistribution discreteIndexedAttributeClassDistribution(int attributeIndex, int attributeValue);
    DiscreteDistribution classDistribution();
    vector<DiscreteDistribution> attributeClassDistribution(int attributeIndex);
    vector<DiscreteDistribution> allAttributesDistribution();
    Instance* average();
    Instance* standardDeviation();
    vector<double> continuousAttributeAverage();
    vector<double> continuousAttributeStandardDeviation();
    Matrix covariance(Vector average);
    vector<Instance*> getInstances();
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_INSTANCELIST_H
