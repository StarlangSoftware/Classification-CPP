//
// Created by Olcay Taner Yıldız on 29.01.2019.
//

#include "EuclidianDistance.h"
#include "../Attribute/DiscreteAttribute.h"
#include "../Attribute/ContinuousAttribute.h"
#include <cmath>

/**
 * Calculates Euclidian distance between two instances. For continuous features: \sum_{i=1}^d (x_i^(1) - x_i^(2))^2,
 * For discrete features: \sum_{i=1}^d 1(x_i^(1) == x_i^(2))
 *
 * @param instance1 First instance
 * @param instance2 Second instance
 * @return Euclidian distance between two instances.
 */
double EuclidianDistance::distance(Instance *instance1, Instance *instance2) {
    double result = 0;
    for (int i = 0; i < instance1->attributeSize(); i++) {
        if (instance1->getAttribute(i)->isDiscrete() && instance2->getAttribute(i)->isDiscrete()) {
            if (((DiscreteAttribute*)(instance1->getAttribute(i)))->getValue() != ((DiscreteAttribute*)(instance2->getAttribute(i)))->getValue()) {
                result += 1;
            }
        } else {
            if (instance1->getAttribute(i)->isContinuous() && instance2->getAttribute(i)->isContinuous()) {
                result += pow(((ContinuousAttribute*)(instance1->getAttribute(i)))->getValue() - ((ContinuousAttribute*)(instance2->getAttribute(i)))->getValue(), 2);
            }
        }
    }
    return result;
}
