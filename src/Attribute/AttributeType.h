//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_ATTRIBUTETYPE_H
#define CLASSIFICATION_ATTRIBUTETYPE_H

enum class AttributeType{
    /**
     * Continuous Attribute
     */
            CONTINUOUS,
    /**
     * Discrete Attribute
     */
            DISCRETE,
    /**
     * Binary Attribute
     */
            BINARY,
    /**
     * Discrete Indexed Attribute is used to store the indices.
     */
            DISCRETE_INDEXED
};

#endif //CLASSIFICATION_ATTRIBUTETYPE_H
