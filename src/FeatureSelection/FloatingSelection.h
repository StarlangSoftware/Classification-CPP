//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_FLOATINGSELECTION_H
#define CLASSIFICATION_FLOATINGSELECTION_H
#include "SubSetSelection.h"

class FloatingSelection : public SubSetSelection{
protected:
    vector<FeatureSubSet> operatorToModify(const FeatureSubSet& current, int numberOfFeatures) override;
public:
    FloatingSelection();
};


#endif //CLASSIFICATION_FLOATINGSELECTION_H
