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
    [[nodiscard]] int sampleSize() const;
    [[nodiscard]] int classCount() const;
    [[nodiscard]] int attributeCount() const;
    [[nodiscard]] int discreteAttributeCount() const;
    [[nodiscard]] int continuousAttributeCount() const;
    [[nodiscard]] string getClasses() const;
    [[nodiscard]] string info(const string& dataSetName) const;
    [[nodiscard]] string to_string(const string& dataSetName) const;
    void addInstance(Instance* current);
    void addInstanceList(const vector<Instance*>& instanceList);
    [[nodiscard]] vector<Instance*> getInstances() const;
    [[nodiscard]] Partition getClassInstances() const;
    [[nodiscard]] InstanceList getInstanceList() const;
    [[nodiscard]] DataDefinition getDataDefinition() const;
    void writeToFile(const string& outFileName);
};


#endif //CLASSIFICATION_DATASET_H
