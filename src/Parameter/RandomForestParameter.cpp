//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#include "RandomForestParameter.h"

/**
 * Parameters of the random forest classifier.
 *
 * @param seed                Seed is used for random number generation.
 * @param ensembleSize        The number of trees in the bagged forest.
 * @param attributeSubsetSize Integer value for the size of attribute subset.
 */
RandomForestParameter::RandomForestParameter(int seed, int ensembleSize, int attributeSubsetSize) : BaggingParameter(seed, ensembleSize) {
    this->attributeSubsetSize = attributeSubsetSize;
}

/**
 * Accessor for the attributeSubsetSize.
 *
 * @return The attributeSubsetSize.
 */
int RandomForestParameter::getAttributeSubsetSize() const{
    return attributeSubsetSize;
}
