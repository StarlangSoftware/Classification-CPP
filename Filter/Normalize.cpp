//
// Created by Olcay Taner Yıldız on 4.02.2019.
//

#include "Normalize.h"
#include "../Attribute/ContinuousAttribute.h"

/**
 * Constructor for normalize feature filter. It calculates and stores the mean (m) and standard deviation (s) of
 * the sample.
 *
 * @param dataSet Instances whose continuous attribute values will be normalized.
 */
Normalize::Normalize(DataSet &dataSet) : FeatureFilter(dataSet) {
    averageInstance = dataSet.getInstanceList().average();
    standardDeviationInstance = dataSet.getInstanceList().standardDeviation();
}

/**
 * Normalizes the continuous attributes of a single instance. For all i, new x_i = (x_i - m_i) / s_i.
 *
 * @param instance Instance whose attributes will be normalized.
 */
void Normalize::convertInstance(Instance *instance) {
    for (int i = 0; i < instance->attributeSize(); i++) {
        if (instance->getAttribute(i)->isContinuous()) {
            ContinuousAttribute* xi = (ContinuousAttribute*)(instance->getAttribute(i));
            ContinuousAttribute* mi = (ContinuousAttribute*)(averageInstance->getAttribute(i));
            ContinuousAttribute* si = (ContinuousAttribute*)(standardDeviationInstance->getAttribute(i));
            xi->setValue((xi->getValue() - mi->getValue()) / si->getValue());
        }
    }
}

void Normalize::convertDataDefinition() {
}
