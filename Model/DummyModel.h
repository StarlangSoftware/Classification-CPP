//
// Created by Olcay Taner Yıldız on 8.02.2019.
//

#ifndef CLASSIFICATION_DUMMYMODEL_H
#define CLASSIFICATION_DUMMYMODEL_H

#include <DiscreteDistribution.h>
#include "Model.h"
#include "../InstanceList/InstanceList.h"

class DummyModel : public Model {
private:
    DiscreteDistribution distribution;
public:
    explicit DummyModel(InstanceList& trainSet);
    string predict(Instance* instance) override;
};


#endif //CLASSIFICATION_DUMMYMODEL_H
