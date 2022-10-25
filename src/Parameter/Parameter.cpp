//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#include "Parameter.h"

/**
 * Constructor of {@link Parameter} class which assigns given seed value to seed.
 *
 * @param seed Seed is used for random number generation.
 */
Parameter::Parameter(int seed) {
    this->seed = seed;
}

/**
 * Accessor for the seed.
 *
 * @return The seed.
 */
int Parameter::getSeed() const{
    return seed;
}
