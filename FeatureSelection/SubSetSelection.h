//
// Created by olcay on 13.02.2019.
//

#ifndef CLASSIFICATION_SUBSETSELECTION_H
#define CLASSIFICATION_SUBSETSELECTION_H


#include "FeatureSubSet.h"
#include "../Experiment/Experiment.h"
#include "../Experiment/MultipleRun.h"

class SubSetSelection {
protected:
    FeatureSubSet initialSubSet;
    virtual vector<FeatureSubSet> operatorToModify(FeatureSubSet& current, int numberOfFeatures) = 0;
    void forward(vector<FeatureSubSet> currentSubSetList, FeatureSubSet& current, int numberOfFeatures);
    void backward(vector<FeatureSubSet> currentSubSetList, FeatureSubSet& current);
public:
    explicit SubSetSelection(FeatureSubSet& initialSubSet);
    FeatureSubSet execute(MultipleRun* multipleRun, Experiment experiment);
};


#endif //CLASSIFICATION_SUBSETSELECTION_H
