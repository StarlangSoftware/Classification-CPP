//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#include "KnnInstance.h"

/**
 * The constructor that sets the instance and distance value.
 *
 * @param instance Instance input.
 * @param distance Double distance value.
 */
KnnInstance::KnnInstance(Instance* instance, double distance) {
    this->instance = instance;
    this->distance = distance;
}

/**
 * The to_string method returns the concatenation of class label of the instance and the distance value.
 *
 * @return The concatenation of class label of the instance and the distance value.
 */
string KnnInstance::to_string() const{
    string str;
    str += instance->getClassLabel();
    str += + " ";
    str += distance;
    return str;
}

double KnnInstance::getDistance() const{
    return distance;
}

Instance *KnnInstance::getInstance() const{
    return instance;
}
