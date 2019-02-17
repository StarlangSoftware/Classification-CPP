//
// Created by Olcay Taner Yıldız on 4.02.2019.
//

#ifndef CLASSIFICATION_NORMALIZE_H
#define CLASSIFICATION_NORMALIZE_H


#include "FeatureFilter.h"

class Normalize : public FeatureFilter {
private:
    Instance* averageInstance;
    Instance* standardDeviationInstance;
public:
    explicit Normalize(DataSet& dataSet);
protected:
    void convertInstance(Instance* instance) override;
    void convertDataDefinition() override;
};


#endif //CLASSIFICATION_NORMALIZE_H
