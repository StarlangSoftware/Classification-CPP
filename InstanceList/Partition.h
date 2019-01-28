//
// Created by Olcay Taner Yıldız on 27.01.2019.
//

#ifndef CLASSIFICATION_PARTITION_H
#define CLASSIFICATION_PARTITION_H
#include "InstanceList.h"

class Partition {
private:
    vector<InstanceList*> multiList;
public:
    Partition();
    void add(InstanceList* list);
    int size();
    InstanceList* get(int index);
    vector<Instance*>* getLists();
};


#endif //CLASSIFICATION_PARTITION_H
