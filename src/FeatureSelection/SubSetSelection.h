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
    virtual vector<FeatureSubSet> operatorToModify(const FeatureSubSet& current, int numberOfFeatures) = 0;
    void forward(vector<FeatureSubSet>& currentSubSetList, const FeatureSubSet& current, int numberOfFeatures);
    void backward(vector<FeatureSubSet>& currentSubSetList, const FeatureSubSet& current);
public:
    explicit SubSetSelection(const FeatureSubSet& initialSubSet);
    explicit SubSetSelection(int numberOfFeatures);
    SubSetSelection();
    FeatureSubSet execute(MultipleRun* multipleRun, Experiment experiment);
};


#endif //CLASSIFICATION_SUBSETSELECTION_H
