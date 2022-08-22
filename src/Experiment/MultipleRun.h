//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_MULTIPLERUN_H
#define CLASSIFICATION_MULTIPLERUN_H


#include "Experiment.h"
#include "../Performance/ExperimentPerformance.h"

class MultipleRun {
public:
    virtual ExperimentPerformance* execute(Experiment experiment) = 0;
};


#endif //CLASSIFICATION_MULTIPLERUN_H
