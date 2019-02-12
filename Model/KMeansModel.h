//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#ifndef CLASSIFICATION_KMEANSMODELS_H
#define CLASSIFICATION_KMEANSMODELS_H


#include "GaussianModel.h"
#include "../DistanceMetric/DistanceMetric.h"

class KMeansModel : public GaussianModel{
private:
    InstanceList classMeans;
    DistanceMetric* distanceMetric;
public:
    KMeansModel(DiscreteDistribution priorDistribution, InstanceList& classMeans, DistanceMetric* distanceMetric);
protected:
    double calculateMetric(Instance* instance, string Ci) override;
};


#endif //CLASSIFICATION_KMEANSMODELS_H
