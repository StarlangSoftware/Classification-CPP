//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_BOOTSTRAPRUN_H
#define CLASSIFICATION_BOOTSTRAPRUN_H


#include "MultipleRun.h"

class BootstrapRun : public MultipleRun {
private:
    int numberOfBootstraps;
public:
    BootstrapRun(int numberOfBootstraps);
    ExperimentPerformance* execute(Experiment experiment) override;
};


#endif //CLASSIFICATION_BOOTSTRAPRUN_H
