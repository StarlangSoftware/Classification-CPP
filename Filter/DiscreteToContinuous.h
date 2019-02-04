//
// Created by Olcay Taner Yıldız on 2.02.2019.
//

#ifndef CLASSIFICATION_DISCRETETOCONTINUOUS_H
#define CLASSIFICATION_DISCRETETOCONTINUOUS_H


#include "LaryFilter.h"

class DiscreteToContinuous : LaryFilter {
public:
    DiscreteToContinuous(DataSet& dataSet);
protected:
    virtual void convertInstance(Instance* instance) override;
    virtual void convertDataDefinition() override;
};


#endif //CLASSIFICATION_DISCRETETOCONTINUOUS_H
