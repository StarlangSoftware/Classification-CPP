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
    [[nodiscard]] Attribute* attributeAverage(int index) const;
    [[nodiscard]] Attribute* attributeStandardDeviation(int index) const;
    [[nodiscard]] vector<double> continuousAttributeAverage(int index) const;
    [[nodiscard]] vector<double> continuousAttributeStandardDeviation(int index) const;
protected:
    vector<Instance*> list;
public:
    InstanceList();
    InstanceList(const DataDefinition& definition, const string& separator, const string& fileName);
    explicit InstanceList(ifstream& inputFile);
    explicit InstanceList(const vector<Instance*>& list);
    void add(Instance* instance);
    void addAll(const vector<Instance*>& instanceList);
    [[nodiscard]] int size() const;
    void clear();
    [[nodiscard]] Instance* get(int index) const;
    void sort(int attributeIndex);
    void sort();
    void shuffle(int seed);
    [[nodiscard]] Bootstrap<Instance*> bootstrap(int seed) const;
    [[nodiscard]] vector<string> getClassLabels() const;
    [[nodiscard]] virtual string getClassLabel() const {return "";};
    [[nodiscard]] vector<string> getDistinctClassLabels() const;
    [[nodiscard]] vector<string> getUnionOfPossibleClassLabels() const;
    [[nodiscard]] vector<string> getAttributeValueList(int attributeIndex) const;
    [[nodiscard]] DiscreteDistribution attributeDistribution(int index) const;
    [[nodiscard]] DiscreteDistribution discreteIndexedAttributeClassDistribution(int attributeIndex, int attributeValue) const;
    [[nodiscard]] DiscreteDistribution classDistribution() const;
    [[nodiscard]] vector<DiscreteDistribution> attributeClassDistribution(int attributeIndex) const;
    [[nodiscard]] vector<DiscreteDistribution> allAttributesDistribution() const;
    [[nodiscard]] Instance* average() const;
    [[nodiscard]] Instance* standardDeviation() const;
    [[nodiscard]] vector<double> continuousAttributeAverage() const;
    [[nodiscard]] vector<double> continuousAttributeStandardDeviation() const;
    [[nodiscard]] Matrix covariance(const Vector& average) const;
    [[nodiscard]] vector<Instance*> getInstances() const;
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_INSTANCELIST_H
