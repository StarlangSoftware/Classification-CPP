//
// Created by olcay on 31.01.2019.
//

#include "ClassificationAlgorithmExpectedException.h"

/**
 * The toString method returns "Classification Algorithm required for accuracy metric" String.
 *
 * @return "Classification Algorithm required for accuracy metric" String.
 */
const char *ClassificationAlgorithmExpectedException::what() const noexcept {
    return "Classification Algorithm required for accuracy metric";
}
