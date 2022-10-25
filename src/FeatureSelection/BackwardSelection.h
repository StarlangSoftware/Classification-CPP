//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_BACKWARDSELECTION_H
#define CLASSIFICATION_BACKWARDSELECTION_H
#include "SubSetSelection.h"

class BackwardSelection : public SubSetSelection {
protected:
    vector<FeatureSubSet> operatorToModify(const FeatureSubSet& current, int numberOfFeatures) override;
public:
    explicit BackwardSelection(int numberOfFeatures);
};


#endif //CLASSIFICATION_BACKWARDSELECTION_H
