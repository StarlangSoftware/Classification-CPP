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
    explicit Partition(const InstanceList& list);
    Partition(InstanceList& list, double ratio, int seed, bool stratified);
    Partition(const InstanceList& list, int attributeIndex);
    Partition(const InstanceList& list, int attributeIndex, int attributeValue);
    Partition(const InstanceList& list, int attributeIndex, double splitValue);
    void add(InstanceList* list);
    [[nodiscard]] int size() const;
    [[nodiscard]] InstanceList* get(int index) const;
    [[nodiscard]] vector<Instance*>* getLists() const;
};


#endif //CLASSIFICATION_PARTITION_H
