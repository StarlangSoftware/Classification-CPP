//
// Created by Olcay Taner YILDIZ on 30.08.2024.
//

#ifndef CLASSIFICATION_RANDOMFORESTMODEL_H
#define CLASSIFICATION_RANDOMFORESTMODEL_H


#include "TreeEnsembleModel.h"

class RandomForestModel : public TreeEnsembleModel {
public:
    RandomForestModel() = default;
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_RANDOMFORESTMODEL_H
