//
// Created by Olcay Taner Yıldız on 29.01.2019.
//

#ifndef CLASSIFICATION_DISTANCEMETRIC_H
#define CLASSIFICATION_DISTANCEMETRIC_H

#include "../Instance/Instance.h"

class DistanceMetric {
public:
    virtual double distance(Instance* instance1, Instance* instance2) = 0;
};


#endif //CLASSIFICATION_DISTANCEMETRIC_H
