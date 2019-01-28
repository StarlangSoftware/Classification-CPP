//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#ifndef CLASSIFICATION_INSTANCELIST_H
#define CLASSIFICATION_INSTANCELIST_H

#include <Bootstrap.h>
#include "../Instance/Instance.h"
#include "../DataSet/DataDefinition.h"

class InstanceList {
protected:
    vector<Instance*> list;
public:
    InstanceList();
    InstanceList(DataDefinition definition, string separator, string fileName);
    InstanceList(vector<Instance*> list);
    void add(Instance* instance);
    void addAll(vector<Instance*> instanceList);
    int size();
    Instance* get(int index);
    void sort(int attributeIndex);
    void sort();
    void shuffle(int seed);
    Bootstrap<Instance*> bootstrap(int seed);
    vector<string> getClassLabels();
    vector<string> getDistinctClassLabels();
    vector<string> getUnionOfPossibleClassLabels();
    vector<Instance*> getInstances();
};


#endif //CLASSIFICATION_INSTANCELIST_H
