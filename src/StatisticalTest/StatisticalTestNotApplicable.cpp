//
// Created by olcay on 31.01.2019.
//

#include "StatisticalTestNotApplicable.h"

const char *StatisticalTestNotApplicable::what() const noexcept {
    string s = test + " is not applicable. " + reason;
    return s.c_str();
}

StatisticalTestNotApplicable::StatisticalTestNotApplicable(string test, string reason) {
    this->test = std::move(test);
    this->reason = std::move(reason);
}
