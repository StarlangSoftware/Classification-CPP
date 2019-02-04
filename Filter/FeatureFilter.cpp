//
// Created by Olcay Taner Yıldız on 2.02.2019.
//

#include "FeatureFilter.h"

/**
 * Constructor that sets the dataSet.
 *
 * @param dataSet DataSet that will bu used.
 */
FeatureFilter::FeatureFilter(DataSet& dataSet) {
    this->dataSet = dataSet;
}

/**
 * Feature converter for a list of instances. Using the abstract method convertInstance, each instance in the
 * instance list will be converted.
 */
void FeatureFilter::convert() {
    vector<Instance*> instances = dataSet.getInstances();
    for (Instance* instance : instances) {
        convertInstance(instance);
    }
    convertDataDefinition();
}
