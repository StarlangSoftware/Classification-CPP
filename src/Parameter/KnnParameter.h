//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#ifndef CLASSIFICATION_KNNPARAMETER_H
#define CLASSIFICATION_KNNPARAMETER_H
#include "KMeansParameter.h"

class KnnParameter : public KMeansParameter {
private:
    int k;
public:
    KnnParameter(int seed, int k, DistanceMetric* distanceMetric);
    KnnParameter(int seed, int k);
    [[nodiscard]] int getK() const;
};


#endif //CLASSIFICATION_KNNPARAMETER_H
