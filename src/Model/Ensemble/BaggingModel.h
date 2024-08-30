//
// Created by Olcay Taner YILDIZ on 30.08.2024.
//

#ifndef CLASSIFICATION_BAGGINGMODEL_H
#define CLASSIFICATION_BAGGINGMODEL_H

#include "TreeEnsembleModel.h"

class BaggingModel : public TreeEnsembleModel{
public:
    BaggingModel() = default;
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_BAGGINGMODEL_H
