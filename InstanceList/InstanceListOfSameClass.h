//
// Created by olcay on 28.01.2019.
//

#ifndef CLASSIFICATION_INSTANCELISTOFSAMECLASS_H
#define CLASSIFICATION_INSTANCELISTOFSAMECLASS_H


#include "InstanceList.h"

class InstanceListOfSameClass : public InstanceList {
private:
    string classLabel;
public:
    explicit InstanceListOfSameClass(string classLabel);
    string getClassLabel() override;
};


#endif //CLASSIFICATION_INSTANCELISTOFSAMECLASS_H
