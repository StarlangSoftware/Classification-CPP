//
// Created by Olcay Taner Yıldız on 2.02.2019.
//

#ifndef CLASSIFICATION_LARYFILTER_H
#define CLASSIFICATION_LARYFILTER_H


#include "FeatureFilter.h"

class LaryFilter : public FeatureFilter{
protected:
    vector<DiscreteDistribution> attributeDistributions;
    void removeDiscreteAttributes(Instance* instance, int size);
    void removeDiscreteAttributes(int size);
public:
    LaryFilter(DataSet& dataSet);
};


#endif //CLASSIFICATION_LARYFILTER_H
