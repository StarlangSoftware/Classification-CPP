//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#ifndef CLASSIFICATION_INSTANCELIST_H
#define CLASSIFICATION_INSTANCELIST_H

#include "Bootstrap.h"
#include "DiscreteDistribution.h"
#include "Matrix.h"
#include "../Instance/Instance.h"
#include "../DataSet/DataDefinition.h"

class InstanceList {
private:
    Attribute* attributeAverage(int index) const;
    Attribute* attributeStandardDeviation(int index) const;
    vector<double> continuousAttributeAverage(int index) const;
    vector<double> continuousAttributeStandardDeviation(int index) const;
protected:
    vector<Instance*> list;
public:
    InstanceList();
    InstanceList(const DataDefinition& definition, const string& separator, const string& fileName);
    explicit InstanceList(ifstream& inputFile);
    explicit InstanceList(const vector<Instance*>& list);
    void add(Instance* instance);
    void addAll(const vector<Instance*>& instanceList);
    int size() const;
    void clear();
    Instance* get(int index) const;
    void sort(int attributeIndex);
    void sort();
    void shuffle(int seed);
    Bootstrap<Instance*> bootstrap(int seed) const;
    vector<string> getClassLabels() const;
    virtual string getClassLabel() const {return "";};
    vector<string> getDistinctClassLabels() const;
    vector<string> getUnionOfPossibleClassLabels() const;
    vector<string> getAttributeValueList(int attributeIndex) const;
    DiscreteDistribution attributeDistribution(int index) const;
    DiscreteDistribution discreteIndexedAttributeClassDistribution(int attributeIndex, int attributeValue) const;
    DiscreteDistribution classDistribution() const;
    vector<DiscreteDistribution> attributeClassDistribution(int attributeIndex) const;
    vector<DiscreteDistribution> allAttributesDistribution() const;
    Instance* average() const;
    Instance* standardDeviation() const;
    vector<double> continuousAttributeAverage() const;
    vector<double> continuousAttributeStandardDeviation() const;
    Matrix covariance(const Vector& average) const;
    vector<Instance*> getInstances() const;
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_INSTANCELIST_H
