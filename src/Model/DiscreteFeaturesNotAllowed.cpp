//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#include "DiscreteFeaturesNotAllowed.h"

const char *DiscreteFeaturesNotAllowed::what() const noexcept {
    return "Discrete Features are not allowed for this classifier";
}
