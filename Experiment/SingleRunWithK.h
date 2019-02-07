//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_SINGLERUNWITHK_H
#define CLASSIFICATION_SINGLERUNWITHK_H

#include "CrossValidation.h"
#include "SingleRun.h"

class SingleRunWithK : public SingleRun {
public:
    explicit SingleRunWithK(int K);
protected:
    int K;
    Performance* runExperiment(Classifier* classifier, Parameter* parameter, CrossValidation<Instance*>* crossValidation);
    Performance* execute(Experiment experiment);
};


#endif //CLASSIFICATION_SINGLERUNWITHK_H
