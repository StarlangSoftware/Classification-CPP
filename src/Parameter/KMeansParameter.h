//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#ifndef CLASSIFICATION_KMEANSPARAMETER_H
#define CLASSIFICATION_KMEANSPARAMETER_H
#include "Parameter.h"
#include "../DistanceMetric/DistanceMetric.h"

class KMeansParameter : public Parameter {
protected:
    DistanceMetric* distanceMetric;
public:
    explicit KMeansParameter(int seed);
    KMeansParameter(int seed, DistanceMetric* distanceMetric);
    [[nodiscard]] DistanceMetric* getDistanceMetric() const;
};


#endif //CLASSIFICATION_KMEANSPARAMETER_H
