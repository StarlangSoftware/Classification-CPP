//
// Created by olcay on 29.01.2019.
//

#ifndef CLASSIFICATION_DATASET_H
#define CLASSIFICATION_DATASET_H


#include "../InstanceList/InstanceList.h"
#include "../InstanceList/Partition.h"
#include "../FeatureSelection/FeatureSubSet.h"

class DataSet {
private:
    InstanceList instances;
    DataDefinition definition;
public:
    DataSet();
    explicit DataSet(const DataDefinition& definition);
    explicit DataSet(ifstream& file);
    DataSet(const DataDefinition& definition, const string& separator, const string& fileName);
    DataSet getSubSetOfFeatures(const FeatureSubSet& featureSubSet);
    bool checkDefinition(Instance* instance) const;
    void setDefinition(Instance* instance);
    int sampleSize() const;
    int classCount() const;
    int attributeCount() const;
    int discreteAttributeCount() const;
    int continuousAttributeCount() const;
    string getClasses() const;
    string info(const string& dataSetName) const;
    string to_string(const string& dataSetName) const;
    void addInstance(Instance* current);
    void addInstanceList(const vector<Instance*>& instanceList);
    vector<Instance*> getInstances() const;
    Partition getClassInstances() const;
    InstanceList getInstanceList() const;
    DataDefinition getDataDefinition() const;
    void writeToFile(const string& outFileName);
};


#endif //CLASSIFICATION_DATASET_H
