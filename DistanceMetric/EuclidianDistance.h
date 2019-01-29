//
// Created by Olcay Taner Yıldız on 29.01.2019.
//

#ifndef CLASSIFICATION_EUCLIDIANDISTANCE_H
#define CLASSIFICATION_EUCLIDIANDISTANCE_H


#include "DistanceMetric.h"

class EuclidianDistance : public DistanceMetric {
public:
    double distance(Instance* instance1, Instance* instance2);
};


#endif //CLASSIFICATION_EUCLIDIANDISTANCE_H
