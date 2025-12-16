//
// Created by Olcay Taner Yıldız on 2.02.2019.
//

#ifndef CLASSIFICATION_FEATUREFILTER_H
#define CLASSIFICATION_FEATUREFILTER_H


#include "../DataSet/DataSet.h"

class FeatureFilter {
protected:
    DataSet dataSet;
    virtual void convertInstance(Instance* instance) = 0;
    virtual void convertDataDefinition() = 0;
public:
    explicit FeatureFilter(const DataSet& dataSet);
    void convert();
};


#endif //CLASSIFICATION_FEATUREFILTER_H
