//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_FORWARDSELECTION_H
#define CLASSIFICATION_FORWARDSELECTION_H
#include "SubSetSelection.h"

class ForwardSelection : public SubSetSelection {
protected:
    vector<FeatureSubSet> operatorToModify(const FeatureSubSet& current, int numberOfFeatures) override;
public:
    ForwardSelection();
};


#endif //CLASSIFICATION_FORWARDSELECTION_H
