//
// Created by Olcay Taner Yıldız on 2.02.2019.
//

#ifndef CLASSIFICATION_TRAINEDFEATUREFILTER_H
#define CLASSIFICATION_TRAINEDFEATUREFILTER_H


#include "FeatureFilter.h"

class TrainedFeatureFilter : public FeatureFilter{
protected:
    virtual void train() = 0;
public:
    explicit TrainedFeatureFilter(const DataSet& dataSet);
};


#endif //CLASSIFICATION_TRAINEDFEATUREFILTER_H
