//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_SINGLERUN_H
#define CLASSIFICATION_SINGLERUN_H

#include "Experiment.h"
#include "../Performance/Performance.h"

class SingleRun {
public:
    virtual Performance* execute(const Experiment& experiment) = 0;
};


#endif //CLASSIFICATION_SINGLERUN_H
