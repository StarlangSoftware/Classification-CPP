//
// Created by Olcay Taner Yıldız on 29.01.2019.
//

#ifndef CLASSIFICATION_MAHALANOBISDISTANCE_H
#define CLASSIFICATION_MAHALANOBISDISTANCE_H
#include <Matrix.h>
#include "DistanceMetric.h"

class MahalanobisDistance : DistanceMetric {
private:
    Matrix covarianceInverse = Matrix(0, 0);
public:
    MahalanobisDistance(Matrix covarianceInverse);
    double distance(Instance* instance1, Instance* instance2);
};


#endif //CLASSIFICATION_MAHALANOBISDISTANCE_H
