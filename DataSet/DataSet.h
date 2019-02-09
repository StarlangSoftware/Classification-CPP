//
// Created by olcay on 29.01.2019.
//

#ifndef CLASSIFICATION_DATASET_H
#define CLASSIFICATION_DATASET_H


#include "../InstanceList/InstanceList.h"
#include "../InstanceList/Partition.h"

class DataSet {
private:
    InstanceList instances;
    DataDefinition definition;
public:
    DataSet();
    DataSet(DataDefinition& definition);
    DataSet(ifstream file);
    DataSet(DataDefinition definition, string separator, string fileName);
    bool checkDefinition(Instance* instance);
    void setDefinition(Instance* instance);
    int sampleSize();
    int classCount();
    int attributeCount();
    int discreteAttributeCount();
    int continuousAttributeCount();
    string getClasses();
    string info(string dataSetName);
    string to_string(string dataSetName);
    void addInstance(Instance* current);
    void addInstanceList(vector<Instance*> instanceList);
    vector<Instance*> getInstances();
    Partition getClassInstances();
    InstanceList getInstanceList();
    DataDefinition getDataDefinition();
    void writeToFile(string outFileName);
};


#endif //CLASSIFICATION_DATASET_H
