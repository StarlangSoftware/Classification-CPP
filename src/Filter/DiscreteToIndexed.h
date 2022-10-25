//
// Created by Olcay Taner Yıldız on 4.02.2019.
//

#ifndef CLASSIFICATION_DISCRETETOINDEXED_H
#define CLASSIFICATION_DISCRETETOINDEXED_H


#include "LaryFilter.h"

class DiscreteToIndexed : public LaryFilter{
public:
    DiscreteToIndexed(const DataSet& dataSet);
protected:
    void convertInstance(Instance* instance) override;
    void convertDataDefinition() override;
};


#endif //CLASSIFICATION_DISCRETETOINDEXED_H
